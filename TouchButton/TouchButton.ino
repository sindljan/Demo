#define VSTUP 3
void setup() {
Serial.begin(9600);
pinMode(13, OUTPUT);
attachInterrupt(digitalPinToInterrupt(VSTUP), dotyk, RISING);
}
void loop() {
}
void dotyk(){
Serial.println("Tlacitko stisknuto.");
}
