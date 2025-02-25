#include "type_test_basic.hpp"
#include "rawterm.h"
#include "rawterm_utils.h"

#include <iostream>

TypeTestBasic::TypeTestBasic() {
    std::cout << "Created TypeTestBasic instance" << std::endl;
}

TypeTestBasic::~TypeTestBasic() {
    std::cout << "Destroyed TypeTestBasic instance" << std::endl;
}

void run() {

    std::string model = "User should type this out!";
    
    char input;

    clear_terminal();

    // TODO might have to change this here
    std::cout << model << "\r\n" << std::flush;

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

    std::cout << "\r\nDone\r\n" << std::endl;

}