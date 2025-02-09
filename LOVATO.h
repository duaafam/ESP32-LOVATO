#ifndef LOVATO_h
#define LOVATO_h

#include "Arduino.h";

// Define measurement registers and scaling factors
struct Measurement {
  uint16_t registerAddress;
  uint8_t words;
  float scaleFactor;
  const char* name;
};

// List of parameters to read
Measurement parameters[] = {
  {0x0002, 2, 100.0, "L1 Phase Voltage (V)"},
  {0x0004, 2, 100.0, "L2 Phase Voltage (V)"},
  {0x0006, 2, 100.0, "L3 Phase Voltage (V)"},
  {0x0008, 2, 10000.0, "L1 Current (A)"},
  {0x000A, 2, 10000.0, "L2 Current (A)"},
  {0x000C, 2, 10000.0, "L3 Current (A)"},
  {0x0032, 2, 1000.0, "Frequency (Hz)"},
  {0x0014, 2, 100.0, "L1 Active Power (W)"},
  {0x0016, 2, 100.0, "L2 Active Power (W)"},
  {0x0018, 2, 100.0, "L3 Active Power (W)"},
  {0x003A, 2, 100.0, "Total Active Power (W)"},
  {0x0046, 2, 100.0, "Current Asymmetry (%)"}
};

#endif