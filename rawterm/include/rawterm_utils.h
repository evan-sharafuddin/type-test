// starting to work on general terminal utils, such as formatting, printing, selecting options, etc


#ifndef RAWTERM_UTILS_H
#define RAWTERM_UTILS_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>

enum errorc {
    success, 
    line_number_size, // line number is too big for character buffer
    color_not_found   // color name not found in list of colors
};

// general output
int out( char* );

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
int foreground_color( char* );
int background_color( char* );
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
void continuous_read( char* );
void esc_sequence_read( char* );


// clearing text
int clear_cursor_to_end();
int clear_start_to_cursor();
int clear_line();
int clear_terminal();

// buttons 

// struct for buttons 
typedef struct button {
    char* text;
    int width;
    bool sel;
} button_t;


#endif // RAWTERM_UTILS_H