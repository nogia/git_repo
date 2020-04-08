#pragma once

#include "GlgClass.h"

class GlgTagRecord
{
public:
   GlgTagRecord( void );
   ~GlgTagRecord( void );
public:
   GlgObjectC tag_obj;
   int data_type;
   char * tag_source;
   char * tag_name;
};
