#include <string.h>
#include <ctype.h>

#include "bitsmode.h"


mode_t
turn_off_umask()
{
	return umask(0);
}


mode_t
str_to_octals(const char *str_octals)
{
	if (strlen(str_octals) > CHARACTERS)
		return EXCEEDED_ERROR;

	mode_t octals = 0;
	mode_t temp_mode = 0;
	mode_t temp_int = 0;
	int bits = 0;
	int i;
	
	size_t len = strlen(str_octals);
	for(i = len-1; i >= 0; i--) {
		
		if (!isdigit(str_octals[i]))
			return DIGITS_ERROR;
			
		if ( str_octals[i] > '7' || str_octals[i] < '0' )
			return RANGE_ERROR;
			
		temp_int = str_octals[i] - '0'; //convert to int
		temp_mode = temp_int << bits; //shifting mode's bits to the appropriate place(from right to left)
		octals = octals | temp_mode; //set mode
		bits = bits + 3;
		
	}
	
	return octals;
}
