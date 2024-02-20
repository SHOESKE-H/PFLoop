#define DEBUG 1

#include <iostream>
#include <cstring>
#include <src/Arguments/Arguments.hpp>
#include <src/Video/VideoReader.hpp>
#include <src/Video/Frame.hpp>

inline void log([[maybe_unused]] const std::string& t_logMsg)
{
#if DEBUG
    std::cerr << t_logMsg << '\n';
#endif
}

[[noreturn]] void usage(void)
{
    std::cout << "Usage: perfectloop [OPTIONS]\n" <<
        "Options:\n" <<
        "    --help | -H                          | Diplays the usage of this tool.\n" <<
        "    --input | -i [Input Video]           | Specifies the input video.\n" <<
        "    --output | -o [Output Video]         | Specifies the output video.\n";

    exit(0);
}

int main(int argc, const char** argv)
{
    try {
        log("Entered main func");

        if (argc == 1) // No arguments specified
            usage();

        Arguments args(argc, argv);
    
        log("Arguments: ");
        log("\tHelp?: " + std::to_string(args.arg(Arguments::Type::Help).m_state == Arguments::State::Existent));
        log("\tInput file: " + args.arg(Arguments::Type::InputFile).m_value);
        log("\tOutput file: " + args.arg(Arguments::Type::OutputFile).m_value);

        if (args.arg(Arguments::Type::Help).m_state == Arguments::State::Existent)
            usage();
        
        VideoReader vReader(args.arg(Arguments::Type::InputFile).m_value);
        std::vector<Frame> frames = vReader.extractFrames();
        std::cout << "Number of frames of input file \"" << args.arg(Arguments::Type::InputFile).m_value << "\": " << frames.size() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }

    exit(0);
}
