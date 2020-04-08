// This is the main DLL file.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace System;
using namespace std;
#include "Compress.h"

namespace Compress 
{
	static unsigned int  buffer, mask;
	unsigned char  getByteNOfNumber(int nByte, int number)
	{
		int x11 = (number >> (8*nByte)) & 0xff;
		return (unsigned char )x11;
	}
	unsigned int Add_Nth_byte(int byteNumber, int number)
    {
		return  (((number) & 0xFF)<<(8 * byteNumber)); 
    }
	Compress::Compress(char * op)
	 {
		  textsize = 0;
		  codesize = 0;
		  printcount = 0;
		  text_buf = new unsigned char[N + F - 1];
		  lson = new int[N+1];
		  rson = new int[N+257];
		  dad = new int[N+1];  
		  low = 0;
		  high = Q4; 
		  value = 0;
		  shifts = 0;
		  char_to_sym = new int[N_CHAR];
		  sym_to_char = new int[N_CHAR + 1];
		  sym_freq = new unsigned int[N_CHAR + 1];
		  sym_cum =  new unsigned int[N_CHAR + 1];
		  position_cum = new unsigned int[N+1];   
		  operation = op;
		  if(* operation == 'e')
		  {
		     buffer =0, mask=128;
		  }
		  else if( * operation == 'd')
		  {
		     buffer =0, mask=0;
		  }
	 }
	Compress::~Compress()
	{
	}
	void  Compress::Error(char *message)
	 {
	                 printf("\n%s\n", message);
	                 exit(EXIT_FAILURE);
	 }
    void  Compress::PutBit(int bit)
	 {
	     if(* operation == 'e')
		 {
			if (bit) buffer |= mask;
			 if ((mask >>= 1) == 0) 
			{
	
				if (putc(buffer, outfile) == EOF) Error("Write Error");
				buffer = 0;  mask = 128;  codesize++;
			 }
		 }
		 else if(* operation == 'd')
		 {
			   static unsigned int  buffer = 0, mask = 128;
			   if (bit) buffer |= mask;
			    if ((mask >>= 1) == 0) 
			    {
	
				     if (putc(buffer, outfile) == EOF) Error("Write Error");
				        buffer = 0;  mask = 128;  codesize++;
			    }
		 }
     }
	 void  Compress::PutBit(int bit,unsigned char * value)
	 {
	    if(* operation == 'e')
	   {
			 if (bit) 
					buffer |= mask;
			 if ((mask >>= 1) == 0) 
				{
                     *outfile_buffer = buffer;
					 outfile_buffer++;
					 lenOutfile++;
		             buffer = 0;  mask = 128;  codesize++;
			    }
	    }
       else if(* operation == 'd')
	   {
		   static unsigned int  buffer = 0, mask = 128;
		   if (bit) 
					buffer |= mask;
			 if ((mask >>= 1) == 0) 
				{
                    *outfile_buffer = buffer;
					 outfile_buffer++;
					 lenOutfile++;
		             buffer = 0;  mask = 128;  codesize++;
			    }
	   }
	  
     }
	 void Compress::FlushBitBuffer(void)  /* Send remaining bits */
	{
		int  i;
	    for (i = 0; i < 7; i++) 
			PutBit(0);
	}
	  void Compress::FlushBitBuffer(unsigned char * value)  /* Send remaining bits */
	{
		int  i;
	    for (i = 0; i < 7; i++) 
			PutBit(0,value);
	}


	int Compress::GetBit(void)  /* Get one bit (0 or 1) */
	{
	   if(* operation == 'e')
	   {
			if ((mask >>= 1) == 0) 
			{
		        buffer = getc(infile);  
				mask = 128;                                    
            }
			 return ((buffer & mask) != 0);
	   }
	   else if(* operation == 'd')
	   {
		   
		   if ((mask >>= 1) == 0) 
			{
		        buffer = getc(infile);  
				mask = 128;                                    
            }
			 return ((buffer & mask) != 0);
	   }
	}
	int Compress::GetBit(unsigned char * value1)  /* Get one bit (0 or 1) */
	{
	    if(* operation == 'e')
		{
			if ((mask >>= 1) == 0) 
			{
		         buffer = * value1;
			     mask = 128;                                    
            
	        }
	         return ((buffer & mask) != 0);
		}
		else if(* operation == 'd')
		{
			if ((mask >>= 1) == 0) 
			{
		         buffer = (unsigned int) (*infile_buffer);
				 infile_buffer++;
			     mask = 128;                                    
	        }
	         return ((buffer & mask) != 0);
		}
	}
	void Compress::rst_crc(void)
    {
       crc_16=0xffff;
    }
	void Compress::calc_crc(unsigned char ch)
	 {
		unsigned short index;

		index = crc_16 >> 8;
		index = index ^ ch;
		crc_16 = crc_16 << 8;
		crc_16 = crc_16 ^ crc_table[index];
	}
	unsigned short Compress::get_crc(void)
	{
			return crc_16;
	}
	void Compress::InitTree(void)  /* Initialize trees */
	{
		int  i;

	/* For i = 0 to N - 1, rson[i] and lson[i] will be the right and
	   left children of node i.  These nodes need not be initialized.
	   Also, dad[i] is the parent of node i.  These are initialized to
	   NIL (= N), which stands for 'not used.'
	   For i = 0 to 255, rson[N + i + 1] is the root of the tree
	   for strings that begin with character i.  These are initialized
	   to NIL.  Note there are 256 trees. */

		for (i = N + 1; i <= N + 256; i++) rson[i] = NIL;	/* root */
		for (i = 0; i < N; i++) dad[i] = NIL;	/* node */
	}

	void Compress::InsertNode(int r)
	/* Inserts string of length F, text_buf[r..r+F-1], into one of the
	   trees (text_buf[r]'th tree) and returns the longest-match position
	   and length via the global variables match_position and match_length.
	   If match_length = F, then removes the old node in favor of the new
	   one, because the old one will be deleted sooner.
	   Note r plays double role, as tree node and position in buffer. */
	{
			int  i, p, cmp, temp;
			unsigned char  *key;

			cmp = 1;  key = &text_buf[r];  p = N + 1 + key[0];
			rson[r] = lson[r] = NIL;  match_length = 0;
			for ( ; ; ) {
				if (cmp >= 0) {
					if (rson[p] != NIL) p = rson[p];
					else {  rson[p] = r;  dad[r] = p;  return;  }
				} else {
				if (lson[p] != NIL) p = lson[p];
				else {  lson[p] = r;  dad[r] = p;  return;  }
			}
			for (i = 1; i < F; i++)
				if ((cmp = key[i] - text_buf[p + i]) != 0)  break;
			if (i > THRESHOLD) {
				if (i > match_length) {
					match_position = (r - p) & (N - 1);
					if ((match_length = i) >= F) break;
				} else if (i == match_length) {
					if ((temp = (r - p) & (N - 1)) < match_position)
						match_position = temp;
				}
			}
		}
		dad[r] = dad[p];  lson[r] = lson[p];  rson[r] = rson[p];
		dad[lson[p]] = r;  dad[rson[p]] = r;
		if (rson[dad[p]] == p) rson[dad[p]] = r;
		else                   lson[dad[p]] = r;
		dad[p] = NIL;  /* remove p */
	}

	void Compress::DeleteNode(int p)  /* Delete node p from tree */
	{
		int  q;
	
		if (dad[p] == NIL) return;  /* not in tree */
		if (rson[p] == NIL) q = lson[p];
		else if (lson[p] == NIL) q = rson[p];
		else {
			q = lson[p];
			if (rson[q] != NIL) {
				do {  q = rson[q];  } while (rson[q] != NIL);
				rson[dad[q]] = lson[q];  dad[lson[q]] = dad[q];
				lson[q] = lson[p];  dad[lson[p]] = q;
			}
			rson[q] = rson[p];  dad[rson[p]] = q;
		}
		dad[q] = dad[p];
		if (rson[dad[p]] == p) rson[dad[p]] = q;
		else                   lson[dad[p]] = q;
		dad[p] = NIL;
	}

	void  Compress::StartModel(void)  /* Initialize model */
	{
		int ch, sym, i;
	
		sym_cum[N_CHAR] = 0;
		for (sym = N_CHAR; sym >= 1; sym--) {
			ch = sym - 1;
			char_to_sym[ch] = sym;  sym_to_char[sym] = ch;
			sym_freq[sym] = 1;
			sym_cum[sym - 1] = sym_cum[sym] + sym_freq[sym];
		}
		sym_freq[0] = 0;  /* sentinel (!= sym_freq[1]) */
		position_cum[N] = 0;
		for (i = N; i >= 1; i--)
			position_cum[i - 1] = position_cum[i] + 10000 / (i + 200);
					/* empirical distribution function (quite tentative) */
					/* Please devise a better mechanism! */
	}

	void  Compress::UpdateModel(int sym)
	{
		int i, c, ch_i, ch_sym;
	
		if (sym_cum[0] >= MAX_CUM) {
			c = 0;
			for (i = N_CHAR; i > 0; i--) {
				sym_cum[i] = c;
				c += (sym_freq[i] = (sym_freq[i] + 1) >> 1);
			}
			sym_cum[0] = c;
		}
		for (i = sym; sym_freq[i] == sym_freq[i - 1]; i--) ;
		if (i < sym) {
			ch_i = sym_to_char[i];    ch_sym = sym_to_char[sym];
			sym_to_char[i] = ch_sym;  sym_to_char[sym] = ch_i;
			char_to_sym[ch_i] = sym;  char_to_sym[ch_sym] = i;
		}
		sym_freq[i]++;
		while (--i >= 0) sym_cum[i]++;
	}

	void Compress::Output(int bit)  /* Output 1 bit, followed by its complements */
	{
		PutBit(bit);
		for ( ; shifts > 0; shifts--) PutBit(! bit);
	}
	   void Compress::Output(int bit, unsigned char * value)
	   {
		   PutBit(bit,value);
		   for ( ; shifts > 0; shifts--) 
			   PutBit(! bit,value);
	   }
	

	void  Compress::EncodePosition(int position)
	{
		unsigned long int  range;

		range = high - low;
		high = low + (range * position_cum[position    ]) / position_cum[0];
		low +=       (range * position_cum[position + 1]) / position_cum[0];
		for ( ; ; ) {
			if (high <= Q2) Output(0);
			else if (low >= Q2) {
				Output(1);  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				shifts++;  low -= Q1;  high -= Q1;
			} else break;
			low += low;  high += high;
		}
	}
	void  Compress::EncodePosition(int position,unsigned char * value)
	{
		unsigned long int  range;

		range = high - low;
		high = low + (range * position_cum[position    ]) / position_cum[0];
		low +=       (range * position_cum[position + 1]) / position_cum[0];
		for ( ; ; ) {
			if (high <= Q2) Output(0,value);
			else if (low >= Q2) {
				Output(1,value);  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				shifts++;  low -= Q1;  high -= Q1;
			} else break;
			low += low;  high += high;
		}
	}
	void  Compress::EncodeEnd(void)
	{
		shifts++;
		if (low < Q1) Output(0);  else Output(1);
		FlushBitBuffer();  /* flush bits remaining in buffer */
	}
	void  Compress::EncodeEnd(unsigned char * value)
	{
		shifts++;
		if (low < Q1) Output(0,value);  else Output(1,value);
		FlushBitBuffer(value);  /* flush bits remaining in buffer */
	}
	int  Compress::BinarySearchSym(unsigned int x)
		/* 1      if x >= sym_cum[1],
		N_CHAR if sym_cum[N_CHAR] > x,
		i such that sym_cum[i - 1] > x >= sym_cum[i] otherwise */
	{
		int i, j, k;
	
		i = 1;  j = N_CHAR;
		while (i < j) {
		
			k = (i + j) / 2;
			if (sym_cum[k] > x) 
				i = k + 1;  
			else j = k;
		}
		return i;
	}

	int  Compress::BinarySearchPos(unsigned int x)
		/* 0 if x >= position_cum[1],
		N - 1 if position_cum[N] > x,
		i such that position_cum[i] > x >= position_cum[i + 1] otherwise */
	{
		int i, j, k;
	
		i = 1;  j = N;
		while (i < j) {
			k = (i + j) / 2;
			if (position_cum[k] > x) i = k + 1;  else j = k;
		}
		return i - 1;
	}

	void  Compress::StartDecode(void)
	{
		int i;
		for (i = 0; i < M + 2; i++)
		    value = 2 * value + GetBit();
	}
	void  Compress::StartDecode(unsigned char * value1)
	{
		int i;

		for (i = 0; i < M + 2; i++)
				value = 2 * value + (unsigned long int)(GetBit(value1));
	}
	int  Compress::DecodeChar(void)
	{
		int	 sym, ch;
		unsigned long int  range;
	
		range = high - low;
		sym = BinarySearchSym((unsigned int)(((value - low + 1) * sym_cum[0] - 1) / range));
		high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
		low +=       (range * sym_cum[sym    ]) / sym_cum[0];
		for ( ; ; ) {
			if (low >= Q2) {
				value -= Q2;  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				value -= Q1;  low -= Q1;  high -= Q1;
			} else if (high > Q2) break;
			low += low;  high += high;
			value = 2 * value + GetBit();
		}
		ch = sym_to_char[sym];
		UpdateModel(sym);
		return ch;
	}
	int  Compress::DecodeChar(unsigned char * value1)
	{
		int	 sym, ch;
		unsigned long int  range;
	
		range = high - low;
		unsigned int temp = (unsigned int)(((value - low + 1) * sym_cum[0] - 1) / range);
		sym = BinarySearchSym((unsigned int)
			(((value - low + 1) * sym_cum[0] - 1) / range));
		high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
		low +=       (range * sym_cum[sym    ]) / sym_cum[0];
		for ( ; ; ) {
			if (low >= Q2) {
				value -= Q2;  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				value -= Q1;  low -= Q1;  high -= Q1;
			} else if (high > Q2) break;
			low += low;  high += high;
			value = 2 * value + GetBit(value1);
		}
		ch = sym_to_char[sym];
		UpdateModel(sym);
		return ch;
	}
	int  Compress::DecodePosition(void)
	{
		int position;
		unsigned long int  range;
	
		range = high - low;
		position = BinarySearchPos((unsigned int)
			(((value - low + 1) * position_cum[0] - 1) / range));
		high = low + (range * position_cum[position    ]) / position_cum[0];
		low +=       (range * position_cum[position + 1]) / position_cum[0];
		for ( ; ; ) {
			if (low >= Q2) {
				value -= Q2;  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				value -= Q1;  low -= Q1;  high -= Q1;
			} else if (high > Q2) break;
			low += low;  high += high;
			value = 2 * value + GetBit();
		}
		return position;
	}
	int  Compress::DecodePosition(unsigned char * value1)
	{
		int position;
		unsigned long int  range;
	
		range = high - low;
		position = BinarySearchPos((unsigned int)
			(((value - low + 1) * position_cum[0] - 1) / range));
		high = low + (range * position_cum[position    ]) / position_cum[0];
		low +=       (range * position_cum[position + 1]) / position_cum[0];
		for ( ; ; ) {
			if (low >= Q2) {
				value -= Q2;  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				value -= Q1;  low -= Q1;  high -= Q1;
			} else if (high > Q2) break;
			low += low;  high += high;
			value = 2 * value + GetBit(value1);
		}
		return position;
	}
	void Compress::EncodeChar(int ch)
	{
		int  sym;
		unsigned long int  range;

		sym = char_to_sym[ch];
		range = high - low;
		high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
		low +=       (range * sym_cum[sym    ]) / sym_cum[0];
		for ( ; ; ) {
			if (high <= Q2) Output(0);
			else if (low >= Q2) {
				Output(1);  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				shifts++;  low -= Q1;  high -= Q1;
			} else break;
			low += low;  high += high;
		}
		UpdateModel(sym);
	}
	void Compress::EncodeChar(int ch,unsigned char * value)
	{
		int  sym;
		unsigned long int  range;

		sym = char_to_sym[ch];
		range = high - low;
		high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
		low +=       (range * sym_cum[sym    ]) / sym_cum[0];
		for ( ; ; ) {
			if (high <= Q2) Output(0,value);
			else if (low >= Q2) {
				Output(1,value);  low -= Q2;  high -= Q2;
			} else if (low >= Q1 && high <= Q3) {
				shifts++;  low -= Q1;  high -= Q1;
			} else break;
			low += low;  high += high;
		}
		UpdateModel(sym);
	}
/********** Encode and Decode **********/
   
	void  Compress::Encode(void)
	{
		int  i, c, len, r, s, last_match_length;
        unsigned short crc;

        printf("Compressing file...\n"); 
	    fseek(infile, 0L, SEEK_END);
	   textsize = ftell(infile);
	if (fwrite(&textsize, sizeof textsize, 1, outfile) < 1)
		Error("Write Error");  /* output size of text */
        // write blank variable for file crc
        if (fwrite(&crc, sizeof crc, 1, outfile) < 1)
		Error("File CRC write error");  /* output size of text */
	   codesize += sizeof textsize;
        rst_crc();
	if (textsize == 0) return;
	rewind(infile);  textsize = 0;
	StartModel();  InitTree();
	s = 0;  r = N - F;
	for (i = s; i < r; i++) text_buf[i] = ' ';
	for (len = 0; len < F && (c = getc(infile)) != EOF; len++)
		{
		     text_buf[r + len] = c;
             calc_crc(c);
         }
	
	textsize = len;
	for (i = 1; i <= F; i++) InsertNode(r - i);
	InsertNode(r);
	do {
		if (match_length > len) 
			match_length = len;
		if (match_length <= THRESHOLD) {
			match_length = 1;  EncodeChar(text_buf[r]);
		} else {
			EncodeChar(255 - THRESHOLD + match_length);
			EncodePosition(match_position - 1);
		}
		last_match_length = match_length;
		
		for (i = 0; i < last_match_length && (c = getc(infile)) != EOF; i++) 
		{
			DeleteNode(s); 
			text_buf[s] = c;
            calc_crc(c);
			if (s < F - 1) text_buf[s + N] = c;
			s = (s + 1) & (N - 1);
			r = (r + 1) & (N - 1);
			InsertNode(r);
		}
		if ((textsize += i) > printcount) {
			printf("%12ld\r", textsize);  
			printcount += 1024;
		}
		while (i++ < last_match_length) {
			DeleteNode(s);
			s = (s + 1) & (N - 1);
			r = (r + 1) & (N - 1);
			if (--len) InsertNode(r);
		}
	} while (len > 0);
	EncodeEnd();
	printf("In : %lu bytes\n", textsize);
	printf("Out: %lu bytes\n", codesize);
	printf("Out/In: %.3f\n", (double)codesize / textsize);
        crc=get_crc();
        printf("File CRC16: %XH bytes\n", crc);

        fseek(outfile, sizeof textsize, SEEK_SET);  // rewind file back to crc position
        if (fwrite(&crc, sizeof crc, 1, outfile) < 1)
		Error("File CRC write error");  /* output size of text */
	}

	
	void  Compress::Encode(unsigned char * value)
	{
		int  i, c, len, r, s, last_match_length;
        unsigned short crc;
        textsize = lenInfile;
        lenOutfile = 0;
	   for(int i=0;i<(sizeof textsize);i++)
	   {
		  *outfile_buffer =  getByteNOfNumber(i,  textsize);
		  outfile_buffer++;
		  lenOutfile++;
	  }
	
	  for(int i=0;i<(sizeof crc);i++)
	  {
			   *outfile_buffer =  getByteNOfNumber(i,  crc);
		        outfile_buffer++;
		        lenOutfile++;
	  }
      codesize += sizeof textsize;
	  rst_crc();
	  if (textsize == 0) 
		 return;
	  unsigned char * temp = infile_buffer;
	  int g=0;
	  textsize = 0;
	  StartModel();  InitTree();
	  s = 0;  r = N - F;
	  for (i = s; i < r; i++) text_buf[i] = ' ';
	  for (len = 0; len < F && (temp != NULL) && g<lenInfile; len++,temp++,g++)
		{
			c = *temp;
            text_buf[r + len] = c;
            calc_crc(c);
         }
	textsize = len;
	for (i = 1; i <= F; i++) InsertNode(r - i);
	InsertNode(r);
	do {
		if (match_length > len) match_length = len;
		if (match_length <= THRESHOLD) {
			match_length = 1;  EncodeChar(text_buf[r],value);
		} else {
			
			EncodeChar(255 - THRESHOLD + match_length,value);
			EncodePosition(match_position - 1,value);
		}
		last_match_length = match_length;
		
		for (i = 0; i < last_match_length && temp != NULL && g<lenInfile ; i++,temp++,g++) 
		{
			        c = *temp;
					DeleteNode(s); 
					text_buf[s] = c;
                    calc_crc(c);
					if (s < F - 1) text_buf[s + N] = c;
						s = (s + 1) & (N - 1);
						r = (r + 1) & (N - 1);
					InsertNode(r);
		}
		if ((textsize += i) > printcount) {
			;//printf("%12ld\r", textsize);  printcount += 1024;
		}
		while (i++ < last_match_length) {
			DeleteNode(s);
			s = (s + 1) & (N - 1);
			r = (r + 1) & (N - 1);
			if (--len) InsertNode(r);
		}
	} while (len > 0);
	EncodeEnd(value);
	}

	void  Compress::Decode(unsigned char * value1)
	{
		int  i, j, k, r, c;
		unsigned long int  count;
		unsigned short f_crc;
       
		textsize = 0;
        lenOutfile = 0;
		f_crc =0;
		cout<<endl;
		i=0;
	    for( ;i<(sizeof textsize) ;i++)
	    {
			 textsize = textsize + Add_Nth_byte(i, (unsigned long )(*infile_buffer));
			 cout << textsize <<endl;
			 infile_buffer++;
		}
		if (textsize != lenInfile || textsize == 0) 
			return;      
		int cc= i + (sizeof (unsigned short));
	    for(;i<cc ;i++)
		{
			f_crc = f_crc + Add_Nth_byte(i, (unsigned short)(*infile_buffer));
			infile_buffer++;
		}
		rst_crc();
		StartDecode(value1);  StartModel();
		for (i = 0; i < N - F; i++) text_buf[i] = ' ';
		r = N - F;
		for (count = 0; count < textsize; ) 
		{
			c = DecodeChar(value1);
			if (c < 256)
			{
				*outfile_buffer = c;
				 outfile_buffer++;
				 lenOutfile++;
				 text_buf[r++] = c;
				 calc_crc(c);
				 r &= (N - 1);  count++;
			} 
			else
			{
				i = (r - DecodePosition(value1) - 1) & (N - 1);
				j = c - 255 + THRESHOLD;
				for (k = 0; k < j; k++)
				{
					 c = text_buf[(i + k) & (N - 1)];
					*outfile_buffer = c;
				     outfile_buffer++;
				     lenOutfile++;
					 text_buf[r++] = c;			
					 calc_crc(c);
					 r &= (N - 1);  count++;
				}
			}
			if (count > printcount) {
				printf("%12lu\r", count);  printcount += 1024*16;
			}
		}
		
		printf("%12lu\n", count);
			printf("Unpacked file CRC16: %XH bytes\n", get_crc());

			if (f_crc != get_crc())
			   printf("Warning! Checksum doesn't match!", f_crc);
	}
	void  Compress::Decode(void)
	{
		int  i, j, k, r, c;
		unsigned long int  count;
			unsigned short f_crc;
       
		if (fread(&textsize, sizeof textsize, 1, infile) < 1)
			Error("Read Error");  /* read size of text */
		cout << endl;
		cout << textsize<<endl;
		if (textsize == 0) return;
			if (fread(&f_crc, sizeof (unsigned short), 1, infile) < 1)
            Error("File CRC16 read error");  /* read size of text */
        rst_crc();
		StartDecode();  StartModel();
		for (i = 0; i < N - F; i++) text_buf[i] = ' ';
		r = N - F;
		for (count = 0; count < textsize; ) {
			c = DecodeChar();
			if (c < 256) {
				putc(c, outfile);  
				text_buf[r++] = c;
							
				calc_crc(c);
				r &= (N - 1);  count++;
			} else {
				i = (r - DecodePosition() - 1) & (N - 1);
				j = c - 255 + THRESHOLD;
				for (k = 0; k < j; k++) {
					c = text_buf[(i + k) & (N - 1)];
					putc(c, outfile);
					text_buf[r++] = c;
					calc_crc(c);
					r &= (N - 1);  count++;
				}
			}
			if (count > printcount) {
				printf("%12lu\r", count);  printcount += 1024*16;
			}
		}

		printf("%12lu\n", count);
			printf("Unpacked file CRC16: %XH bytes\n", get_crc());

			if (f_crc != get_crc())
			   printf("Warning! Checksum doesn't match!", f_crc);
	}

	unsigned short  Compress::calc_file_crc(void)
	 {
	   unsigned short crc=0;
	   unsigned long i;
	 
	   int f = fseek(infile, 0L, SEEK_END);
	   textsize = ftell(infile);
	   rewind(infile);
	   for (i=0; i<textsize; i++)
	       crc +=getc(infile);
	   rewind(infile);  
	   textsize=0;
       return crc;
	 }
	unsigned short  Compress::calc_file_crc(int length)
	 {
	   unsigned short crc=0;
	   unsigned long i;
	   textsize = length;
	   unsigned char * temp = infile_buffer;
	   for (i=0; i<textsize; i++)
	   {
         crc += *temp;
		 temp++;
	   }
	   textsize=0;
	   return crc;
	 }
   int Compress::runCompress(int argc, char *argv[])
   {
	 char  *s;
     unsigned short file_crc, file_crc1;
	 
	 if (argc != 4) {
		printf("'lzari e file1 file2' encodes file1 into file2.\n"
			   "'lzari d file2 file1' decodes file2 into file1.\n");
		return EXIT_FAILURE;
	 }
	if ((s = argv[1], s[1] || strpbrk(s, "DEde") == NULL)
	 || (s = argv[2], (infile  = fopen(s, "rb")) == NULL)
	 || (s = argv[3], (outfile = fopen(s, "wb")) == NULL)) {
		printf("??? %s\n", s);  return EXIT_FAILURE;
	}

        file_crc=calc_file_crc();

	if (toupper(*argv[1]) == 'E')
	   Encode(); 
    else
	   Decode();
	
	fclose(infile);  fclose(outfile);
    file_crc1=get_crc();

	return EXIT_SUCCESS;
	 }

	 void Compress::CompressFile(char *in, char *out)
	 {
            infile=fopen(in,"rb");
            if (infile==NULL)
            printf("it's not working");
                 else
            printf("finaly");
	
		    outfile = fopen(out,"wb");
			 if (outfile==NULL)
            printf("it's not working");
                 else
            printf("finaly");
			calc_file_crc();
			Encode();
			fclose(infile);
			fclose(outfile);
			get_crc();
	 }
	
	  void Compress::CompressFile(unsigned char *in,unsigned  long lengthin ,unsigned char *out, unsigned long & lengthout)
	 {
		 infile_buffer =  in;
		 outfile_buffer = out;
		 lenInfile = lengthin;
		 lenOutfile = 0;
		 if(infile_buffer==NULL)
			 return;

		 calc_file_crc(lenInfile);
		 Encode(outfile_buffer);
		 lengthout = lenOutfile; 
		 for(int i=0;i<lengthout;i++)
				   outfile_buffer--;
		
		 unsigned short crc = get_crc();
		 for(int i=0;i<(sizeof lengthout);i++)
	         outfile_buffer++;
		  for(int i=0;i<(sizeof crc);i++)
		  {
			   *outfile_buffer =  getByteNOfNumber(i,  crc);
		        outfile_buffer++; 
		  }
		   for(int i=0;i<(sizeof lengthout) + (sizeof crc);i++)
			    outfile_buffer--;
		out = outfile_buffer;
		     
		 
	 }
	 bool Compress::DecompressFile(char *in, char *out)
	 {
		 unsigned short file_crc, file_crc1;
            infile=fopen(in,"rb");
            if (infile==NULL)
            printf("it's not working");
                 else
            printf("finaly");
	
		    outfile = fopen(out,"wb");
			 if (outfile==NULL)
            printf("it's not working");
                 else
            printf("finaly");
			file_crc = calc_file_crc();
			Decode();
			fclose(infile);
			fclose(outfile);
			file_crc1=get_crc();
			return true;
	 }

	  bool Compress::DecompressFile(unsigned char *in,unsigned  long lengthin ,unsigned char *out, unsigned long & lengthout)
	 {
		 infile_buffer =  in;
		 outfile_buffer = out;
		 lenInfile = lengthin;
		 lenOutfile = 0;
		 if(infile_buffer==NULL)
			 return false;
         unsigned short file_crc, file_crc1;
		 file_crc = calc_file_crc(lenInfile);
		 Decode(outfile_buffer);
		 lengthout = lenOutfile; 
	     file_crc1=get_crc();
		 out = outfile_buffer;
	     return true;
	 }
}