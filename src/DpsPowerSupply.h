#include <Stream.h>

typedef enum FunctionCode {
	READ_REG = 0x03,
	WRITE_REG = 0x06,
	WRITE_MULT_REG = 0x10
};

typedef enum Address {
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
};

class DPS_psu {
public:
	DPS_psu(Stream &, uint8_t);
	void write(Address, uint16_t);
	uint16_t read(Address);
	void writeVoltageCurrent(uint16_t centiVolts, uint16_t centiAmps);
  
private:
	Stream *stream;
	byte buffer[15];
	uint8_t deviceAddress;
	uint32_t tsLastCommandSent;  //Timestamp of last command sent
	bool lastResponseRecieved;   //Has the last response been recieved?
	
	void sendDataSingle(FunctionCode functionCode, Address registerAddress, uint16_t registerValue);
	void sendDataMult(FunctionCode functionCode, uint16_t registerAddress, uint16_t numberofAddresses, uint8_t numberofBytes, uint16_t registerValue, uint16_t register2Value);
	uint16_t crc_DPS(const unsigned char *input_str, size_t num_bytes);
	void init_crc16_tab(void);
	bool crc_tab16_init;
	uint16_t crc_tab16[256];
	static const uint16_t CRC_POLY_16 = 0xA001;
	static const uint16_t CRC_START = 0xFFFF;

	union Data {
		struct Byte {
			byte byteL;
			byte byteH;
		} byte;
		uint16_t word;
	} data;
};
