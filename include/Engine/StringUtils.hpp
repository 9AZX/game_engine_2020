#ifndef ENGINE_STRING_UTILS_HPP_
#define ENGINE_STRING_UTILS_HPP_

#include <string>
#include <vector>

namespace Engine {

extern std::vector<std::string> splitString(
    const std::string & string,
    const std::string & delimiters
) noexcept;

extern void lTrimString(std::string & string) noexcept;
extern void rTrimString(std::string & string) noexcept;
extern void trimString(std::string & string) noexcept;
extern std::string lTrimString(const std::string & string) noexcept;
extern std::string rTrimString(const std::string & string) noexcept;
extern std::string trimString(const std::string & string) noexcept;

} /* namespacce Engine */

#endif /* ENGINE_STRING_UTILS_HPP_ */
