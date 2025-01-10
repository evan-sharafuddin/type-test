// Provides types and functions for widgets such as titles, buttons, etc

typedef struct button {
    char* text; // text to display inside button
    int width;  // width of the button 
    bool sel;   // whether button is selected by cursor
} button_t;

typedef struct title {
    char* text; // text for title 
    int width;  // width of the button
} title_t;

typedef struct body {
    char* text; // body text
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
    char* fgbutton_sel;
    char* bgbutton_sel;
    char* fgbutton_def;
    char* bgbutton_def;

    char* fgtitle;
    char* bgtitle;

    char* fgbody;
    char* bgbody;

} widget_t;

// helper functions below
// TODO want to create some helpers for creating default struct, etc
// need to think about whether I want to dynamically allocate widget_t,
// or if its small enough that copying to new stack frame is not that labor intensive

