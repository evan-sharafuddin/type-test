// Provides types and functions for widgets such as titles, buttons, etc

// TODO create static widget struct instance so don't need to call it for each function



#ifndef RAWTERM_WIDGETS_H
#define RAWTERM_WIDGETS_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <stdbool.h>

typedef struct button {
    const char* text; // text to display inside button
    int pad;  // padding of the button 
    bool sel;   // whether button is selected by cursor
} button_t;

typedef struct title {
    const char* text; // text for title 
    int width;  // width of the button
} title_t;

typedef struct body {
    const char* text; // body text
    int width;  // width of the box containing body text
} body_t;

// TODO might be worth just having the buttons in here and the other
// widgets can be on their own
typedef struct widgets {
    
    // pointer to array of each type of widget
    button_t* buttons;
    title_t*  titles;
    body_t* bodies;

    // keep track of number of each widget
    int nbuttons;
    int ntitles;
    int nbodies;

    // default foreground and background colors of each widget
    // buttons have selected and deselected color combinations
    const char* fgbutton_sel;
    const char* bgbutton_sel;
    const char* fgbutton_def;
    const char* bgbutton_def;

    const char* fgtitle;
    const char* bgtitle;

    const char* fgbody;
    const char* bgbody;

} widget_t;

// helper functions below
// TODO want to create some helpers for creating default struct, etc
// need to think about whether I want to dynamically allocate widget_t,
// or if its small enough that copying to new stack frame is not that labor intensive

widget_t* default_widget();

int add_button( const char*, int  );
void add_title( const char*, int );
void add_body( const char*, int);

void print_buttons();

void remove_buttons();

int prompt_buttons();

#ifdef __cplusplus
}
#endif

#endif // RAWTERM_WIDGETS_H