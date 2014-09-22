#ifndef __UTIL_SFORMAT_H_INCLUDED__
#define __UTIL_SFORMAT_H_INCLUDED__

/** @file
 *
 * @brief Defines typesafe string formatting functions to use in logging
 */

#include <string>
#include <sstream>

namespace util {

  /** Base case for the util::sformat() function when no additional arguments
   * are provided. This function is used in recursive parameter expansion as
   * the base, parameterless control case. This means that the string being
   * passed in is returned without changes.
   *
   * @param[in] format A format string with no placeholders.
   *
   * @return A copy of the original format string.
   */
  std::string sformat(const std::string &format);

  /** Generic, typesafe function which applies formatting to a control format
   * string, replacing any '$' characters in the string with the stringified
   * version of the values passed in. This is a recursive function, which takes
   * the format string, replaces the first ocurrence of the control character
   * with the stringified version of the first argument, and recursively
   * invokes itself.
   *
   * For example:
   *
   * ~~~
   * util::sformat("This $ a $ string with a number: $", "is" "control", 15);
   * // Will produce "This is a control string with a number: 15"
   * ~~~
   *
   * @tparam T the type of the first parameter value.
   * @tparam Ts variadic parameter with the rest of the values to replace.
   *
   * @param format the format string to process. It should contain one '$'
   * character for each value provided.
   * @param value the first value to replace in the format string.
   * @ts the rest of the values to replace in the format string.
   *
   * @return A new string, having replaced al '$' characters with the string
   * representation of each of the values.
   */
  template<typename T, typename... Ts>
  std::string sformat(
      const std::string &format,
      const T& value,
      const Ts&... ts) {

    std::stringstream value_as_string;
    value_as_string << value;

    std::string new_format(format);
    new_format.replace(format.find_first_of('$'), 1, value_as_string.str());

    return sformat(new_format, ts...);
  }

};

#endif
