#ifndef __RAII__SEM_OWNER__H_INCLUDED__
#define __RAII__SEM_OWNER__H_INCLUDED__

#include <vector>

namespace raii {
  class sem_owner {
    public:
      explicit sem_owner(
          unsigned short set_size,
          const std::vector<unsigned short> &initial_values);

      explicit sem_owner(
          unsigned short set_size,
          unsigned short initial_value);

      explicit sem_owner(const sem_owner& other) = delete;
      sem_owner &operator=(const sem_owner& other) = delete;

      explicit sem_owner(sem_owner &&other) = delete;
      sem_owner &operator=(sem_owner &&other) = delete;

      int id();

      ~sem_owner();

    private:
      int identifier;
  };
}

#endif
