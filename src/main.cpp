

#include <iostream>
#include "rawterm.h"

int main() {

    enable_raw_mode();

    std::string model = "User should type this out!";
    
    char input;

    std::string ENDL = "\r\n";
    std::cout << "Welcome to type test!" << ENDL << std::flush;
    std::cout << model << ENDL << ENDL << std::flush;

    for ( auto it = model.begin(); it != model.end(); ++it ) {

        if ( read( STDIN_FILENO, &input, 1 ) == -1 && errno != EAGAIN )
            die("read");

        if ( input == 127 ) {
            write(STDOUT_FILENO, "\b\x1b[1P", 5);
            
            if ( it == model.begin() ) {
                --it;
            }
            else {
                it -= 2;
            }
            
            continue;
        }

        if ( input != *it ) { // set text to red
            write(STDOUT_FILENO, "\x1b[1;31m", 7);
        }

        write(STDOUT_FILENO, &input, 1);

        if ( input != *it ) { // set text to default
            write(STDOUT_FILENO, "\x1b[0m", 4);
        }

        if ( input == 'q' ) {
            break;
        }
    }

    printf("\r\n");

    return 0;
}