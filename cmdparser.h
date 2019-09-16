#ifndef __cmdparser_H__
#define __cmdparser_H__

#include "../settings.h"
#include "cmdtoken.h"
#include "serialcmdstream.h"

//	Define max readers :
//		Serial port
//		WiFi UDP
#define	CMDPARSER_MAX_STREAMS	2

class CmdParser
{
	public:
		CmdParser();
		
		bool process();
		
		inline CmdStream* lastStream() const;
		inline const CmdToken& cmd() const;
		inline const CmdToken& arg() const;
		inline void shiftArg();
		inline void resetArg();

	protected:
		CmdToken m_cmd;
		CmdToken m_arg;
		CmdStream *m_streams[ CMDPARSER_MAX_STREAMS ];
		CmdStream *m_lastStream;
#if defined( SET_SERIAL_COMMANDS )
		SerialCmdStream m_serialStream;
#endif

	private:
		void findNextToken( CmdToken &token, const char *start );
};

//	----- INLINE FUNCTIONS -----
CmdStream* CmdParser::lastStream() const {
	return m_lastStream;
}
const CmdToken& CmdParser::cmd() const {
	return m_cmd;
}
const CmdToken& CmdParser::arg() const {
	return m_arg;
}
void CmdParser::shiftArg() {
	findNextToken( m_arg, m_arg.end() );
}
void CmdParser::resetArg() {
	memcpy( &m_arg, &m_cmd, sizeof( m_arg ) );
	shiftArg();
}


#endif