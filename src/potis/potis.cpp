#include <iostream>
#include "potis.h"


float Potis::getPoti(int potNo){
  float potVal = 0;
  switch (potNo) {
    case 0: potVal = poti0; break;
    case 1: potVal = poti1; break;
    case 2: potVal = poti2; break;
    case 3: potVal = poti3; break;
    default: std::cout<< "Provide poti ID!" << std::endl;
  }
  return potVal;
}

void Potis::setPoti(int potNo, float potVal){
  switch (potNo) {
    case 0: poti0 = potVal; break;
    case 1: poti1 = potVal; break;
    case 2: poti2 = potVal; break;
    case 3: poti3 = potVal; break;
    default: std::cout<< "Provide poti ID!" << std::endl;
  }
}

