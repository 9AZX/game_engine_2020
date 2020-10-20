#pragma once

#ifndef Core_HPP_
#define Core_HPP_

#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <stdint.h>

class Core
{
public:
    Core(std::string gameName);

    void init() const noexcept;

private:
    const std::string _gameName = "";
}; /* class Core */

#endif /* Core_HPP_ */
