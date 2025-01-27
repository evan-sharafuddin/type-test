// first instance of a typing test
// trying to keep things simple here

#ifndef TYPE_TEST_BASIC_HPP
#define TYPE_TEST_BASIC_HPP

#include <string>
#include <fstream>

class TypeTestBasic : public TypeTestInterface {

public:
    TypeTestBasic();
    ~TypeTestBasic();

    void run();

private:
    std::ifstream prompt_bank;
    std::string prompt;

};


#endif // TYPE_TEST_BASIC_HPP