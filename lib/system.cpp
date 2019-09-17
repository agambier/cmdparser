#define SYSTEM_PUBLIC
#include "system.h"

//
//
System::System() :
	m_isSystemReady( false ),
#if defined( ESP8266 )
	m_resetReason( ESP.getResetInfoPtr()->reason )
#else
	m_resetReason( 0 )
#endif
{
}

#if defined( SYSTEM_COMMANDS )
//
//
const __FlashStringHelper* System::keyWord() const
{
	return F( "system" );
}

//
//
void System::processCmd( Cmd::Parser &parser )
{
	if( parser.cmd() != keyWord() )
		return;

	//	System information
	if( parser.arg() == F( "info" ) )
	{	
		parser.lastStream()->println( "System information..." );
		parser.lastStream()->printf( "  State            : %s\n", isSystemReady() ? "READY" : "BOOT FAILED" );
#if defined( ESP8266 )
		parser.lastStream()->printf( "  CPU ID           : %08X\n", cpuId() );
		parser.lastStream()->printf( "  CPU Frequence    : %d MHz\n", cpuFreqMHz() );
		parser.lastStream()->printf( "  Reset reason     : %s\n", ESP.getResetReason().c_str() );
		parser.lastStream()->printf( "  Sketch size      : %d bytes\n", ESP.getSketchSize() );
		parser.lastStream()->printf( "  Free sketch size : %d bytes\n", ESP.getFreeSketchSpace() );
		parser.lastStream()->printf( "  FLASH ID         : %08X\n", ESP.getFlashChipId() );
		parser.lastStream()->printf( "  FLASH Size       : %d bytes\n", ESP.getFlashChipSize() );
		parser.lastStream()->printf( "  FLASH speed      : %d MHz\n", ESP.getFlashChipSpeed() / 1000000 );
#endif
		return;
	}

	//	System reboot
	if( parser.arg() == F( "reboot" ) )
	{	
		parser.lastStream()->println( "Rebooting system..." );
		reboot();
		return;
	}

	//	help
	if( 0 == parser.arg().length() )
	{
		parser.lastStream()->println( "System commands..." );
		parser.lastStream()->println( "  info -> Displays system information." );
		parser.lastStream()->println( "  reboot -> Reboot system." );
		return;
	}
	
	//	???
	parser.lastStream()->println( "[ERROR] Unknown command." );
}
#endif

//
//
void System::handleBootFailures() const
{
	if( m_isSystemReady )
		return;

	Serial.print( "#############################\n");
	Serial.print( "## SYSTEM FAILED TO BOOT ! ##\n");
	Serial.print( "#############################\n");
	for( ;; )
	{
		wdtFeed();
	};
}