// starting to work on general terminal utils, such as formatting, printing, selecting options, etc


#ifndef RAWTERM_UTILS_H
#define RAWTERM_UTILS_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif 

enum errorc {
    success, 
    line_number_size, // line number is too big for character buffer
    color_not_found,   // color name not found in list of colors
    out_of_bounds // desired cursor movement was out of bounds for terminal
};

// general output
int out( const char* );

// cursor navigation
int move_cursor_up( unsigned int );
int move_cursor_down( unsigned int );
int move_cursor_left( unsigned int );
int move_cursor_right( unsigned int );
int move_cursor_home();
int newline(); 


// cursor options
int show_cursor();
int hide_cursor();


// color options and formatting
int foreground_color( const char* );
int background_color( const char* );
int bold();
int italicize();
int faint();
int reset_formatting();

// struct containing color mappings
typedef struct color {
    const char* name;
    int fg;
    int bg;
} color_t;


// read modes
void continuous_read( const char* );
void esc_sequence_read( const char* );


// clearing text
int clear_cursor_to_end();
int clear_start_to_cursor();
int clear_line();
int clear_terminal();
int clear_char();

// getters
int get_line();
int get_col();

#ifdef __cplusplus
}
#endif

#endif // RAWTERM_UTILS_H