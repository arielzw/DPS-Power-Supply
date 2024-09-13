#include <Stream.h>
#include <DpsPowerSupply.h>
#include <SoftwareSerial.h>

HardwareSerial SerialPsu(D2, D8); //rx tx
//SoftwareSerial SerialPsu(D7, D8); //rx tx Funciona OK, probado a 9600
DPS_psu psu(SerialPsu, 1);


void setup() {
	// put your setup code here, to run once:
	//SerialPsu.timeout(2000);

  
	SerialPsu.begin(9600);
	Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);

  psu.write(B_LED, 3);
  
  psu.write(ONOFF, false);
  
  psu.write(U_SET, 600);
  psu.write(I_SET, 500);
  delay(2000);
  
  psu.write(U_SET, 1200);
  psu.write(I_SET, 800);
	psu.write(ONOFF, true);
  
  delay(500);
  psu.write(B_LED, 1);
	
  Serial.println((float)psu.read(UOUT)/100);
	Serial.println((float)psu.read(IOUT)/100);
  Serial.println((float)psu.read(POWER)/100);
  Serial.println((float)psu.read(U_SET)/100);
  Serial.println(psu.read(MODEL));
	
}

void loop() {
  // put your main code here, to run repeatedly:

}
