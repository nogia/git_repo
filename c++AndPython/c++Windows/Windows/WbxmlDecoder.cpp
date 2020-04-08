#include "stdafx.h"

#include "WbxmlDecoder.h"
#include "PCData.h"
#include "SyncMLError.h"
#include "MemoryManagement.h"
#include "SyncMLError.h"

static short startDocument(void* entry, const char *fpi, long length);
static short startDocumentInt(WbxmlDecoder_ptr_t wbxmldec, long fpi);
static short endDocument(WbxmlDecoder_ptr_t wbxmldec);
static short startToken(WbxmlDecoder_ptr_t wbxmldec, unsigned char token);
static short startTokenLit(void* entry, const char *characters,
      long length);
static short endElement(WbxmlDecoder_ptr_t wbxmldec);
static void content(void* entry, const char *characters, long length);
static void contentToken(WbxmlDecoder_ptr_t wbxmldec, long token);
static short switchCodePage(WbxmlDecoder_ptr_t wbxmldec, long codePage);
static void toggleCodeSpace(WbxmlDecoder_ptr_t wbxmldec);
short decode(void *,const char *,long);

#define WbxmlDecoder(wbxmldec,standardDTDs) \
{\
	ElementDecoder(&wbxmldec->decoder,standardDTDs);\
	wbxmldec->decoder.decode = decode; \
} 

WbxmlDecoder_ptr_t newWbxmlDecoder(ElementDTD_ptr_t standardDTDs[])
{
   WbxmlDecoder_ptr_t decoder = getMemory(WbxmlDecoder_t);
   if (decoder)
   {
      ElementDecoder(&decoder->decoder, standardDTDs);
      decoder->decoder.decode = decode;
      //		WbxmlDecoder(,standardDTDs);
   }
   return decoder;
}
short decode(void* entry, const char *message, long length)
{
	WbxmlDecoder_ptr_t wbxmldec = (WbxmlDecoder_ptr_t)entry;
   short errorcode;
   WbxmlHandler_t handler;
   handler.content = content;
   handler.contentToken = (void (*)(void *, long))contentToken;
   handler.endDocument = (short (*)(void *))endDocument;
   handler.endElement = (short (*)(void *))endElement;
   handler.startDocumentFPIInt = (short (*)(void *, long))startDocumentInt;
   handler.startDocumentFPIString
         = startDocument;
   handler.startToken = (short (*)(void *, unsigned char))startToken;
   handler.startTokenLit = startTokenLit;
   handler.switchCodePage = (short (*)(void *, long))switchCodePage;
   handler.toggleCodeSpace = (void (*)(void *))toggleCodeSpace;
   wbxmldec->inTagSpace = TRUE;
   errorcode = parse(message, 0, length, &handler, wbxmldec);
   if (_SUCCESS != errorcode)
      SyncMLException(DECODER_EXCEPTION,0,"WbxmlDecoder ::decoder");

   return errorcode;
}

/**
 * @see WbxmlHandler#startDocumentFPIString
 */
short startDocument(void* entry, const char *fpi, long length)
{
	WbxmlDecoder_ptr_t wbxmldec = (WbxmlDecoder_ptr_t)entry;
   ElementDTD_ptr_t *dtdptr = wbxmldec->decoder.eStack.dtds;
   while (0 != *dtdptr)
   {
      if (StrNCmp((*dtdptr)->fpis, fpi, length) && 0 == (*dtdptr)->codePage)
      {
         wbxmldec->decoder.eStack.dtd = *dtdptr;
         return _SUCCESS;
      }
      dtdptr++;

   }
#ifdef _DEBUG
   WbxmlExceptionMsg("WbxmlDecoder ::StartDocument: _INVALID_FPI.");
#endif
   return _INVALID_FPI;
}

/**
 * @see WbxmlHandler#startDocumentFPIInt
 */
short startDocumentInt(WbxmlDecoder_ptr_t wbxmldec, long fpi)
{
   ElementDTD_ptr_t *dtdptr = wbxmldec->decoder.eStack.dtds;
   while (0 != *dtdptr)
   {
      if ((*dtdptr)->fpi == fpi && 0 == (*dtdptr)->codePage)
      {
         wbxmldec->decoder.eStack.dtd = *dtdptr;
         return _SUCCESS;
      }
   }
#ifdef _DEBUG
   WbxmlExceptionMsg("StartDocumentInt: _INVALID_FPI");
#endif
   return _INVALID_FPI;
}
/**
 * @see WbxmlHandler#endDocument
 */
short endDocument(WbxmlDecoder_ptr_t wbxmldec)
{
   /*	#ifdef _DEBUG
    SyncML4CLogStr("<> ");
    #endif*/
   if (wbxmldec->decoder.eStack.top >= wbxmldec->decoder.eStack.estack)
   {
#ifdef _DEBUG
      WbxmlExceptionMsg("endDocument : _INCOMPLETE_MSG.");
#endif
      return _INCOMPLETE_MSG;
   }
   else
      return _SUCCESS;
}
/**
 * @see WbxmlHandler#startToken
 */
short startToken(WbxmlDecoder_ptr_t wbxmldec, unsigned char token)
{
   long elementID = wbxmldec->decoder.eStack.dtd->getIDByToken(token);
   if (wbxmldec->inTagSpace)
   {
      /*
       #ifdef _DEBUG
       SyncML4CLogStr("\n< ");
       SyncML4CLogStr((char *)wbxmldec->decoder.eStack.dtd->getTag(token));
       SyncML4CLogStr(" ");
       #endif*/
      if (0 == elementID)
      {
#ifdef _DEBUG
         WbxmlExceptionMsg("startToken : _INVALID_TOKEN");
#endif
         return _INVALID_TOKEN;
      }
      return (startSyncmlElement(&wbxmldec->decoder, elementID));
   }
   return _SUCCESS;
}
/**
 * @see WbxmlHandler#startTokenLit
 */
short startTokenLit(void* entry, const char *characters, long length)
{
	WbxmlDecoder_ptr_t wbxmldec = (WbxmlDecoder_ptr_t)entry;
   long elementID =
         wbxmldec->decoder.eStack.dtd->getIDByLit(characters, length);
   if (wbxmldec->inTagSpace)
   {
      if (0 == elementID)
      {
#ifdef _DEBUG
         WbxmlExceptionMsg("startTokenLit : _INVALID_TAG.");
#endif
         return _INVALID_TAG;
      }
      return startSyncmlElement(&wbxmldec->decoder, elementID);
   }
   return _SUCCESS;
}
/**
 * @see WbxmlHandler#endElement
 */
short endElement(WbxmlDecoder_ptr_t wbxmldec)
{
   if (wbxmldec->inTagSpace)
      return endSyncmlElement(&wbxmldec->decoder, 0, -1);
   return _SUCCESS;
}
/**
 * @see WbxmlHandler#content
 */
void content(void* entry, const char *characters, long length)
{
	WbxmlDecoder_ptr_t wbxmldec = (WbxmlDecoder_ptr_t)entry;
   if (wbxmldec->inTagSpace)
      syncmlContent(&wbxmldec->decoder, characters, length);
}
/**
 * @see WbxmlHandler#content
 */
void contentToken(WbxmlDecoder_ptr_t /*wbxmldec*/, long /*token*/)
{
}
/**
 * @see WbxmlHandler#switchCodePage
 */
short switchCodePage(WbxmlDecoder_ptr_t wbxmldec, long codePage)
{
   ElementDTD_ptr_t *dtdsptr = wbxmldec->decoder.eStack.dtds;
   long fpi = wbxmldec->decoder.eStack.dtd->fpi;
   while (0 != *dtdsptr)
   {
      if (fpi == (*dtdsptr)->fpi && codePage == (*dtdsptr)->codePage)
      {
         wbxmldec->decoder.eStack.dtd = *dtdsptr;
         return _SUCCESS;
      }
      dtdsptr++;
   }
#ifdef _DEBUG
   WbxmlExceptionMsg("switchCodePage : _INVALID_CODEPAGE.");
#endif
   return _INVALID_CODEPAGE;
}
/**
 * @see WbxmlHandler#toggleCodeSpace
 */
void toggleCodeSpace(WbxmlDecoder_ptr_t wbxmldec)
{
   wbxmldec->inTagSpace = !wbxmldec->inTagSpace;
}
