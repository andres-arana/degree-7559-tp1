#ifndef __UTIL__FILE_LOCK_H_INCLUDED__
#define __UTIL__FILE_LOCK_H_INCLUDED__

#include <string>

namespace util {

  class file_lock {
    private:
      int file_descriptor;

      void lock();

      void unlock();

    public:

      explicit file_lock(int file_descriptor);

      explicit file_lock(const std::string &filename);


      ~file_lock();
  };

};


#endif
