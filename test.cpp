// testing out some of the ANSI control sequence stuff

#include <iostream>
#include <string>

#include <unistd.h> // Linux, need to have <windows.h> for Windows

using namespace std;

int main() {
    cout << "Testing out some ANSI escape sequences..." << endl;

    // define some constants
    string ESC = "\x1b";
    cout << ESC << "[1;31m" << "red " << ESC << "[0m" << "normal" << endl;

    cout << "in 100 ms, remove only the red text" << flush;
    cout << ESC << "[?25l" << flush; // make cursor invisible
    // different color outputs
    sleep(1);

    // move cursor to end of red
    cout << "\r" << flush;
    cout << ESC << "[1A" << flush << ESC << "[3C" << flush;

    // pause 
    sleep(1);

    // erase the red text, then pause
    cout << ESC << "[1K" << flush;
    cout << "\n" << endl;
    sleep(1);

    // make cursor visible
    cout << ESC << "[?25h" << flush;
    // experiment with faded text
    cout << "Printing out some faded text" << endl;
    cout << ESC << "[2m" << "This should be faded " << ESC << "[22m" << "This should not" << endl;
    cout << ESC << "[9m" << "What is blinking mode??" << endl;
    sleep(1);
    cout << ESC << "[29m" << flush;
    cout << "more text" << endl;
    cout << "done!" << endl;



    
    
    

    return 0;
}