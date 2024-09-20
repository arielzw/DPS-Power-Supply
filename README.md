# DPS Power supply control for Arduino
Control of Ruideng DPS power supply series throught serial port.
Supports writing and reading all parameters (voltage, current, power, protections, etc.) using a software or hardware serial port.

Code written using the work of https://github.com/AntaresAdroit as starting point.

IMPORTANT NOTE: For the interface to work, the DPS power supply must be the "Communication version" with USB or Bluetooth board INCLUDED (if it will never used) because the serial communication is disabled and connector removed in other versions.

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
psu.write(Parameter, Value);
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
This function is intended for speed up the writing of most commonly used parameters (see timming notes below).
```c++
void psu.writeVoltageCurrent(uint16_t centiVolts, uint16_t centiAmps);
```

## Interface
The Arduino harware or serial port must be connected to the serial port connector of the DPS power supply, it is located in different places depending on the model:
![imagen](https://github.com/user-attachments/assets/933cda70-fc3b-4c14-9e79-6869445d99b8)

![imagen](https://github.com/user-attachments/assets/dcd9623d-f5b3-4096-83af-9456d4c3f371)

Connection:

IMPORTANT NOTE: The DPS uses 3.3 V logic but the standard Arduino boards uses 5 V logic, the simplest way to translate the level is the following:

![imagen](https://github.com/user-attachments/assets/a3909094-3cf0-44df-aba7-ee4431b30fad)

Default baud rate setting at DPS is 9600 but it can be changed pressing V button while power on.

## Considerations about timming.
After sending each command from the Arduino to the DPS, as setting the output voltage for example, the DPS sends a reply with the same command for communication verification. This reply from the DPS may be delayed up to 0.5 s, in the mean time the program flow in the Arduino is stopped. Take in mind this behavior in your final application.

