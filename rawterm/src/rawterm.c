
#include "rawterm.h"

static struct termios orig;

// use this for error checking
// if you pipe in or use "<" when calling the executable from the command line
// the program will use those as the standard input, resulting in errors from tcgetattr()
// and tcsetattr()
void die( const char *s ) {
    perror(s); // prints error message based on errno value returned
    exit(1);
}

void disable_raw_mode() {
    if ( tcsetattr( STDIN_FILENO, TCSAFLUSH, &orig ) == -1 )
        die( "tcsetattr" );
}

void enable_raw_mode() {

    // ensure that we restore the original terminal when the program calls an exit signal
    atexit( disable_raw_mode );

    // get the flags for the stdin stream of this programs terminal
    // NOTE: all terminal sessions have three streams
    // (1) stdin (buffered) (2) stdout (buffered) (3) stderr (not buffered)
    if ( tcgetattr( STDIN_FILENO, &orig ) == -1 ) 
        die( "tcgetattr" );

    // create copy termios struct for our raw terminal
    struct termios raw = orig;
    
    // termios has four sets of flags
    // input, output, control and local 
    // refer to the documentation to see what flags are available in each
    // NOTE: think of the flag as having multiple flags in one. Each bit at a 
    // certain position represents a specific flag

    // managing local flags
    raw.c_lflag &= ~( 
                      ECHO   | // disables echo
                      ICANON | // disables canonical mode
                      ISIG   |  // disables signals such as SIGINT and SIGTSP
                      IEXTEN | // disables Ctrl-V (prints following character literally)
                      BRKINT | // disable break conditions from sending SIGINT
                      INPCK  | // disables parity checking
                      ISTRIP  // disables stripping of 8th byte (likely related to parity)
                    ); 


    raw.c_iflag &= ~( 
                      IXON | // disables Ctrl-S and Ctrl-Q "software flow control"
                      ICRNL  // disables conversion of input \r to \n
                    ); 

    
    raw.c_oflag &= ~(
                      OPOST // disables output processing (i.e., \n to \r\n)
                            // NOTE: with this disabled, you must specifiy \r\n to get proper new line behavior
                    );  

    raw.c_cflag |= (CS8); // bit mask setting character size to 8 bits per byte 

    // set timeout for read()
    // these are "control characters", or arrays of bytes
    raw.c_cc[VMIN] = 1; // add pause so it doesnt skip read() // can read input immediately
    // raw.c_cc[VTIME] = 10; // max amount of time before read() returns -- in 10ths of a second

    // write these attributes
    // NOTE: TCSAFLUSH indicates how/when we set the attribute:
    // "it waits for all pending output to be written to the terminal, 
    // and also discards any input that hasn’t been read."
    if ( tcsetattr( STDIN_FILENO, TCSAFLUSH, &raw ) == -1 ) 
        die( "tcsetattr" );

}