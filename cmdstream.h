#ifndef __cmdstream_H__
#define __cmdstream_H__

#include <stdio.h>
#include <stdint.h>
#include "../settings.h"

class CmdStream
{
	public:
		CmdStream();

		virtual bool read() = 0;
		virtual bool write( const uint8_t *data, size_t size );
		virtual bool printf( const char *format, ... );
		virtual bool print( const char *string );

		inline bool isCmdReady() const;
		inline const char* lastCmd() const;
		inline void reset();

	private:
		uint8_t m_index;
		bool m_isCmdReady;
		char m_lastCmd[ SET_COMMAND_STREAM_SIZE ];

	protected:
		void addChar( char value );
};

//	----- INLINE FUNCTIONS -----
const char* CmdStream::lastCmd() const {
	return m_lastCmd;
}
bool CmdStream::isCmdReady() const {
	return m_isCmdReady;
}
void CmdStream::reset() {
	m_isCmdReady = false;
}

#endif