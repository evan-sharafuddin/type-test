#include "rawterm_utils.h"

// cursor options
int show_cursor() {
    return write( STDOUT_FILENO, "\x1b[?25l", strlen("\x1b[?25l") );
}

int hide_cursor() {
    return write( STDOUT_FILENO, "\x1b[?25l", strlen("\x1b[?25h") );
}
