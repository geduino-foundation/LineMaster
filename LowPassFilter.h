#ifndef _LOW_PASS_FILTER_H_
#define _LOW_PASS_FILTER_H_

#include <Arduino.h>

class LowPassFilter {

  public:

    LowPassFilter(const unsigned int _dim) : dim(_dim) {
      
      // Initialization
      init();
    
    };

    void filter(const int value, int * filtered);

  private:

    const unsigned int dim;

    unsigned int index;

    int * buffer;

    void init();
  
};

#endif
