#include "cmdtoken.h"

namespace Cmd
{
//
//
Token::Token( const char *start, uint8_t length ) :
	m_start( start ), 
	m_length( length )
{
}

}