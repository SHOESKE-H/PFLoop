#define DEBUG 1

#include <iostream>
#include <cstring>
#include "src/Arguments/Arguments.h"

void log([[maybe_unused]] const std::string& t_logMsg) {
#if DEBUG
    std::cerr << t_logMsg << '\n';
#endif
    return;
}

void usage(const bool& shouldExit) {
    std::cout << "Usage: perfectloop [OPTIONS]\n" <<
        "Options:\n" <<
        "\t--help | -H\n" <<
        "\t\tDiplays the usage of this tool. (incompatible with every other argument)\n" <<
        "\t--input | -i [Input Video]\n" <<
        "\t\tSpecifies the input video to fix the loop of.\n" <<
        "\t--output | -o [Output Video]\n" <<
        "\t\tSpecifies the final video to write to.\n";

    if (shouldExit)
        exit(0);

    return;
}

int main(int argc, const char** argv) {
    try {
        log("Entered main func");

        if (argc == 1)
            usage(true);

        Arguments args(argc, argv);
    
        log("Arguments: ");
        std::string tmp;
        bool btmp;
        btmp = args.arg(Arguments::Arg::Help, tmp);
        log("\tHelp?: " + std::to_string(btmp == Arguments::State::Exists));
        args.arg(Arguments::Arg::InputFile, tmp);
        log("\tInput file: " + tmp);
        args.arg(Arguments::Arg::OutputFile, tmp);
        log("\tOutput file: " + tmp);
    
        if (args.arg(Arguments::Arg::Help) == Arguments::State::Exists)
            usage(true);

        // Do stuff with acquiered arguments
        // ...
    } catch (std::exception& e) {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }

    exit(0);
}