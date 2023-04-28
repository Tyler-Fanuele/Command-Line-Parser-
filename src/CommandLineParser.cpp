#include "CommandLineParser.h"
/*

    This constructor uses the arguments, number of arguments, and a formated
    string of options to parse the command line arguments and store their 
    arguments.

    step 1: parse the formatted option string and split it by the '-' token
    step 2: remove the empty string at the begining if you have options
    step 3: 

*/
CommandLineParser::CommandLineParser(int argc, char** argv, string fOptions) {
    findOptions(fOptions);

    // Debug message
    for (auto each : _options) {
        cout << "Option name: " << each.first << " Amount of args: " << each.second.getNumArgs() << endl;
    }

    string temp;
    for (int i = 1; i < argc; i++) {
        temp = temp + argv[i] + " ";
    }    
    temp.pop_back();
    //cout << "|" << temp << "|" << endl;

    std::regex match_str("^(-[\\w]+([\\w ])*)*$");
    std::smatch base_match;

    if (std::regex_match(temp, base_match, match_str)) {
        cout << "match" << endl;
    }
    else {
        throw std::invalid_argument("CommandLineParser - input arguments: (" + temp + ") are formatted wrong");
    }

    vector<string> command_line_args = parseCommandLineArgs(temp);

    for (auto each : command_line_args) {
        string temp;
        stringstream temp_stream(each);
        vector<string> arg_pieces;

        while (getline(temp_stream, temp, ' ')) {
            arg_pieces.push_back(temp);
        }
        for (auto e : arg_pieces) {
            cout << e << " | ";
        }
        cout << endl << "vector size = " << arg_pieces.size() << endl;

        if (_options.find(arg_pieces[0]) != _options.end()) {
            if ((arg_pieces.size() - 1) == _options[arg_pieces[0]].getNumArgs()) {
                cout << arg_pieces[0] << " found with enough args" << endl;
            }
            else {
                cout << arg_pieces[0] << " did not have enough args" << endl;
            }
        }
        else {
            cout << arg_pieces[0] << " not found in map" << endl;
        }

    }
    
}

void CommandLineParser::findOptions(string fOptions) {

    std::regex options_test("^(-([\\w]\\[[\\d]+\\])+)+$");


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