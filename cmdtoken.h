#ifndef __cmdtoken_H__
#define __cmdtoken_H__

#include <Arduino.h>
#include <stdint.h>
#include <string.h>

class CmdToken
{
	public:
		CmdToken( const char *start = nullptr, uint8_t length = 0 );

		inline const char* start() const;
		inline void setStart( const char *start );

		inline const char* end() const;

		inline uint8_t length() const;
		inline void setLength( uint8_t length );

		inline bool isValid() const;

		inline void toString( char *string ) const;
		inline bool operator== ( const char *string ) const;
		inline bool operator== ( const __FlashStringHelper *string ) const;
		inline bool operator!= ( const char *string ) const;
		inline bool operator!= ( const __FlashStringHelper *string ) const;
	private:
		const char *m_start;
		uint8_t m_length;	
};

//	----- INLINE FUNCTIONS -----
const char* CmdToken::start() const {
	return m_start;
}
void CmdToken::setStart( const char *start ) {
	m_start = start;
}
const char* CmdToken::end() const {
	return m_start + m_length;
}
uint8_t CmdToken::length() const {
	return m_length;
}
void CmdToken::setLength( uint8_t length ) {
	m_length = length;
}
bool CmdToken::isValid() const {
	return 0 != m_length;
}
void CmdToken::toString( char *string ) const {
	strncpy( string, m_start, m_length );
	string[ m_length ] = 0;
}
bool CmdToken::operator== ( const char *string ) const {
	return ( strlen( string ) == m_length ) && !strncmp( m_start, string, m_length );
}
bool CmdToken::operator== ( const __FlashStringHelper *string ) const {
	return ( strlen_P( reinterpret_cast< PGM_P >( string ) ) == m_length ) && !strncmp_P( m_start, reinterpret_cast< PGM_P >( string ), m_length );
}
bool CmdToken::operator!= ( const char *string ) const {
	return !operator==( string );
}
bool CmdToken::operator!= ( const __FlashStringHelper *string ) const {
	return !operator==( string );
}



#endif