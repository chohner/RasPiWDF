#include <iostream>
#include <sys/types.h> // open
#include <sys/stat.h>  // open
#include <fcntl.h>     // open
#include <sys/ioctl.h> // control
#include <unistd.h>    // read/write usleep
#include <stdlib.h>    // exit
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions

using namespace std;

int fd;
// adress with addr=GND : 0x48
int ads_address = 0x48;
float VPS;
int16_t val;
uint8_t writeBuf[3];
uint8_t readBuf[2];

void setup_ads(){
  //open device on /dev/i2c-1
  if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
    cout << "Error: Couldn't open device! " << fd << endl;
    exit (1);
  }

  // connect to ads1115 as i2c slave
  if (ioctl(fd, I2C_SLAVE, ads_address) < 0) {
    cout << "Error: Couldn't find device on address!" << endl;
    exit (1);
  }


  // setup ADS1115
  writeBuf[0] = 0b00000001; // (points to Config register)
  writeBuf[1] = 0b11010101; // bit 15-8 0xD3
  writeBuf[2] = 0b10000011; // bits 7-0  0x85

  VPS = 2.048 / 32768.0; // volts per step

  // begin conversation
  if (write(fd, writeBuf, 3) != 3) {
    perror("Write to register 1");
    exit(-1);
  }
  // wait for bit 15 (1 : ready)
  while ((writeBuf[0] & 0x80) == 0) {
    if (read(fd, writeBuf, 2) != 2) {
      perror("Read conversion");
      exit(-1);
    }
  }
  cout << "ADS1115 Setup complete" << endl;
}

float read_ads(){
  // set pointer to 0
  readBuf[0] = 0;
  if (write(fd, readBuf, 1) != 1) {
    perror("Write register select");
    exit(-1);
  }

  // read conversion register
  if (read(fd, readBuf, 2) != 2) {
    perror("Read conversion");
    exit(-1);
  }

  float pot_val = 0;
  // multiply by 256 then add readBuf[1]
  val = readBuf[0] << 8 | readBuf[1];
  if (val < 0)   val = 0;  // LSB sometimes generates very low neg number.
  // return voltage
  pot_val = val * VPS;
  return pot_val;
}


int main() {
  setup_ads();

  float pot1 = 0;
  pot1 = read_ads();
  cout << pot1 << endl;
  // power down ASD1115
  writeBuf[0] = 1;    // config register is 1
  writeBuf[1] = 0b11000011; // bit 15-8 0xC3 single shot on
  writeBuf[2] = 0b10000101; // bits 7-0  0x85
  if (write(fd, writeBuf, 3) != 3) {
    perror("Write to register 1");
    exit (1);
  }
  close(fd);
return 0;
}

