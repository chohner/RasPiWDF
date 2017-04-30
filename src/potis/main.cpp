#include <thread>  // std::thread
#include "potis.h"

int main() {
  setup_ads();

  int n = 10000;
  std::thread readingThread (read_n_values, n);
  //readingThread.detach();  // don't wait
  readingThread.join();  // pauses until finished

  powerdown_ads();
return 0;
}

