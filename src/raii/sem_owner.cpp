#include "raii/sem_owner.h"
#include "syscalls/sem.h"
#include <algorithm>
#include <iterator>

using namespace std;
using namespace raii;

sem_owner::sem_owner(unsigned short set_size, unsigned short initial_value)
  : identifier(syscalls::semget(set_size)) {
    syscalls::semsetall(
        identifier,
        vector<unsigned short>(set_size, initial_value));
  }

int sem_owner::id() {
  return identifier;
}

sem_owner::~sem_owner() {
  syscalls::semrelease(identifier);
}
