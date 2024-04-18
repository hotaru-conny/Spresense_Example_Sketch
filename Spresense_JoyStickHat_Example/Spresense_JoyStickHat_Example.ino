#include <Wire.h>

#define JOYSTICK_ADDRESS 0x38
#define JOYSTICK_REGISTER 0x02


struct JoystickData {
  int8_t x;
  int8_t y;
	bool pressed;
} data;

void readData() {
  Wire.beginTransmission(JOYSTICK_ADDRESS);
	Wire.write(JOYSTICK_REGISTER);
	Wire.endTransmission();
	
	Wire.requestFrom(JOYSTICK_ADDRESS, 3);
	if (Wire.available()) {
        data.x = Wire.read();
        data.y = Wire.read();
        data.pressed = Wire.read() == 0;
	}
}

void setup() {
  //Serial初期化
  Serial.begin(115200);

  //I2C初期化
  Wire.begin();
}

void loop() {
    readData();
    Serial.printf("(%d, %d):%d\n", data.x, data.y, data.pressed);
    delay(20);
}