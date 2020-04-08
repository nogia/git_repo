/*
 *   	Licensed Materials - Property of IBM
 * 	(c) Copyright IBM Corp. 2002, 2003 All Rights Reserved
 */
#ifndef _WBXMLPARSER_H
#define _WBXMLPARSER_H
/**
 * struct is to handle callbacks from the WBXML parser.
 */
typedef struct
{
	/**
	* Indicates the start of the WBXML document.
	* @param fpi the char pointer pointing to the Formal Public Identifier.
	* @param start the starting offset of the FPI.
	* @param length the length of the FPI in char.
	*/
	short (*startDocumentFPIString)(void *userCtx,const char *fpi,long length);
	/**
	* Indicates the start of the WBXML document.
	* @param fpi the documents Formal Public Identifier represented by an int.
	*/
	short (*startDocumentFPIInt)(void *userCtx,long fpi);
	/**
	* Indicates the end of the WBXML document.
	*/
	short (*endDocument)(void *userCtx);
	/**
	* Indicates the start of an element. The element can either be an attribute or
	* a tag depending on the current codespace.
	* @param token the element represented by a WBXML token.
	*/
	short (*startToken)(void *userCtx,unsigned char token);
	/**
	* Indicates the start of an element.  The element can either be an attribute of
	* a tag depending on the current codespace.
	* @param characters the char pointer pointing the literal.
	* @param start the starting offset of the literal.
	* @param length the length of the literal in bytes.
	*/
	short (*startTokenLit)(void *userCtx,const char *characters,long length);
	/**
	* Indicates the end of an element.  The element can either be an attribute or
	* a tag depending on the current codespace.
	*/
	short (*endElement)(void *userCtx);
	/**
	* Indicates content
	* @param characters the char pointer pointing the content.
	* @param start the starting offset of the content.
	* @param length the length of the content in bytes.
	*/
	void (*content)(void *userCtx,const char *characters,long length);
	/**
	* Indicates an attribute content.
	* @param token the token representing the attributes content.
	*/
	void (*contentToken)(void *userCtx,long token);
	/**
	* Indicates a switch in the active codepage within the current code space.
	* @param codePage the new code page.
	*/
	short (*switchCodePage)(void *userCtx,long codePage);
	/**
	* Indicates a switch between the tag codespace and the attribute codespace.
	* The initial codespace is the tag codespace.
	*/
	void (*toggleCodeSpace)(void *userCtx);
} WbxmlHandler_t , *WbxmlHandler_ptr_t;
/* Parse WBXML */
short parse(const char *aBuffer, const long anOffset, const long length, WbxmlHandler_ptr_t _handler, void *userCtx);
#endif
