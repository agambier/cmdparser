#include <Arduino.h>
#include <stdarg.h>
#include "serialcmdstream.h"

//
//
bool SerialCmdStream::read()
{
	while( Serial.available() )
		addChar( static_cast< char >( Serial.read() ) );

	return isCmdReady();
}

//
//
bool SerialCmdStream::printf( const char *format, ...  )
{
	//	format string
	va_list args;
	va_start( args, format) ;
	char string[ 128 ];
	vsnprintf( string, sizeof( string ) / sizeof( string[ 0 ] ) - 1, format, args );
	va_end( args );

	//	output it
	Serial.print( string );

	return true;
}

//
//
bool SerialCmdStream::print( const char *string )
{
	Serial.print( string );
	return true;
}
