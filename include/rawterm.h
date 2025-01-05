/* RawTerm Library

This library contains functionality to create a raw terminal session

Inspired by this link:
https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html

*/

#pragma once

// C headers
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

struct termios orig;
struct termios raw;

// display of error type and exit 
void die( const char* );

// disable raw mode
void disable_raw_mode();

// enable raw mode
void enable_raw_mode();