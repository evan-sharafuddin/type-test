// Implementation for rawterm widgets

#include "rawterm_widgets.h"
#include "rawterm_utils.h"
#include <stdbool.h>
#include <stdio.h>

//  NOTE will have this be stored in stack/
widget_t* default_widget() {
    
    // initialized only once
    static widget_t w = {
        .buttons = NULL,
        .titles  = NULL,
        .bodies  = NULL,

        .nbuttons = 0,
        .ntitles = 0,
        .nbodies = 0,

        .fgbutton_sel = "red",
        .bgbutton_sel = "blue",
        .fgbutton_def = "gray", 
        .bgbutton_def = "default",

        .fgtitle = "white",
        .bgtitle = "red",

        .fgbody = "white",
        .bgbody = "gray", 
    };

    return &w;

}

// TODO add error handelling 
void add_button( widget_t* w, char* text, int width ) {
    
    if ( !w ) return; // must have widget_t struct

    // have the first button we add be selected automatically
    bool sel = !( w->buttons );

    // increment button counter
    ++w->nbuttons;

    button_t bt = {
        .text = text,
        .width = width,
        .sel = sel,
    };

    // TODO might be more efficent to not realloc() every time adding a button
    if ( !(w->buttons) ) {
        w->buttons = malloc( w->nbuttons*sizeof(button_t) );
    }
    else {
        w->buttons = realloc( w->buttons, w->nbuttons*sizeof(button_t) );
    }

    // check for malloc/realloc issues
    // TODO make this better
    if ( !w->buttons ) fprintf(stderr, "malloc() or realloc() error");

}

// TODO might want to more explicitly check for deref null pointers
void print_buttons( widget_t* w ) {

    button_t bt;
    for ( int i = 0; i < w->nbuttons; ++i ) {
        bt = w->buttons[i];
        foreground_color( (bt->sel) ? w->fgbutton_sel : w->fgbutton_def );

    }
}
