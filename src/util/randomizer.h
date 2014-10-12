#ifndef __UTIL__RANDOMIZER__H_INCLUDED__
#define __UTIL__RANDOMIZER__H_INCLUDED__

namespace util {
  class randomizer {
    public:
      explicit randomizer(unsigned long min, unsigned long max);

      unsigned long next();

    private:
      unsigned long min;
      unsigned long max;
  };
}

#endif
