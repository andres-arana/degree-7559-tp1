#ifndef __RAII__FILE_LOCK_H_INCLUDED__
#define __RAII__FILE_LOCK_H_INCLUDED__

#include <string>

namespace raii {
  class file_lock {
    public:
      file_lock();
      explicit file_lock(int file_descriptor);

      file_lock(const file_lock &other) = delete;
      file_lock &operator=(const file_lock &other) = delete;

      file_lock(file_lock &&other);
      file_lock &operator=(file_lock &&other);

      ~file_lock();

    private:
      int file_descriptor;
  };
}

#endif
