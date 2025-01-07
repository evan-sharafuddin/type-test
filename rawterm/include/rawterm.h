/* RawTerm Library

This library contains functionality to create a raw terminal session

Inspired by this link:
https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html

*/

#ifndef RAWTERM_H
#define RAWTERM_H

// C headers
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

// prevent "name mangeling" 
// https://stackoverflow.com/questions/1041866/what-is-the-effect-of-extern-c-in-c
#ifdef __cplusplus
extern "C" {
#endif 

// display of error type and exit 
void die( const char* );

// disable raw mode
void disable_raw_mode();

// enable raw mode
void enable_raw_mode();

#ifdef __cplusplus
}
#endif

#endif // RAWTERM_H