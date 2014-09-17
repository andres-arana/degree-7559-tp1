#ifndef __UTIL_SFORMAT_H_INCLUDED__
#define __UTIL_SFORMAT_H_INCLUDED__

#include <string>
#include <sstream>

namespace util {

  std::string sformat(const std::string &format);

  template<typename T, typename... Ts>
  std::string sformat(const std::string &format, const T& value, const Ts&... ts) {
    std::stringstream value_as_string;
    value_as_string << value;

    std::string new_format(format);
    new_format.replace(format.find_first_of('$'), 1, value_as_string.str());

    return sformat(new_format, ts...);
  }

};

#endif
