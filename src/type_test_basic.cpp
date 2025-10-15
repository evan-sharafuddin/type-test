#include "type_test_basic.hpp"
#include "rawterm.h"
#include "rawterm_utils.h"
#include "rawterm_widgets.h"

#include <iostream>
#include <chrono>
#include <thread>

TypeTestBasic::TypeTestBasic() {
    // std::cout << "Created TypeTestBasic instance" << std::endl;
    enable_raw_mode();
    clear_terminal();
    #define PAD 1

    main_menu = init_widget();
    add_button( main_menu, "Play Game", PAD );
    add_button( main_menu, "Quit"     , PAD );
    set_title( main_menu, "Welcome to Type Test!", PAD );

    stats_page = init_widget();
    add_button( stats_page, "Continue", PAD );
    set_title( stats_page, "Game Stats", PAD );
}

TypeTestBasic::~TypeTestBasic() {
    // std::cout << "Destroyed TypeTestBasic instance" << std::endl;
    free_widget( main_menu );
    free_widget( stats_page );
    
    show_cursor();
    clear_terminal();
    move_cursor_home();
    disable_raw_mode();
}

void TypeTestBasic::play_mult() {
    // repeatively prompt menu until user enters quit
    while ( menu() );

}

bool TypeTestBasic::menu() {

    // create buttons using rawterm_widgets
    prompt_buttons( main_menu );

    if ( main_menu->buttons[0].sel ) {
        run();
        return true;
    }
    else {
        return false;
    }
}

int TypeTestBasic::run() {

    std::string model = "User should type this out!";
    
    char input;

    std::string ENDL = "\r\n";
    std::cout << "Welcome to type test!" << ENDL << std::flush;
    std::cout << model << ENDL << ENDL << std::flush;

    int mistake_cnt = 0;
    // int test_cnt = 0;
    int total_mistakes = 0;

    auto it = model.begin();

    // make some room in the terminal!
    move_cursor_down(5);
    move_cursor_up(5);

    while ( true ) {

        if ( read( STDIN_FILENO, &input, 1 ) == -1 && errno != EAGAIN )
            die("read");

        if ( input == 'q' ) {
            return -1; // terminated game early
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
            total_mistakes++;
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

    clear_terminal();
    move_cursor_home();

    return total_mistakes;

}