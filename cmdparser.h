#ifndef __cmdparser_H__
#define __cmdparser_H__

#include "cmdtoken.h"
#include "serialcmdstream.h"

//	Define max readers :
//		Serial port
//		WiFi UDP
#define	CMDPARSER_MAX_STREAMS	2

namespace Cmd
{

class Parser
{
	public:
		Parser();
		
		bool process();
		
		inline Stream* lastStream() const;
		inline const Token& cmd() const;
		inline const Token& arg() const;
		inline void shiftArg();
		inline void resetArg();

	protected:
		Token m_cmd;
		Token m_arg;
		Stream *m_streams[ CMDPARSER_MAX_STREAMS ];
		Stream *m_lastStream;
#if defined( SERIAL_COMMANDS )
		SerialStream m_serialStream;
#endif

	private:
		void findNextToken( Token &token, const char *start );
};

//	----- INLINE FUNCTIONS -----
Stream* Parser::lastStream() const {
	return m_lastStream;
}
const Token& Parser::cmd() const {
	return m_cmd;
}
const Token& Parser::arg() const {
	return m_arg;
}
void Parser::shiftArg() {
	findNextToken( m_arg, m_arg.end() );
}
void Parser::resetArg() {
	memcpy( &m_arg, &m_cmd, sizeof( m_arg ) );
	shiftArg();
}

}
#endif