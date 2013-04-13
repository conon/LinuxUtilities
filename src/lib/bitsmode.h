#ifndef BITSMODE_H
#define BITSMODE_H

#include <sys/stat.h>

#define EXCEEDED_ERROR	8
#define DIGITS_ERROR	9
#define RANGE_ERROR		10


#define CHARACTERS  5

/**
 * Converts string octal representation, to type mode_t octal representation
 * 
 * @param str_octals	octal string representation
 * @return				mode_t octal representation
 * 
 * @return 				EXCEEDED_ERROR ( 8 )  if str_octals contains more characters
 * 						than CHARACTERS.
 * @return				DIGITS_ERROR ( 9 ) if str_octals contains characters that
 * 						are not digits.
 * @return				RANGE_ERROR ( 10 ) if str_octals is not in digit range of
 * 						octals numbers(0-7).
 * 
 * */
mode_t str_to_octals(const char *str_octals);



/**
 * Turns off file mode creation mask, This functions always succeeds
 * 
 * @return				The previous umask value
 * */
mode_t turn_off_umask();


#endif
