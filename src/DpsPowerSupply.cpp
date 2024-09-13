//#include <sys/_stdint.h>
#include <Arduino.h>
#include "DpsPowerSupply.h"

DPS_psu::DPS_psu(Stream &stream, uint8_t deviceAddress)
  : stream(&stream), deviceAddress(deviceAddress) {
 
  crc_tab16_init = false;
  stream.readBytes(buffer, 5);  //Lectura para eliminar ruidos
}

void DPS_psu::write(Address registerAddress, uint16_t value){
  sendDataSingle(WRITE_REG, registerAddress, value);
}

uint16_t DPS_psu::read(Address registerAddress){
  sendDataSingle(READ_REG, registerAddress, 0x01);
  data.byte.byteL = buffer[4];
  data.byte.byteH = buffer[3];
  return data.word;
}


//Pass in centi Amps (500 = 5.00A, for example)
void DPS_psu::writeVoltageCurrent(uint16_t centiVolts, uint16_t centiAmps) {
  sendDataMult(WRITE_MULT_REG, 0x0000, 0x0002, 0x04, centiVolts, centiAmps);
}

//sends data to the power supply (un registro)
void DPS_psu::sendDataSingle(FunctionCode functionCode, Address registerAddress, uint16_t registerValue) {
  digitalWrite(LED_BUILTIN, true);
  buffer[0] = deviceAddress;
  buffer[1] = functionCode;
  buffer[2] = registerAddress >> 8;
  buffer[3] = registerAddress;
  buffer[4] = registerValue >> 8;
  buffer[5] = registerValue;
  uint16_t crcVal = crc_DPS(buffer, 6);
  buffer[6] = crcVal >> 8;
  buffer[7] = crcVal;
  
  delay(5);  // 3.5 data Frame delay
  stream->write(buffer, 8);
  
  byte bytes = 8;
  if (functionCode == READ_REG) {
    bytes = 5 + registerValue * 2;
  }
  stream->readBytes(buffer, bytes);  //Se leen los datos retornados por la fuente esto puede demorar hasta 500 ms
  digitalWrite(LED_BUILTIN, false);
}

//sends data to the power supply (múltiples registros)
void DPS_psu::sendDataMult(FunctionCode functionCode, uint16_t registerAddress, uint16_t numberofAddresses, uint8_t numberofBytes, uint16_t registerValue, uint16_t register2Value) {
  byte buffer[13] = { deviceAddress, functionCode, registerAddress >> 8, registerAddress, numberofAddresses >> 8, numberofAddresses, numberofBytes, registerValue >> 8, registerValue, register2Value >> 8, register2Value };
  uint16_t crcVal = crc_DPS(buffer, 11);
  buffer[11] = crcVal >> 8;
  buffer[12] = crcVal;
  delay(5);  // 3.5 data Frame delay
  stream->write(buffer, 13);
  stream->readBytes(buffer, 8);  //Se leen los datos retornados por la fuente y así limpiar el buffer
}

//CRC function
//Modified from https://github.com/lammertb/libcrc/blob/master/src/crc16.c
//which is is licensed under the MIT License
uint16_t DPS_psu::crc_DPS(const unsigned char *input_str, size_t num_bytes) {

  uint16_t crc;
  const unsigned char *ptr;
  size_t a;

  if (!crc_tab16_init)
    init_crc16_tab();

  crc = CRC_START;
  ptr = input_str;

  if (ptr != NULL)
    for (a = 0; a < num_bytes; a++) {
      crc = (crc >> 8) ^ crc_tab16[(crc ^ (uint16_t)*ptr++) & 0x00FF];
    }


  uint8_t crc_a = crc;
  uint8_t crc_b = crc >> 8;
  crc = crc_a << 8;
  crc = crc + crc_b;

  return crc;
}

//CRC Table building function
void DPS_psu::init_crc16_tab(void) {

  uint16_t i;
  uint16_t j;
  uint16_t crc;
  uint16_t c;

  for (i = 0; i < 256; i++) {
    crc = 0;
    c = i;
    for (j = 0; j < 8; j++) {
      if ((crc ^ c) & 0x0001)
        crc = (crc >> 1) ^ CRC_POLY_16;
      else
        crc = crc >> 1;
      c = c >> 1;
    }
    crc_tab16[i] = crc;
  }

  crc_tab16_init = true;
}
