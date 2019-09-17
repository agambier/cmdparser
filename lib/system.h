#ifndef __system_H__
#define __system_H__

#include <Arduino.h>
#if defined( ESP8266 )
#	include <user_interface.h>
#else
#	include <avr/wdt.h>
#endif

#if defined( SYSTEM_COMMANDS )
#	include "cmdparser.h"
#endif

class System
{
	public:
		System();

#if defined( SYSTEM_COMMANDS )
		const __FlashStringHelper* keyWord() const;
		void processCmd( Cmd::Parser &parser );
#endif
		inline bool isSystemReady() const;
		inline void systemIsReady();

		inline bool isNormalReset() const;
		inline bool isWdtReset() const;
		inline bool isDeepSleepReset() const;
		inline bool isSoftwareReset() const;
		inline uint8_t resetReason() const;

		inline void reboot() const;
		inline uint32_t cpuId() const;
		inline uint8_t cpuFreqMHz() const;

		void handleBootFailures() const;

		inline void wdtDisable() const;
		inline void wdtEnable( uint8_t timeout ) const;
		inline void wdtFeed() const;
	private:
		bool m_isSystemReady;
		uint8_t m_resetReason;
};

//	----- inline functions -----
bool System::isSystemReady() const {
	return m_isSystemReady;
}
void System::systemIsReady() {
	m_isSystemReady = true;
}
bool System::isNormalReset() const {
#if defined( ESP8266 )
	return ( REASON_DEFAULT_RST == m_resetReason ) 
		|| ( REASON_EXCEPTION_RST == m_resetReason )
		|| ( REASON_EXT_SYS_RST == m_resetReason );
#else
	return true;
#endif
}
bool System::isWdtReset() const {
#if defined( ESP8266 )
	return ( REASON_WDT_RST == m_resetReason ) 
		|| ( REASON_SOFT_WDT_RST == m_resetReason );
#else
	return true;
#endif
}
bool System::isDeepSleepReset() const {
#if defined( ESP8266 )
	return ( REASON_DEEP_SLEEP_AWAKE == m_resetReason );
#else
	return true;
#endif
}
bool System::isSoftwareReset() const {
#if defined( ESP8266 )
	return ( REASON_SOFT_RESTART == m_resetReason );
#else
	return true;
#endif
}
uint8_t System::resetReason() const {
	return m_resetReason;
}
void System::reboot() const {
#if defined( ESP8266 )
	ESP.restart();
#else
	wdtDisable();
	wdtEnable( WDTO_15MS );
	for(;;);
#endif
}
uint32_t System::cpuId() const {
#if defined( ESP8266 )
	return ESP.getChipId();
#else
	return 0;
#endif
}
uint8_t System::cpuFreqMHz() const {
#if defined( ESP8266 )
	return 	ESP.getCpuFreqMHz();
#else
	return 0;
#endif
}
void System::wdtDisable() const
{
#if defined( ESP8266 )
#else
	wdt_disable();
#endif
}
void System::wdtEnable( uint8_t timeout ) const
{
#if defined( ESP8266 )
#else
	wdt_enable( timeout );
#endif
}
void System::wdtFeed() const
{
#if defined( ESP8266 )
#else
	wdt_reset();
#endif
}


#endif