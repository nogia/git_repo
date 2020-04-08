/*
 *   	Licensed Materials - Property of IBM
 * 	(c) Copyright IBM Corp. 2002, 2003 All Rights Reserved
 */

#include "stdafx.h"

#include "WbxmlParser.h"
#include "SyncMLExceptionErrorCodes.h"
#include "SyncMLError.h"
#include "global.h"

/**
 * Used to parse WBXML documents.
 */
/**
 * Global WBXML tokens
 */
#define SWITCH_PAGE		0x00
#define END				0x01
#define ENTITY			0x02
#define STR_I			0x03
#define LITERAL			0x04
#define EXT_I_0			0x40
#define EXT_I_1			0x41
#define EXT_I_2			0x42
#define PI				0x43
#define LITERAL_C		0X44
#define EXT_T_0			0x80
#define EXT_T_1			0x81
#define EXT_T_2			0x82
#define STR_T			0x83
#define LITERAL_A		0x84
#define EXT_0			0xC0
#define EXT_1			0xC1
#define EXT_2			0xC2

// Windows Opaque Definition
#ifdef OPAQUE
#undef OPAQUE
#endif

#define OPAQUE			0xC3
#define LITERAL_AC		0xC4
#define EMPTY_MASK		0x40
#define ATTRSTART		0x80
#define CHARSET			0x6A
typedef struct
{
   WbxmlHandler_ptr_t handler;
   void *userCtx;
   long depth;
   const char *buffer;
   const char *endPtr;
   const char *currentPtr;
   const char *stringTableStartPtr;
   const char *stringTableEndPtr;
   const char *stringOffset;
   long stringLength;
} WbxmlParserContext_t, *WbxmlParserContext_ptr_t;
/* Function to check if the next byte is a code page switch */
#define readCodePageSwitch(ctxptr)		\
	if (SWITCH_PAGE == (*ctxptr->currentPtr & 0xFF))	\
	{							\
		++(ctxptr->currentPtr);	\
      errorcode = ctxptr->handler->switchCodePage(ctxptr->userCtx,*ctxptr->currentPtr ++ & 0xFF);\
      if (errorcode)	\
			return errorcode;		\
	}

/* Function to read processing instructions */
#define readPIs(ctxprt)				\
	while((ctxptr)->currentPtr < (ctxptr)->endPtr && PI == (*(ctxptr)->currentPtr &0xFF))		\
	{							\
		++(ctxptr)->currentPtr;	\
      errorcode = readAttribute(ctxptr);\
      if (errorcode)	\
			return errorcode;\
		if (END != (*(ctxptr)->currentPtr++ & 0xFF)) return _INVALID_END_OF_PI;\
	}
/* Function to read a string from the string table */
static void readStringTable (WbxmlParserContext_ptr_t ctxptr, long offset );
/* Function to read a string */
static short readStringEntity (WbxmlParserContext_ptr_t ctxptr );
/* Function to read a 32 bit unsigned integer encoded as a multi-byte integer */
static long readMultiByteInt (WbxmlParserContext_ptr_t ctxptr );
/* Parse WBXML */
static short doParse (WbxmlParserContext_ptr_t ctxptr );
/* Function to read an attribute name-value pair, returns two strings */
static short readAttribute (WbxmlParserContext_ptr_t ctxptr );
/* Function to read a string from the string table */
void readStringTable (WbxmlParserContext_ptr_t ctxptr, long offset )
{
   const char *stringStart;
   const char *stringThrough;
   ctxptr->stringOffset = ctxptr->stringTableStartPtr + offset;
   ctxptr->stringLength = 0;
   stringStart = ctxptr->stringOffset;
   stringThrough = stringStart;
   if (stringThrough < ctxptr->stringTableEndPtr )
   {
      while (0 != *stringThrough && stringThrough < ctxptr->stringTableEndPtr )
         stringThrough ++;
      ctxptr->stringLength = stringThrough - stringStart;
   }
}

/* Function to read a string */
short readStringEntity (WbxmlParserContext_ptr_t ctxptr )
{
   switch (*ctxptr->currentPtr++ & 0xFF )
   {
      case OPAQUE:
         ctxptr->stringLength=readMultiByteInt (ctxptr );
         ctxptr->stringOffset = ctxptr->currentPtr;
         ctxptr->currentPtr += ctxptr->stringLength;
//         ctxptr->stringOffset;
         break;
      case STR_I:
         ctxptr->stringOffset= ctxptr->currentPtr;
         while (0 != *ctxptr->currentPtr++ )
         {
            ;
         }
         /* Calculate string length excluding trailing null */
         ctxptr->stringLength = ctxptr->currentPtr - ctxptr->stringOffset - 1;
//         ctxptr->stringOffset;
         break;
      case STR_T:
      case LITERAL:
      case LITERAL_A:
      case LITERAL_C:
         readStringTable (ctxptr, readMultiByteInt (ctxptr ) );
         break;
      case ENTITY:
         return _INVALID_ENTITY;
   }
   return _SUCCESS;
}
/* Function to read a 32 bit unsigned integer encoded as a multi-byte integer */
long readMultiByteInt (WbxmlParserContext_ptr_t ctxptr )
{
   long mbuint32 = 0;
   do
   {
      mbuint32 = (mbuint32 << 7) | (*ctxptr->currentPtr & 0x7F);
   }
   while ((*ctxptr->currentPtr++ & 0x80) > 0 );
   return mbuint32;
}
static short doParse (WbxmlParserContext_ptr_t ctxptr )
{
   int stop = 0;
   short errorcode= _SUCCESS;

   for (;;)
   {
      unsigned char data = *ctxptr->currentPtr & 0xFF;
      if (((data & 0xF0) == EXT_I_0 || (data & 0xF0) == EXT_T_0
            || (data & 0xF0) == EXT_0) && (data & 0x0F) < STR_I )
         return _INVALID_TOKEN;
      if (data == STR_I || data == OPAQUE || data == STR_T || data == ENTITY )
      {
         errorcode = readStringEntity (ctxptr );
         if (_SUCCESS != errorcode )
            return errorcode;
         ctxptr->handler->content (ctxptr->userCtx, ctxptr->stringOffset,
               ctxptr->stringLength );
      }
      else
      {
         readCodePageSwitch(ctxptr);
         data = *ctxptr->currentPtr++ & 0xFF;
         switch (data )
         {
            case PI:
               readAttribute (ctxptr );
               if (_SUCCESS != (errorcode = readAttribute(ctxptr)) )
               {
#ifdef _DEBUG
                  WbxmlExceptionMsg ("doParse." );
#endif
                  return errorcode;
               }
               break;
            case END:
               stop = errorcode = ctxptr->handler->endElement (ctxptr->userCtx );
               if (errorcode )
                  return errorcode;
               --ctxptr->depth;
               if (ctxptr->depth==0 )
               {
                  readPIs(ctxptr);
                  errorcode = ctxptr->handler->endDocument (ctxptr->userCtx );
                  if (errorcode )
                  {
#ifdef _DEBUG
                     WbxmlExceptionMsg ("doParse." );
#endif
                     return errorcode;
                  }
                  return _SUCCESS;
               }
               if (stop )
                  return _NORMAL_PARSER_END;
               break;
            default:
               /* Get tag string */
               if (data == LITERAL || data == LITERAL_C || data == LITERAL_A )
               {
				  --ctxptr->currentPtr;
                  errorcode = readStringEntity (ctxptr );
                  if (errorcode )
                     return errorcode;
                  errorcode = ctxptr->handler->startTokenLit (ctxptr->userCtx,
                        ctxptr->stringOffset, ctxptr->stringLength );
               }
               else
                  errorcode = ctxptr->handler->startToken (ctxptr->userCtx,
                        (unsigned char)(data & 0x3F) );
               if (errorcode )
                  return errorcode;
               /* Read and ignore attributes */
               if (data >= ATTRSTART )
               {
                  while (END != *ctxptr->currentPtr )
                  {
                     errorcode= readAttribute (ctxptr );
                     if (errorcode )
                     {
#ifdef _DEBUG
                        WbxmlExceptionMsg ("doParse." );
#endif
                        return errorcode;
                     }
                  }
                  ++ctxptr->currentPtr;
               }
               if ((data & EMPTY_MASK) == 0 )
               {
                  errorcode = ctxptr->handler->endElement (ctxptr->userCtx );
                  if (errorcode )
                     return errorcode;
               }
               else
                  ++ctxptr->depth;
         }
      }
   }
   //return errorcode;
}

short parse (const char *aBuffer, const long anOffset, const long length,
      WbxmlHandler_ptr_t _handler, void *userCtx )
{
   short errorcode;
   short fpiIsRef;
   long fpi;
   long stringTableLength;
   WbxmlParserContext_t ctx;
   ctx.userCtx = userCtx;
   ctx.handler = _handler;
   ctx.depth = 0;
   ctx.buffer = aBuffer;
   ctx.currentPtr = ctx.buffer + anOffset;

   /* Move to starting of the WBXML */
   ctx.endPtr = ctx.currentPtr + length;
   /* Read WBXML Header */
   /* Read version */
   ctx.currentPtr ++;
   /* Read FPI */
   fpiIsRef = 0 == (*ctx.currentPtr);
   if (fpiIsRef )
      ctx.currentPtr ++;
   fpi = readMultiByteInt (&ctx );

   /* Read char encoding */
   if (readMultiByteInt (&ctx ) != CHARSET )
      return _UNSUPPORT_CHARSET;
   /* Read set string table parameters*/
   stringTableLength = readMultiByteInt (&ctx );
   ctx.stringTableStartPtr = ctx.currentPtr;
   ctx.stringTableEndPtr = ctx.currentPtr + stringTableLength;
   ctx.currentPtr = ctx.stringTableEndPtr;
   /* Check FPI */
   if (fpiIsRef )
   {
      readStringTable (&ctx, fpi );
//      ctx.stringOffset;
      errorcode = ctx.handler->startDocumentFPIString (ctx.userCtx,
            ctx.stringOffset, ctx.stringLength );
   }
   else
      errorcode = ctx.handler->startDocumentFPIInt (ctx.userCtx, fpi );
   if (errorcode )
      return errorcode;
   /* Parse body */
   {
      WbxmlParserContext_ptr_t ctxptr = &ctx;
      readPIs(ctxptr);
   }
   return (doParse (&ctx ));
}

/* Function to read an attribute name-value pair, returns two strings */
short readAttribute (WbxmlParserContext_ptr_t ctxptr )
{
   short errorcode= _SUCCESS;

   /* Switch to attribute code space */
   ctxptr->handler->toggleCodeSpace (ctxptr->userCtx );
   /* Check if it is a literal */
   if (LITERAL == (*ctxptr->currentPtr & 0xFF) )
   {
      errorcode = readStringEntity (ctxptr );
      if (errorcode )
         return errorcode;
      errorcode = ctxptr->handler->startTokenLit (ctxptr->userCtx,
            ctxptr->stringOffset, ctxptr->stringLength );
   }
   else
   {
      /* Read optional code page switch */
      readCodePageSwitch(ctxptr);
      /* Check if it belongs to the lower half of the attribute code page */
      if ((*ctxptr->currentPtr & 0xFF) >= ATTRSTART )
         return _INVALID_ATTRIBUTE;
      errorcode = ctxptr->handler->startToken (ctxptr->userCtx,
            (unsigned char)((*ctxptr->currentPtr++) & 0x3F) );
   }
   if (errorcode )
      return errorcode;
   /* Read the attribute value */
   for (;;)
   {
      int data = *ctxptr->currentPtr & 0xFF;
      if (((data & 0xF0) == EXT_I_0 || (data & 0xF0) == EXT_T_0
            || (data & 0xF0) == EXT_0) && (data & 0x0F) < STR_I )
         return _INVALID_TOKEN;
      if (data == STR_I || data == OPAQUE || data == STR_T || data == ENTITY )
      {
         errorcode = readStringEntity (ctxptr );
         if (_SUCCESS != errorcode )
            return errorcode;
         ctxptr->handler->content (ctxptr->userCtx, ctxptr->stringOffset,
               ctxptr->stringLength );
      }
      else
      {
         readCodePageSwitch(ctxptr);
         if ((*ctxptr->currentPtr & 0xFF) < ATTRSTART )
            break;
         ctxptr->handler->contentToken (ctxptr->userCtx, *ctxptr->currentPtr++
               & 0x3F );
      }
   }
   errorcode = ctxptr->handler->endElement (ctxptr->userCtx );
   if (errorcode )
      return errorcode;
   ctxptr->handler->toggleCodeSpace (ctxptr->userCtx );
   return _SUCCESS;
}
