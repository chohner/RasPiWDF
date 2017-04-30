#ifndef POTIS_H
#define POTIS_H

class Potis {
  private:
    float poti0;
    float poti1;
    float poti2;
    float poti3;

  public:
    float getPoti(int potNo);

    void setPoti(int potNo, float potVal);
};

void setup_ads();
void powerdown_ads();
void read_n_values(int n);

#endif  // POTIS_H
