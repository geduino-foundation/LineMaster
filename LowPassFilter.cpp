#include "LowPassFilter.h"

void LowPassFilter::filter(const int value, int * filtered) {

  // Put value into buffer
  buffer[index] = value;

   // Increase index
  if (++index >= dim) {

    // Reset index
    index = 0;
    
  }
  
  long sum = 0;

  for (int index2 = 0; index2 < dim; index2++) {

    // Sum
    sum += (long) buffer[index2];
    
  }

  // Calculate filtered
  * filtered = (int) (sum / dim);

}

void LowPassFilter::init() {

  // Alloc memory for buffer
  buffer = (int *) malloc(sizeof(int) * dim);

  // Fill buffer with zeroes
  memset(buffer, 0, sizeof(int) * dim);

  // Set index to zero
  index = 0;
  
}
