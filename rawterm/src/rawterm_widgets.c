// Implementation for rawterm widgets

#include "rawterm_widgets.h"
#include "rawterm_utils.h"
#include "rawterm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


static widget_t widget = {
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

// TODO add error handelling 
// NOTE returns index of the button 
int add_button( const char* text, int pad ) {
    
    // if ( !w ) return; // must have widget_t struct

    // have the first button we add be selected automatically
    bool sel = !( widget.buttons );

    // increment button counter
    ++widget.nbuttons;

    button_t bt = {
        .text = text,
        .pad = pad,
        .sel = sel,
    };

    // TODO might be more efficent to not realloc() every time adding a button

    // NOTE C++ is type safe, so we cannot rely on implicit cast betwen void* pointer to our struct
    // need to explicitly cast
    if ( !(widget.buttons) ) {
        widget.buttons = (button_t*) malloc( widget.nbuttons*sizeof(button_t) );
    }
    else {
        widget.buttons = (button_t*) realloc( widget.buttons, widget.nbuttons*sizeof(button_t) );
    }

    // check for malloc/realloc issues
    // TODO make this better

    if ( !widget.buttons ) fprintf(stderr, "malloc() or realloc() error");

    widget.buttons[widget.nbuttons-1] = bt;

    // return index of this button (this will always be 0 or greater)
    return widget.nbuttons - 1;

}

// TODO create clean function that resets widget entirely
void remove_buttons() {
    free( widget.buttons );
}

// TODO might want to more explicitly check for deref null pointers
void print_buttons() {

    button_t bt;
    for ( int i = 0; i < widget.nbuttons; ++i ) {
        bt = widget.buttons[i];

        char pad [bt.pad];
        sprintf( pad, "%*s", bt.pad, "" );

        foreground_color( (bt.sel) ? widget.fgbutton_sel : widget.fgbutton_def );
        background_color( (bt.sel) ? widget.fgbutton_sel : widget.fgbutton_def );
        out(pad);
        out(bt.text);
        out(pad);

        reset_formatting();
        out(" ");
    }
}

int prompt_buttons() {
    // select button!
#define ENTER 13 // TODO add all keys as compiler defs
    
    // first hide the curser 
    hide_cursor();

    // print out buttons
    print_buttons();

    while (1) {
        char c = '\0';

        if ( read( STDIN_FILENO, &c, 1 ) == -1 && errno != EAGAIN )
            die("read");

        // TODO store idx of selected button instead of searching thru to find
        if (c == ENTER) {

            // show cursor before leaving
            show_cursor();
            clear_line();

            for ( int i = 0; i < widget.nbuttons; ++i ) {
                if ( widget.buttons[i].sel ) return i;
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
                    for ( int i = 0; i < widget.nbuttons; ++i ) {
                        
                        if ( widget.buttons[i].sel ) {
                            
                            // if left arrow, select left unless we are already on leftmost button
                            if ( left && !(i == 0) ) {
                                widget.buttons[i].sel = false;
                                widget.buttons[i-1].sel = true;
                            }

                            // if right arrow, select right unless we are already on rightmost button
                            else if ( right && !(i == widget.nbuttons-1) ) { 
                                widget.buttons[i].sel = false;
                                widget.buttons[i+1].sel = true;
                            }  

                            break; // done 
                        }
                    }
                }

                // clear the line
                clear_line();

                // print out the buttons on the line 
                print_buttons();
            }
        }
    }
}
