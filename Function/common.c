#include "common.h"

void delay_ms( unsigned int t )
{
	unsigned char i;
	while ( t-- )
		for ( i = 0 ; i < 120; i++ );
}

unsigned int strtoint( unsigned char * str )
{
	unsigned char *strpointer;
	unsigned int tmp;

	tmp = 0;
	strpointer = str;

	while ( *strpointer != '\0' )
	{
		tmp = tmp * 10 + ( *strpointer - '0' );
		strpointer++;
	}

	return tmp;
}
