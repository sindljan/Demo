#define DIO_PIN_2 4

void setup() {
  // put your setup code here, to run once:
   for (int i=0; i <= 20; i++){
      pinMode(i, OUTPUT);
      delay(10);
   }
   Serial.begin(9600);
}

void TestPin(int pin){
  Serial.print("Testovany pin: ");
  Serial.println(pin);
  digitalWrite(pin, HIGH);       // sets the digital pin 2 on
  delay(2000);                  // waits for a second
  digitalWrite(pin, LOW);        // sets the digital pin 2 off
  delay(5000);                  // waits for a second
}

void loop() {
  // put your main code here, to run repeatedly:
     for (int i=0; i <= 20; i++){
      TestPin(i);
      delay(10);
   }
}
