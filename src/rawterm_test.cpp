#include <iostream>
#include <string>
#include "rawterm.h"
#include "rawterm_utils.h"


int main() {
    
    
    std::cout << "Type a key to make stuff happen...\r\n" << std::flush;

    enable_raw_mode();

    char input;

    while ( true ) {

        if ( read( STDIN_FILENO, &input, 1 ) == -1 && errno != EAGAIN )
            die("read");

        // when here, input has been read
        out( &input );

    }

}