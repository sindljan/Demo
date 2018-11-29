// Světelný senzor TEMT6000

// nastavení čísla propojovacího pinu
#define analogPin A0
// vytvoření proměnných pro výsledky měření
int analogHodnota;
int prepocet;

void setup() {
  // zahájení komunikace po sériové lince
  // rychlostí 9600 baud
  Serial.begin(9600);
}

void loop() {
  // načtení hodnoty z analogového pinu
  analogHodnota = analogRead(analogPin);
  // přepočet analogové hodnoty z celého rozsahu
  //  0-1023 na procentuální rozsah 0-100
  prepocet = map(analogHodnota, 0, 1023, 0, 100);
  // výpis načtených dat po sériové lince
  Serial.print("Nactena hodnota: ");
  Serial.print(analogHodnota);
  Serial.print(", v procentech: ");
  Serial.print(prepocet);
  if (prepocet > 50) {
    Serial.println(" | V okoli je dostatek svetla.");
  }
  else {
    Serial.println(" | V okoli je nedostatek svetla.");
  }
  // pauza před novým během loop smyčky
  delay(500);
}
