#ifndef __serialcmdstream_H__
#define __serialcmdstream_H__

#include "cmdstream.h"

class SerialCmdStream : public CmdStream
{
	public:
		bool read();
		bool printf( const char *format, ... );
		bool print( const char *string );
};

#endif