
#include "type_test_interface.hpp"
#include "type_test_basic.cpp"
#include "main_menu.cpp"
#include "terminal.cpp"

#include "rawterm_utils.c"

int main() {
    Terminal t;
    MainMenu mm;
    TypeTestInterface* tt = new TypeTestBasic();

    // this doesn't really do anything right now
    t.main_menu = mm;
    t.type_test = tt;

    delete tt;
}