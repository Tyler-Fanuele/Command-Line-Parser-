#include <iostream>
#include "CommandLineParser.h"

using namespace std;

int main(int argc, char** argv)
{
    try {
        CommandLineParser parser(argc, argv, "-o[2]-ff[0]");
        if (parser.seen("o")) {
            cout << "parser seen -o" << endl;
            std::vector<string> args = parser.optionContents("o");
            for (auto each : args) {
                cout << "   arg: " << each << endl;
            }
        }
    } 
    catch (const invalid_commandline_format e) {
        cout << e.what() << endl;
        exit(1);
    }
    catch (const invalid_commandline_arg e) {
        cout << e.what() << endl;
        exit(2);
    }
    catch (const invalid_commandline_arg_count e) {
        cout << e.what() << endl;
        exit(2);
    }

    

    
    return 0;
}