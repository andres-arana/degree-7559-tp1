#ifndef __RAII__TEMP_FILE__H_INCLUDED__
#define __RAII__TEMP_FILE__H_INCLUDED__

#include <string>

namespace raii {
  class temp_file {
    public:
      explicit temp_file(const std::string &path);

      explicit temp_file(const temp_file& other) = delete;
      temp_file &operator=(const temp_file& other) = delete;

      explicit temp_file(temp_file &&other) = delete;
      temp_file &operator=(temp_file &&other) = delete;

      ~temp_file();

    private:
      std::string file_path;
  };
}

#endif
