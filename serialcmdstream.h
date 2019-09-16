#ifndef __serialcmdstream_H__
#define __serialcmdstream_H__

#include "cmdstream.h"

namespace Cmd
{
class SerialStream : public Stream
{
	public:
		bool read();
		void printf( const char *format, ... );
		void print( const char *string );
		void println( const char *string );
};
}
#endif