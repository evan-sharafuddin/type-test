// ditching the inheritance for now

#ifndef TYPE_TEST_BASIC_HPP
#define TYPE_TEST_BASIC_HPP

#include <string>
#include <fstream>

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

};


#endif // TYPE_TEST_BASIC_HPP