#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68

struct Time {
  byte h;
  byte m;
  byte s;
};

struct Date {
  byte d;
  byte m;
  int y;
  byte wd;
};

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}
void setup() {
  Wire.begin();
  Serial.begin(9600);
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  //setDS3231time(00,00,18,5,29,11,18);
}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year) {
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void resetRegisterTo(byte addr) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(addr); // set DS3231 register pointer to 00h
  Wire.endTransmission();
}

Time getTime() {
  Time now = {0, 0, 0};
  resetRegisterTo(0);
  Wire.requestFrom(DS3231_I2C_ADDRESS, 3);
  // request 3 bytes of data from DS3231 starting from register 00h
  now.s = bcdToDec(Wire.read() & 0x7f);
  now.m = bcdToDec(Wire.read());
  now.h = bcdToDec(Wire.read() & 0x3f);
  return now;
}

Date getDate() {
  Date today = {0, 0, 0, 0};
  resetRegisterTo(3);
  Wire.requestFrom(DS3231_I2C_ADDRESS, 4);
  // request 3 bytes of data from DS3231 starting from register 00h
  today.wd = bcdToDec(Wire.read());
  today.d = bcdToDec(Wire.read());
  today.m = bcdToDec(Wire.read());
  today.y = 2000+bcdToDec(Wire.read());
  return today;
}


void loop() {
  Time now = getTime();
  Date today = getDate();
  Serial.print((String)now.h + ":" + (String)now.m + ":" + (String)now.s);
  Serial.print("  ");
  Serial.println((String)today.d + "." + (String)today.m + "." + (String)today.y);
  delay(1000); // every second
}
