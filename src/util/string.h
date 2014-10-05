#ifndef __UTIL__STRING_H_INCLUDED__
#define __UTIL__STRING_H_INCLUDED__

/** @file
 *
 * @brief Funciones generales y de tipos seguros para el manejo de strings.
 */

#include <string>
#include <sstream>
#include <vector>

namespace util {
  template<typename T>
  std::string string_cast(const T &value) {
    std::stringstream result;
    result << value;
    return result.str();
  }

  std::string sformat(const std::string &format);

  template<typename T, typename... Ts>
  std::string sformat(
      const std::string &format,
      const T& value,
      const Ts&... ts) {

    std::string new_format(format);
    new_format.replace(format.find_first_of('$'), 1, string_cast(value));

    return sformat(new_format, ts...);
  }

  std::vector<std::string> svector(std::vector<std::string> out);

  template<typename T, typename... Ts>
  std::vector<std::string> svector(
      std::vector<std::string> out,
      const T& value,
      const Ts&... ts) {

    out.push_back(string_cast(value));
    return svector(std::move(out), ts...);
  }

  template<typename T, typename... Ts>
  std::vector<std::string> svector(const T& value, const Ts&... ts) {
    std::vector<std::string> result { string_cast(value) };
    return svector(std::move(result), ts...);
  }
}

#endif
