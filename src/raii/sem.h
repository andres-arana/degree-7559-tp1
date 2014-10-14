#ifndef __RAII__SEM__H_INCLUDED__
#define __RAII__SEM__H_INCLUDED__

namespace raii {
  class sem {
    public:
      explicit sem(int semid, int semnum);

      void wait(int amount = 1);

      bool try_wait(int amount = 1);

      void signal(int amount = 1);

      void control();
    private:
      int semid;
      int semnum;

  };
}

#endif
