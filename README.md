# DPS Power supply control for Arduino
Control of Ruideng DPS power supply series throught serial port.
Supports writing and reading all parameters (voltage, current, power, protections, etc.) using a software or hardware serial port.

IMPORTANT NOTE

## Classes

The library consists of 3 functions:

### Constructor:
```c++
DPS_psu psu(Stream, DeviceAddress);
```
Stream: Stream in which data is sent, can be any hardware or software serial port.

DeviceAddress: Device address, by default it is address 0x01;

### Parameter writing:

```c++
psu.write(Parameter, Valor);
```

Parameter: Any of the following options (see file in doc folder):

  U_SET,
  I_SET,
  LOCK,
  ONOFF,
  B_LED,


Value: Value of the parameter to write

Example:
```c++
psu.write(U_SET, 600); // Set output voltage to 6.00 V
```
### Parameter reading:
```c++
uint16_t psu.read(Parameter);
```
Parameter: One of the following options (see file in doc folder):

U_SET,
I_SET,
UOUT,
IOUT,
POWER,
UIN,
LOCK,
PROTECT,
CVCC,
ONOFF,
B_LED,
MODEL,
VERSION

Example:
```c++
currentUout = psu.read(UOUT); // Get the output voltage in centi Volts
Serial.println(currentUout);
```

### Simultaneous writing of voltage and current
This function is intended for speed up the writing of most commonly used parameters for setting (see timming notes below).
void psu.writeVoltageCurrent(uint16_t centiVolts, uint16_t centiAmps);

## Interface
The Arduino harware or serial port must be connected to the serial port connector of the DPS power supply
