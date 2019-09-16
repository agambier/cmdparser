#include "cmdstream.h"

//
//
CmdStream::CmdStream() :
	m_index( 0 ),
	m_isCmdReady( false )
{
	m_lastCmd[ 0 ] = '\0';
}

//
//
bool CmdStream::write( const uint8_t *data, size_t size )
{
	return true;
}

//
//
bool CmdStream::printf( const char *format, ... )
{
	return true;
}

//
//
bool CmdStream::print( const char *string )
{
	return true;
}


//
//
void CmdStream::addChar( char value )
{
	if( '\n' == value )
		return;

	if( 0 == m_index )
		m_isCmdReady = false;

	if( '\r' == value )
	{
		m_lastCmd[ m_index ] = '\0';
		m_index = 0;
		m_isCmdReady = true;
	}
	else if( m_index < ( SET_COMMAND_STREAM_SIZE - 1 ) )
	{
		m_lastCmd[ m_index ] = value;
		m_index ++;
	}
}