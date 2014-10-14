#ifndef __RAII__SEM_SET__H_INCLUDED__
#define __RAII__SEM_SET__H_INCLUDED__

namespace raii {
  class sem_set {
    public:
      explicit sem_set(int semid);

      void wait(int semnum, int amount = 1);

      bool try_wait(int semnum, int amount = 1);

      void signal(int semnum, int amount = 1);

      void control(int semnum);

    private:
      int semid;
  };
}

#endif
