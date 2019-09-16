#ifndef __cmdstream_H__
#define __cmdstream_H__

#include <stdio.h>
#include <stdint.h>

#define COMMAND_STREAM_SIZE		128

namespace Cmd
{

class Stream
{
	public:
		Stream();

		virtual bool read() = 0;
		virtual bool write( const uint8_t *data, size_t size );
		virtual void printf( const char *format, ... );
		virtual void print( const char *string );
		virtual void println( const char *string );

		inline bool isCmdReady() const;
		inline const char* lastCmd() const;
		inline void reset();

	private:
		uint8_t m_index;
		bool m_isCmdReady;
		char m_lastCmd[ COMMAND_STREAM_SIZE ];

	protected:
		void addChar( char value );
};

//	----- INLINE FUNCTIONS -----
const char* Stream::lastCmd() const {
	return m_lastCmd;
}
bool Stream::isCmdReady() const {
	return m_isCmdReady;
}
void Stream::reset() {
	m_isCmdReady = false;
}

}
#endif