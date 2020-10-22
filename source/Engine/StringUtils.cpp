#include "Engine/StringUtils.hpp"

#include <algorithm>
#include <cctype>

std::vector<std::string> Engine::splitString(const std::string & string, const std::string & delimiters) noexcept
{
    if (string.empty()) {
        return std::vector<std::string>();
    }
    auto isDelimiter = [ delimiters ] (int value) {
        return std::find(
            delimiters.begin(),
            delimiters.end(),
            value
        ) != delimiters.end();
    };
    std::vector<std::string> elems;
    std::string::const_iterator current = string.begin();
    std::string::const_iterator end;

    while (current != string.end()) {
        current = std::find_if_not(current, string.end(), isDelimiter);
        end = std::find_if(current, string.end(), isDelimiter);
        elems.push_back(
            string.substr(
                current - string.begin(),
                end - current
            )
        );
        current = end;
    }
    return elems;
}

void Engine::lTrimString(std::string & string) noexcept
{
    string.erase(
        string.begin(),
        std::find_if(
            string.begin(),
            string.end(),
            [](unsigned char c) {
                return !std::isspace(c);
            }
        )
    );
}

void Engine::rTrimString(std::string & string) noexcept
{
    string.erase(
        std::find_if(
            string.rbegin(),
            string.rend(),
            [](unsigned char c) {
                return !std::isspace(c);
            }
        ).base(),
        string.end()
    );
}

void Engine::trimString(std::string & string) noexcept
{
    rTrimString(string);
    lTrimString(string);
}

std::string Engine::lTrimString(const std::string & string) noexcept
{
    std::string trimmedString = string;

    lTrimString(trimmedString);
    return trimmedString;
}

std::string Engine::rTrimString(const std::string & string) noexcept
{
    std::string trimmedString = string;

    rTrimString(trimmedString);
    return trimmedString;
}

std::string Engine::trimString(const std::string & string) noexcept
{
    std::string trimmedString = string;

    lTrimString(trimmedString);
    rTrimString(trimmedString);
    return trimmedString;
}
