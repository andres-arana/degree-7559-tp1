#ifndef __RAII__AUTO_FILE_LOCK_H_INCLUDED__
#define __RAII__AUTO_FILE_LOCK_H_INCLUDED__

#include <string>

namespace raii {
  class auto_file_lock {
    public:
      auto_file_lock();
      explicit auto_file_lock(int file_descriptor);

      auto_file_lock(const auto_file_lock &other) = delete;
      auto_file_lock &operator=(const auto_file_lock &other) = delete;

      auto_file_lock(auto_file_lock &&other);
      auto_file_lock &operator=(auto_file_lock &&other);

      ~auto_file_lock();

    private:
      int file_descriptor;
  };
}

#endif
