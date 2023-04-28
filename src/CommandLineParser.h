#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

using namespace std;

class CommandLineOption {
    public:
    CommandLineOption(int numArgs);
    CommandLineOption();
    CommandLineOption& operator=(CommandLineOption& option);

    int getNumArgs();
    void setNumArgs(int numArgs);
    
    private:
    int _numArgs;
    std::vector<string> args;
};

class CommandLineParser {
    public:
    CommandLineParser(int argc, char** argv, string fOptions);

    private:
    std::map<string, CommandLineOption> _options;

    void findOptions(string fOptions);
    std::vector<string> parseCommandLineArgs(string argvString);
};