#include "Engine/Logging/FileSink.hpp"

#include "Engine/Exceptions/FileException.hpp"

void Engine::Logging::FileSink::setFile(const std::filesystem::path & path)
{
    try {
        _file.open(path, std::ios_base::trunc);
    } catch (const std::ifstream::failure & e) {
        throw FileException(e.what());
    }
}

void Engine::Logging::FileSink::log(const std::string & message)
{
    _file << message << std::endl;
}
