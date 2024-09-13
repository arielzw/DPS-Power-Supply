# DPS Power supply for Arduino
Control of Ruideng DPS power supply series throught serial port
Supports writing and reading all parameters (voltage, current, power, protections, etc.) using a software or hardware serial port.

La librería consta de 3 funciones:

## Constructor:
DPS_psu psu(Stream, DeviceAddress);

Stream: Flujo en el que se envían los datos, puede ser cualquier puerto serie de hardware o de software.
DeviceAddress: Dirección del dispositivo, en forma predeterminada es la dirección 0x01;

## Escritura de datos:
psu.write(Parametro, Valor);
Parametro: Alguna de las siguientes opciones (ver archivo en carpeta doc):
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

Valor: Valor del parámetro a escribir

Ejemplo:
psu.write(U_SET, 600); // Se ajusta la tensión de salida en 6,00 V

## Lectura de datos:
uint16_t read(Parametro);
Parametro: Alguna de las siguientes opciones (ver archivo en carpeta doc):
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

  ## Escritura de tensión y corriente en forma simultánea
  void writeVoltageCurrent(uint16_t centiVolts, uint16_t centiAmps);
