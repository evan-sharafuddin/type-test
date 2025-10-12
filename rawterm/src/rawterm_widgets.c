// Implementation for rawterm widgets

#include "rawterm_widgets.h"
#include "rawterm_utils.h"
#include "rawterm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NULL_PTR -1
widget_t* init_widget() {
    widget_t* w = (widget_t*) malloc(sizeof(widget_t));
    if (!w) return NULL;

    w->buttons = NULL;
    w->titles  = NULL;
    w->bodies  = NULL;

    w->nbuttons = 0;
    w->ntitles  = 0;
    w->nbodies  = 0;

    w->fgbutton_sel = "default";
    w->bgbutton_sel = "red";
    w->fgbutton_def = "gray"; 
    w->bgbutton_def = "default";

    w->fgtitle = "default";
    w->bgtitle = "red";

    w->fgbody = "default";
    w->bgbody = "gray";

    return w;
}

int free_widget( widget_t* w ) {
    if ( !w ) return NULL_PTR; 
    free( w );
    return 0;
}

// TODO add error handelling 
// NOTE returns index of the button 
int add_button( widget_t* w, const char* text, int pad ) {
    
    if ( !w ) return NULL_PTR;
    // if ( !w ) return; // must have widget_t struct

    // have the first button we add be selected automatically
    bool sel = !( w->buttons );

    // increment button counter
    ++w->nbuttons;

    button_t bt = {
        .text = text,
        .pad = pad,
        .sel = sel,
    };

    // TODO might be more efficent to not realloc() every time adding a button

    // NOTE C++ is type safe, so we cannot rely on implicit cast betwen void* pointer to our struct
    // need to explicitly cast
    if ( !(w->buttons) ) {
        w->buttons = (button_t*) malloc( w->nbuttons*sizeof(button_t) );
    }
    else {
        w->buttons = (button_t*) realloc( w->buttons, w->nbuttons*sizeof(button_t) );
    }

    // check for malloc/realloc issues
    // TODO make this better

    if ( !w->buttons ) fprintf(stderr, "malloc() or realloc() error");

    w->buttons[w->nbuttons-1] = bt;

    // return index of this button (this will always be 0 or greater)
    return w->nbuttons - 1;

}

// TODO create clean function that resets widget entirely
int free_buttons( widget_t* w ) {

    if ( !w ) return NULL_PTR;
    free( w->buttons );
    return 0;
}

// TODO might want to more explicitly check for deref null pointers
int print_buttons( widget_t* w ) {
    if ( !w ) return NULL_PTR;

    button_t bt;
    for ( int i = 0; i < w->nbuttons; ++i ) {
        bt = w->buttons[i];

        char pad [bt.pad];
        sprintf( pad, "%*s", bt.pad, "" );

        foreground_color( (bt.sel) ? w->fgbutton_sel : w->fgbutton_def );
        background_color( (bt.sel) ? w->bgbutton_sel : w->bgbutton_def );
        out(pad);
        out(bt.text);
        out(pad);

        reset_formatting();
        out(" ");
    }

    return 0;
}

int prompt_buttons( widget_t* w ) {

    if ( !w ) return NULL_PTR;
    // select button!
#define ENTER 13 // TODO add all keys as compiler defs
    
    // first hide the curser 
    hide_cursor();

    // print out buttons
    print_buttons( w );

    while (1) {
        char c = '\0';

        if ( read( STDIN_FILENO, &c, 1 ) == -1 && errno != EAGAIN )
            die("read");

        // TODO store idx of selected button instead of searching thru to find
        if (c == ENTER) {

            // show cursor before leaving
            show_cursor();
            clear_line();

            for ( int i = 0; i < w->nbuttons; ++i ) {
                if ( w->buttons[i].sel ) return i;
            }

            // no button selected? this should be an error
            return -1;
        }

        // detect arrow key 
        // left: \x1b[D
        // right: \x1b[C

        if (c == 27) {
            char seq[2];

            // account for when user just entered esc key
            if (read(STDIN_FILENO, &seq[0], 1) != 1) continue;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) continue;

            if (seq[0] == '[') {
                bool left = seq[1] == 'D';
                bool right = seq[1] == 'C';
                
                if ( !(left || right) ) continue; // some other arrow key was pressed
                else // select the appropriate button
                {
                    bool sel; 
                    for ( int i = 0; i < w->nbuttons; ++i ) {
                        
                        if ( w->buttons[i].sel ) {
                            
                            // if left arrow, select left unless we are already on leftmost button
                            if ( left && !(i == 0) ) {
                                w->buttons[i].sel = false;
                                w->buttons[i-1].sel = true;
                            }

                            // if right arrow, select right unless we are already on rightmost button
                            else if ( right && !(i == w->nbuttons-1) ) { 
                                w->buttons[i].sel = false;
                                w->buttons[i+1].sel = true;
                            }  

                            break; // done 
                        }
                    }
                }

                // clear the line
                clear_line();

                // print out the buttons on the line 
                print_buttons( w );
            }
        }
    }
    return 0;
}
