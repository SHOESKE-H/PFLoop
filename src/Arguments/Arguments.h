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
        Unknown,
        Exists
    } State;

    typedef enum
    {
        Help,
        InputFile,
        OutputFile
    } Arg;

    State arg(const Arg& t_argument, std::string& t_des) const noexcept
    {
        if (!m_argv.count(t_argument))
            return State::Unknown;

        t_des = m_argv.at(t_argument);

        return State::Exists;
    }

    State arg(const Arg& t_argument) const noexcept
    {
        return static_cast<State>(m_argv.count(t_argument));
    }

private:
    static constexpr char m_defaultOutputFileNameAppendix[] = "-perfect-loop";

    static std::unordered_map<Arg, std::string> parse(const int& t_argc, const char** t_argv)
    {
        std::unordered_map<Arg, std::string> map;
        map.reserve(t_argc);

        const std::unordered_map<std::string, std::pair<bool, Arg>> args =
        {
            {"--help", {false, Arg::Help}},
            {"-H", {false, Arg::Help}},
            {"--input", {true, Arg::InputFile}},
            {"-i", {true, Arg::InputFile}},
            {"--output", {true, Arg::OutputFile}},
            {"-o", {true, Arg::OutputFile}}
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
        if (map.count(Arg::InputFile) && !map.count(Arg::OutputFile))
        {
            size_t fileExtensionLoc = map.at(Arg::InputFile).find_last_of('.');
            std::string outputFile = "";
            if (fileExtensionLoc != std::string::npos)
            {
                std::string outputFile(map.at(Arg::InputFile).substr(0, fileExtensionLoc) +
                        m_defaultOutputFileNameAppendix +
                        map.at(Arg::InputFile).substr(fileExtensionLoc));
                map.insert({Arg::OutputFile, outputFile});
            } else {
                throw BadInputFileException("Input file does not have a file extension.");
            }
        }

        return map;
    }

    std::unordered_map<Arg, std::string> m_argv;
};

#endif // ARGUMENTS_H
