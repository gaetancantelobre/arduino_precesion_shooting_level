
#include <Wire.h>  // Wire library - used for I2C communication

int ADXL345 = 0x53; // The ADXL345 sensor I2C address


int far_left = 2;
int left =3;
int middle = 4;
int right = 5;
int far_right = 6;

float angle_offset = 5;


float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;

void setup() {
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  setUpLEDPins();
  setUpGyro();
}
  
void setUpLEDPins()
{
  pinMode(far_left, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(middle,OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(far_right, OUTPUT);
}


void updateTiltIndicator()
{
  int adjusted_roll = rollF + angle_offset;
  digitalWrite(far_left, LOW);
  digitalWrite(left, LOW);
  digitalWrite(middle, LOW);
  digitalWrite(right, LOW);
  digitalWrite(far_right, LOW);
  if(adjusted_roll > 25)
    digitalWrite(far_left, HIGH);
  else if(adjusted_roll > 3 && adjusted_roll < 25)
    digitalWrite(left, HIGH);
  else if(adjusted_roll < 3 && adjusted_roll > -3)
    digitalWrite(middle,HIGH);
  else if(adjusted_roll < -3 && adjusted_roll > -25)
    digitalWrite(right,HIGH);
  else if(adjusted_roll < -25)
    digitalWrite(far_right,HIGH);
}

void setUpGyro()
{
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
  Wire.endTransmission();
  delay(10);

  //Off-set Calibration
  //X-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1E);
  Wire.write(1);
  Wire.endTransmission();
  delay(10);
  //Y-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1F);
  Wire.write(-2);
  Wire.endTransmission();
  delay(10);

  //Z-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x20);
  Wire.write(-9);
  Wire.endTransmission();
  delay(10);
}


void getTilt()
{
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
  X_out = X_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
  Y_out = Y_out / 256;
  Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
  Z_out = Z_out / 256;

  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
  // Low-pass filter
  rollF = 0.94 * rollF + 0.06 * roll ;
  Serial.println(rollF);
  Serial.println(rollF);

}

void loop() {
  getTilt();
  updateTiltIndicator();
  
}
 