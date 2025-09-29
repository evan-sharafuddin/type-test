

#include <iostream>
#include <string>
#include "rawterm.h"
#include "rawterm_utils.h"


int main() {

    enable_raw_mode();

    std::string model = "User should type this out!";
    
    char input;

    std::string ENDL = "\r\n";
    std::cout << "Welcome to type test!" << ENDL << std::flush;
    std::cout << model << ENDL << ENDL << std::flush;

    int mistake_cnt = 0;
    // int test_cnt = 0;

    auto it = model.begin();

    while ( true ) {

        if ( read( STDIN_FILENO, &input, 1 ) == -1 && errno != EAGAIN )
            die("read");

        if ( input == 127 ) {
            clear_char();
            
            // if ( it == model.begin() ) {
            //     --it;
            // }
            // else {
            //     it -= 2;

            // }

            // if (mistake_cnt > 0) {
            //     mistake_cnt--;
            // }
            
            // // print out some debug stuff
            // char c = *it;
            // std::string one_char_str(1, c);       // C++ string with one character
            // const char* cstr = one_char_str.c_str(); // const char* of that string
            // int prevcol  = get_col();
            // move_cursor_down(1);
            // clear_line();
            // std::string num = std::to_string( prevcol );
            // out( num.c_str() );  

            // int curcol = get_col();
            // if (prevcol == curcol) {}
            // else if ( prevcol > curcol )
            //     move_cursor_right(prevcol - curcol);
            // else
            //     move_cursor_left(curcol - prevcol);
            // move_cursor_up(1);    


            continue;
        }


        if ( input == 'r' ) 
            foreground_color("red");
        if ( input == 'b' )
            foreground_color("black");
            
        // if ( input != *it || mistake_cnt > 0 ) { // set text to red
        //     // write(STDOUT_FILENO, "\x1b[1;31m", 7);
        //     foreground_color("red");
        //     mistake_cnt++;
        // }
        // else {
        //     foreground_color("black");
        //     // write(STDOUT_FILENO, "\x1b[0m", 4);
        // }

        // write(STDOUT_FILENO, &input, 1);
        char input_cstr [2];
        input_cstr[0] = input;
        input_cstr[1] = '\0';
        out( input_cstr );

        if ( input == 'q' ) {
            break;
        }

        // print out some debug stuff
        char c = *it;
        std::string one_char_str(1, c);       // C++ string with one character
        const char* cstr = one_char_str.c_str(); // const char* of that string
        int prevcol  = get_col();
        save_cursor();
        move_cursor_down(1);
        clear_line();
        std::string num = std::to_string( prevcol );
        out( num.c_str() );  
        restore_cursor();
        // int curcol = get_col();
        // if (prevcol == curcol) {}
        // else if ( prevcol > curcol )
        //     move_cursor_right(prevcol - curcol);
        // else
        //     move_cursor_left(curcol - prevcol);
        // move_cursor_up(1);   



        // // iterate model iterator depending on correctness or whether user has completed the model
        // if ( it == model.end() && mistake_cnt > 0 ) {

        //     it--;
        // }
        // else if ( it == model.end() ) {
        //     break;
        // }
        // else {
        //     it++;
        // }
        // move_cursor_right(1);
    }

    printf("\r\n");
    

    return mistake_cnt;
}
