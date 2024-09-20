#include <Stream.h>
#include <DpsPowerSupply.h>
// #include <SoftwareSerial.h> // In case of use software serial

HardwareSerial SerialPsu(D2, D8); //rx tx Definition only required in STM Nucleo boards, not required in Arduino Mega.
//SoftwareSerial SerialPsu(D7, D8); //rx tx In case of use software serial

DPS_psu psu(SerialPsu, 1); // psu class instantiation

void setup() {
	SerialPsu.begin(9600); // Serial communication to the psu, default 9600
	Serial.begin(57600);
	
	psu.write(U_SET, 600); // Setting 6 Volts
	psu.write(I_SET, 500); // Setting 5 Amper
	delay(2000);
	
	psu.write(U_SET, 1200); // Setting 12 Volts
	psu.write(I_SET, 800); // Setting 8 Amper
	psu.write(ONOFF, true); // Output ON
	
	delay(500);
	psu.write(B_LED, 1);	// Backlight brightness level 1
	
	Serial.println((float)psu.read(UOUT)/100); // Reading output voltage and converting go float (centi volts to volts)
	Serial.println((float)psu.read(IOUT)/100);
	Serial.println((float)psu.read(POWER)/100);
	Serial.println((float)psu.read(U_SET)/100); // Reading actual voltage setting.
	Serial.println(psu.read(MODEL)); // Reading model number 5020 for this module
	
}

void loop() {
  // put your main code here, to run repeatedly:

}
