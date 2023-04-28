#include <iostream>
#include "CommandLineParser.h"

using namespace std;

int main(int argc, char** argv)
{
    try {
        CommandLineParser parser(argc, argv, "-o[2]-ff[0]");
    } 
    catch (const invalid_argument e) {
        cout << e.what() << endl;
        exit(1);
    }

    
    return 0;
}