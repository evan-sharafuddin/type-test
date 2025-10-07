// compile this to create a functioning version of the type test game

#include <iostream>
#include <string>
#include "rawterm.h"
#include "rawterm_utils.h"


int main() {

    enable_raw_mode();
    // setvbuf(stdout, NULL, _IONBF, 0);  // disables buffering

    std::string model = "User should type this out!";
    
    char input;

    std::string ENDL = "\r\n";
    std::cout << "Welcome to type test!" << ENDL << std::flush;
    std::cout << model << ENDL << ENDL << std::flush;

    int mistake_cnt = 0;
    // int test_cnt = 0;

    auto it = model.begin();

    // make some room in the terminal!
    move_cursor_down(5);
    move_cursor_up(5);

    while ( true ) {

        if ( read( STDIN_FILENO, &input, 1 ) == -1 && errno != EAGAIN )
            die("read");

        if ( input == 'q' ) {
            break;
        }
        
        if ( input == 127 ) {
            clear_char();
            
            if (mistake_cnt > 0) { // only need to keep track of the mistake count, don't need to increment counter
                mistake_cnt--;
                it--;

                if (mistake_cnt == 0) {
                    foreground_color("default");
                }
            }
            else if ( it == model.begin() ) { // don't want to go out of bounds, keep the 
                // --it;
                continue;
            }
            else {
                // it -= 2;
                it--;
            }


            
            // // print out some debug stuff
            char c = *it;
            std::string one_char_str(1, c);       // C++ string with one character
            const char* cstr = one_char_str.c_str(); // const char* of that string
            save_cursor();
            move_cursor_down(1);
            clear_line();
            out( cstr );
            restore_cursor();

                    // maximum length for an int as string: -2147483648 → 11 chars + '\0'
            char buf[12];
            int len = snprintf(buf, sizeof(buf), "%d", mistake_cnt);
            // if (len < 0) return -1;       // error
            // return out(buf);               // call your existing out()
            save_cursor();
            move_cursor_down(2);
            clear_line();
            out( buf );
            restore_cursor();

   
            continue;
        }

            
        if ( input != *it || mistake_cnt > 0 ) { // set text to red
            // write(STDOUT_FILENO, "\x1b[1;31m", 7);
            foreground_color("red");
            mistake_cnt++;
        }
        else {
            foreground_color("default");
            // write(STDOUT_FILENO, "\x1b[0m", 4);
        }

        char input_cstr [2];
        input_cstr[0] = input;
        input_cstr[1] = '\0';
        out( input_cstr );

        // print out some debug stuff
        char c = *it;
        std::string one_char_str(1, c);       // C++ string with one character
        const char* cstr = one_char_str.c_str(); // const char* of that string
        save_cursor();
        move_cursor_down(1);
        clear_line();
        out( cstr );
        restore_cursor();

        // maximum length for an int as string: -2147483648 → 11 chars + '\0'
        char buf[12];
        int len = snprintf(buf, sizeof(buf), "%d", mistake_cnt);
        save_cursor();
        move_cursor_down(2);
        clear_line();
        out( buf );
        restore_cursor();
    


        // iterate model iterator depending on correctness or whether user has completed the model
        if ( it+1 == model.end() && mistake_cnt == 0 ) {
            break;
        }
        else {
            it++;
        }
    }

    printf("\r\n");
    
    clear_terminal();
    move_cursor_home();
    return mistake_cnt;
}
