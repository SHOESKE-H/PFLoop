#ifndef PFLOOP_SRC_ARGUMENTS_ARGUMENTS_H
#define PFLOOP_SRC_ARGUMENTS_ARGUMENTS_H

#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include <src/Arguments/BadFileException.h>
#include <src/Arguments/ExpectedArgumentException.h>

class Arguments
{
public:
    Arguments(void) noexcept
        : m_argv{} {}
    Arguments(const int& t_argc, const char** t_argv) noexcept
        : m_argv(parse(t_argc, t_argv)) {}

    size_t count(void) const noexcept
    {
        return m_argv.size();
    }

    typedef enum
    {
        Nonexistant,
        Existent
    } State;

    typedef enum
    {
        Unknown,
        Help,
        InputFile,
        OutputFile
    } Type;
    
    struct Arg
    {
        public:
            Arg(void)
                : m_type(Type::Unknown), m_state(State::Nonexistant), m_value() {}

            Type m_type;
            State m_state;
            std::string m_value;
    };

    Arg arg(const Type& t_argument) const noexcept
    {
        Arg argument;
        argument.m_type = t_argument;
        argument.m_state = (State) (m_argv.count(t_argument) == State::Existent);

        if (argument.m_state == State::Nonexistant)
            return argument;
        else
            argument.m_value = m_argv.at(t_argument);

        return argument;
    }

private:
    static constexpr char m_defaultOutputFileNameAppendix[] = "-perfect-loop";

    static std::unordered_map<Type, std::string> parse(const int& t_argc, const char** t_argv)
    {
        std::unordered_map<Type, std::string> map;
        map.reserve(t_argc);

        const std::unordered_map<std::string, std::pair<bool, Type>> args =
        {
            {"--help", {false, Type::Help}},
            {"-H", {false, Type::Help}},
            {"--input", {true, Type::InputFile}},
            {"-i", {true, Type::InputFile}},
            {"--output", {true, Type::OutputFile}},
            {"-o", {true, Type::OutputFile}}
        };
        
        // Parse the arguments
        for (int i = 0; i < t_argc; i++) {
            if (args.count(t_argv[i])) {
                if (args.at(t_argv[i]).first && i >= t_argc - 1)
                    throw ExpectedArgumentException("Argument value expected, but reached end of argument list.");
                map.insert(std::make_pair(args.at(t_argv[i]).second, args.at(t_argv[i]).first ? t_argv[i + 1] : ""));
            }
        }

        // Init missing args with defaults
        size_t fileExtensionLocInputFile = 0;
        size_t fileExtensionLocOutputFile = 0;
        if (map.count(Type::InputFile))
            fileExtensionLocInputFile = map.at(Type::InputFile).find_last_of('.');

        if (map.count(Type::InputFile) && !map.count(Type::OutputFile)) {
            std::string outputFile = "";
            if (fileExtensionLocInputFile != std::string::npos && fileExtensionLocInputFile != map.at(Type::InputFile).size() - 1) {
                std::string outputFile(map.at(Type::InputFile).substr(0, fileExtensionLocInputFile) +
                        m_defaultOutputFileNameAppendix +
                        map.at(Type::InputFile).substr(fileExtensionLocInputFile));
                map.insert({Type::OutputFile, outputFile});
            } else {
                throw BadFileException("Input file does not have a file extension.");
            }
        }
        
        // Check final args
        if (map.count(Type::OutputFile))
            fileExtensionLocOutputFile = map.at(Type::OutputFile).find_last_of('.');
        if (map.count(Type::InputFile) && (fileExtensionLocInputFile == std::string::npos || fileExtensionLocInputFile == map.at(Type::InputFile).size() - 1))
            throw BadFileException("Input file does not have a file extension.");
        if (map.count(Type::OutputFile) && (fileExtensionLocOutputFile == std::string::npos || fileExtensionLocOutputFile == map.at(Type::OutputFile).size() - 1))
            throw BadFileException("Output file does not have a file extension.");

        return map;
    }

    std::unordered_map<Type, std::string> m_argv;
};

#endif // PFLOOP_SRC_ARGUMENTS_ARGUMENTS_H
