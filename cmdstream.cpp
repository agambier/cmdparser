#include "cmdstream.h"

namespace Cmd
{
//
//
Stream::Stream() :
	m_index( 0 ),
	m_isCmdReady( false )
{
	m_lastCmd[ 0 ] = '\0';
}

//
//
bool Stream::write( const uint8_t *data, size_t size )
{
	return true;
}

//
//
void Stream::printf( const char *format, ... )
{
}

//
//
void Stream::print( const char *string )
{
}

//
//
void Stream::println( const char *string )
{
}

//
//
void Stream::addChar( char value )
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
	else if( m_index < ( COMMAND_STREAM_SIZE - 1 ) )
	{
		m_lastCmd[ m_index ] = value;
		m_index ++;
	}
}
}