#include <iostream>
#include "CommandLineParser.h"

using namespace std;

int main(int argc, char** argv)
{
    CommandLineParser test;
    Options option;
    Options option2;
    option.setOption("-o");
    Arguments optionarg;
    optionarg.setName("test");
    option.addArgument(optionarg);
    test.addOption(option);

    option2.setOption("-r");
    Arguments option2arg;
    option2arg.setName("test2");
    option2.addArgument(option2arg);
    test.addOption(option2);

    cout << argv[0] << endl;
    test.parse(argc, argv);
    test.debugDisplay();
    return 1;
}