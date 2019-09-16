#include <Arduino.h>
#include <string.h>
#include "cmdparser.h"

//
//
CmdParser::CmdParser()
{
	//	Set pointers of several streams...
	uint8_t i = 0;
#if defined( SET_SERIAL_COMMANDS )
	m_streams[ i++ ] = &m_serialStream;
#endif
	for( ; i < CMDPARSER_MAX_STREAMS; i++ )
	{
		m_streams[ i ] = nullptr;
	}
	m_lastStream = nullptr;
}

//
//
bool CmdParser::process()
{
	//	Try each stream until one gets a command line
	const char *cmdLine = nullptr;
	for( int i = 0; ( nullptr == cmdLine ) && ( i < CMDPARSER_MAX_STREAMS ); i++ )
	{
		if( m_streams[ i ] && m_streams[ i ]->read() )
		{	
			cmdLine = m_streams[ i ]->lastCmd();
			m_streams[ i ]->reset();
			m_lastStream = m_streams[ i ];
		}
	}
	if( nullptr == cmdLine )
		return false;

	//	First token is the main command
	findNextToken( m_cmd, cmdLine );
	resetArg();

	return true;
}

//
//
void CmdParser::findNextToken( CmdToken &token, const char *start )
{
	token.setLength( 0 );
	//	find start of token
	const char *letter = start;
	for( ; ( ( ' ' == *letter ) || ( '\t' == *letter ) ) && ( 0 != *letter ); letter ++ );
	token.setStart( letter );
	//	find end of token
	for( ; ( ' ' != *letter ) && ( '\t' != *letter ) && ( 0 != *letter ); letter ++ );
	token.setLength( static_cast< uint8_t >( letter - token.start() ) );
}

