
#include "GlgTagRecord.h"

GlgTagRecord::GlgTagRecord( void )
{
}

GlgTagRecord::~GlgTagRecord( void )
{
   GlgFree( tag_source ); // checks for NULL
   GlgFree( tag_name );   // checks for NULL
}
