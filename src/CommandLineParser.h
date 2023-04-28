#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <cstring>

using namespace std;

class CommandLineOption {
    public:
    CommandLineOption(int numArgs);
    CommandLineOption();
    CommandLineOption& operator=(CommandLineOption& option);

    int getNumArgs();
    void setNumArgs(int numArgs);

    std::vector<string> getArgs() {return args;}

    void push_arg(string arg) { args.push_back(arg); }
    
    private:
    int _numArgs;
    std::vector<string> args;
};

class CommandLineParser {
    public:
    CommandLineParser(int argc, char** argv, string fOptions);

    bool seen(string option) { return _options.find(option) != _options.end(); }
    std::vector<string> optionContents(string option) {return _options.at(option).getArgs(); }

    private:
    std::map<string, CommandLineOption> _options;

    void findOptions(string fOptions);
    std::vector<string> parseCommandLineArgs(string argvString);
};

class invalid_commandline_format{
    string msg;
    public:
    invalid_commandline_format(string message) : msg(message) {}
    const string what () const{
        return "invalid command line format - " + msg;
    }
};

class invalid_commandline_arg{
    string msg;
    public:
    invalid_commandline_arg(string message) : msg(message) {}
    const string what () const{
        return "invalid command line argumemnt - " + msg;
    }
};

class invalid_commandline_arg_count{
    string msg;
    public:
    invalid_commandline_arg_count(string message) : msg(message) {}
    const string what () const{
        return "invalid command line argumemnt count - " + msg;
    }
};