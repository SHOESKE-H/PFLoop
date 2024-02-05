#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include "src/Arguments/BadInputFileException.h"

class Arguments
{
public:
    Arguments() noexcept
        : m_argv{} {}
    Arguments(const int& t_argc, const char** t_argv) noexcept
        : m_argv(parse(t_argc, t_argv)) {}

    int count() const noexcept
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
        Arg()
            : type(Type::Unknown), state(State::Nonexistant), value() {}

        Type type;
        State state;
        std::string value;
    };

    Arg arg(const Type& t_argument) const noexcept
    {
        Arg argument;
        argument.type = t_argument;
        argument.state = (State) (m_argv.count(t_argument) == State::Existent);

        if (argument.state == State::Nonexistant)
            return argument;
        else
            argument.value = m_argv.at(t_argument);

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
        for (int i = 0; i < t_argc; i++)
        {
            std::string iStr(t_argv[i]);
            if (args.count(iStr))
            {
                map.insert(std::make_pair(args.at(iStr).second, args.at(iStr).first ? t_argv[++i] : ""));
            }
        }

        // Init missing args with defaults
        if (map.count(Type::InputFile) && !map.count(Type::OutputFile))
        {
            size_t fileExtensionLoc = map.at(Type::InputFile).find_last_of('.');
            std::string outputFile = "";
            if (fileExtensionLoc != std::string::npos)
            {
                std::string outputFile(map.at(Type::InputFile).substr(0, fileExtensionLoc) +
                        m_defaultOutputFileNameAppendix +
                        map.at(Type::InputFile).substr(fileExtensionLoc));
                map.insert({Type::OutputFile, outputFile});
            } else {
                throw BadInputFileException("Input file does not have a file extension.");
            }
        }

        return map;
    }

    std::unordered_map<Type, std::string> m_argv;
};

#endif // ARGUMENTS_H
