#include "rawterm_utils.h"
#include <stdio.h>

// general output
int out ( char* str ) {
    write( STDOUT_FILENO, str, strlen(str) );
}


// curser naviation
#define MAXBUF 7 // includes 3 digit linenumber and 
#define MAXNUM 999
int move_cursor_up( int num_lines ) {
    if ( num_lines > MAXNUM ) {
        return line_number_size;
    }

    char str[MAXBUF];
    // don't need snprintf becaues never will overflow buffer based on above

    sprintf( str, "\x1b[%dA", num_lines );
    
    return write( STDOUT_FILENO, str, strlen(str) );
}

int move_cursor_down( int num_lines ) {
    if ( num_lines > MAXNUM ) {
        return line_number_size;
    }

    char str[MAXBUF];
    sprintf( str, "\x1b[%dB", num_lines );
    
    return write( STDOUT_FILENO, str, strlen(str) );
}

int move_cursor_right( int num_cols ) {
    if ( num_cols > MAXNUM ) {
        return line_number_size;
    }    

    char str[MAXBUF];
    sprintf( str, "\x1b[%dC", num_cols );

    return write( STDOUT_FILENO, str, strlen(str) );
}

int move_cursor_left( int num_cols ) {
    if ( num_cols > MAXNUM ) {
        return line_number_size;
    }

    char str[MAXBUF];
    sprintf( str, "\x1b[%dD", num_cols );

    return write( STDOUT_FILENO, str, strlen(str) );
}

int newline() {
    return write( STDOUT_FILENO, "\r\n", strlen("\r\n") );
}


// cursor options
int show_cursor() {
    return write( STDOUT_FILENO, "\x1b[?25h", strlen("\x1b[?25h") );
}

int hide_cursor() {
    return write( STDOUT_FILENO, "\x1b[?25l", strlen("\x1b[?25l") );
}


// color options and formatting

// load up array of colors
#define NUM_COLORS 9

static color_t colors[NUM_COLORS] = {
    [0] = {"black"  , 30, 40}, 
    [1] = {"red"    , 31, 41},
    [2] = {"green"  , 32, 42},
    [3] = {"yellow" , 33, 43},
    [4] = {"blue"   , 34, 44},
    [5] = {"magenta", 35, 45},
    [6] = {"cyan"   , 36, 46},
    [7] = {"white"  , 37, 47},
    [8] = {"default", 39, 49}
};

#define COLOR_MAXBUF 6
int foreground_color( char* color ) {
    for ( int i = 0; i < sizeof(colors) / sizeof(color_t); ++i ) {
        if ( color == colors[i].name ) {
            char str[COLOR_MAXBUF];
            snprintf( str, COLOR_MAXBUF, "\x1b[%dm", colors[i].fg );
            return write( STDOUT_FILENO, str, strlen(str) );
        }
    }

    return color_not_found;
}

int background_color( char* color ) {
    for ( int i = 0; i < sizeof(colors) / sizeof(color_t); ++i ) {
        if ( color == colors[i].name ) {
            char str[COLOR_MAXBUF];
            snprintf( str, COLOR_MAXBUF, "\x1b[%dm", colors[i].bg );
            return write( STDOUT_FILENO, str, strlen(str) );
        }
    }

    return color_not_found;
}


int bold() {
    return write( STDOUT_FILENO, "\x1b[1m", strlen("\x1b[1m") );
}

int italicize() {
    return write( STDOUT_FILENO, "\x1b[3m", strlen("\x1b[3m") );
}

int faint() {
    return write( STDOUT_FILENO, "\x1b[2m", strlen("\x1b[2m") );
}


int reset_formatting() {
    return write( STDOUT_FILENO, "\x1b[0m", strlen("\x1b[0m") );
}