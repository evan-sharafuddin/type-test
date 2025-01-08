// header for typing test menu 

#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>

#include "type_test_interface.hpp"
#include "main_menu.hpp"
#include "type_test_basic.hpp"

class Terminal {

public:
    Terminal();
    ~Terminal();

private:
    MainMenu main_menu;
    TypeTestInterface* type_test; // dynamically bound


};




#endif // TERMINAL_HPP