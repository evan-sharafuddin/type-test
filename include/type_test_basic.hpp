// ditching the inheritance for now

#ifndef TYPE_TEST_BASIC_HPP
#define TYPE_TEST_BASIC_HPP

#include <string>
#include <fstream>
#include "rawterm_widgets.h"

class TypeTestBasic {

public:
    TypeTestBasic();
    ~TypeTestBasic();

    void play_mult();
    bool menu();
    void run();

private:
    std::ifstream prompt_bank;
    std::string prompt;
    bool game_is_started;
    widget_t* main_menu;

};


#endif // TYPE_TEST_BASIC_HPP