#include "CommandLineParser.h"
/*

    This constructor uses the arguments, number of arguments, and a formated
    string of options to parse the command line arguments and store their 
    arguments.

*/
CommandLineParser::CommandLineParser(int argc, char** argv, string fOptions) {
    // Parse the fOptions string for options to look for 
    try {
        findOptions(fOptions);
    }
    catch (const invalid_option_format e) {
        cout << e.what() << endl;
        exit(-1);
    }

    // combine args back into string
    string temp;
    for (int i = 1; i < argc; i++) {
        temp = temp + argv[i] + " ";
    }    
    // remove final space char
    temp.pop_back();

    // Check if the given command line args are formatted right
    std::regex match_str("^(-[\\w]+([\\w .])*)*$");
    std::smatch base_match;

    // If not formatted correct, throw exception
    if (!std::regex_match(temp, base_match, match_str)) {
        throw invalid_commandline_format("string '" + temp + "' is formatted wrong");
    }

    // Grab list of command line options and their args and put them in vector
    vector<string> command_line_args = parseCommandLineArgs(temp);

    // parse through the options and seporate the args
    // Make sure the arg is in map and if it is check
    // that it has the expected amount of args
    for (auto each : command_line_args) {
        string temp;
        stringstream temp_stream(each);
        vector<string> arg_pieces;

        // split option and args by spaces
        while (getline(temp_stream, temp, ' ')) {
            arg_pieces.push_back(temp);
        }

        // check if option is in map
        if (_options.find(arg_pieces[0]) != _options.end()) {
            // Option is in map
            if ((arg_pieces.size() - 1) == _options[arg_pieces[0]].getNumArgs()) {
                _options[arg_pieces[0]].setSeen();
                // option has expected amount of args
                for (int i = 1; i < arg_pieces.size(); i++) {
                    _options[arg_pieces[0]].push_arg(arg_pieces[i]);
                }
            }
            else {
                // option does not have expected amount of args
                throw invalid_commandline_arg_count("argument '" + arg_pieces[0] + "' does not have " 
                                                    + std::to_string(_options[arg_pieces[0]].getNumArgs()) + " args");
            }
        }
        else {
            // option is not in map
            throw invalid_commandline_arg("argument '" + arg_pieces[0] + "' not found in map");
        }

    }
    
}

void CommandLineParser::findOptions(string fOptions) {

    std::regex options_test("^(-([\\w]+\\[[\\d]+\\])+)+$");
    std::smatch base_match;

    // If not formatted correct, throw exception
    if (!std::regex_match(fOptions, base_match, options_test)) {
        throw invalid_option_format("user format string '" + fOptions + "' is formatted wrong");
    }

    // Vars for splitting the options string
    string temp;
    stringstream temp_stream(fOptions);
    std::vector<string> split_options;

    // Split the string into the argument descriptors using '-'
    while (getline(temp_stream, temp, '-')) {
        split_options.push_back(temp);
    }

    // Get rid of the empty string at the start if there is somthing in the string
    if (split_options.size() > 0) {
        split_options.erase(split_options.begin());
    }

    // Split the options into their parts and store them
    for (auto each : split_options) {
        //cout << "|" << each << "|"<< endl;  // Debugging stuff
        temp_stream = stringstream(each);
        std::vector<string> tokened_option;
        while (getline(temp_stream, temp, '[')) {
            //cout << "   |" << temp << "|"<< endl; // Debugging stuff
            tokened_option.push_back(temp);
        }
        // remove residual ']'
        tokened_option[1].pop_back();
        // Add to map
        _options[tokened_option[0]].setNumArgs(stoi(tokened_option[1]));
    }
}

std::vector<string> CommandLineParser::parseCommandLineArgs(string argvString) {
    string temp;
    stringstream temp_stream(argvString);
    std::vector<string> split_options;

    // Split the string into the argument descriptors using '-'
    while (getline(temp_stream, temp, '-')) {
        split_options.push_back(temp);
    }

    // Get rid of the empty string at the start if there is somthing in the string
    if (split_options.size() > 0) {
        split_options.erase(split_options.begin());
    }

    return split_options;
}


// Command line option class implementations 

CommandLineOption::CommandLineOption() {
    _numArgs = 0;
}

CommandLineOption::CommandLineOption(int numArgs) {
    _numArgs = numArgs;
}

CommandLineOption& CommandLineOption::operator=(CommandLineOption& option) {
    if (this != &option) {
        _numArgs = option.getNumArgs();
    }
    return *this;
}

int CommandLineOption::getNumArgs() {
    return _numArgs;
}

void CommandLineOption::setNumArgs(int numArgs) {
    _numArgs = numArgs;
}