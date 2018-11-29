#define PRX_PIN 7

void setup() {
  Serial.begin(9600);
  pinMode(PRX_PIN, INPUT);
}
void loop() {
  // jednobitová proměnná pro uložení stavu
  bool stav;
  // načtení stavu aktuálního pinu, nutná
  // negace, protože modul vrací 0 při detekci
  stav = !digitalRead(PRX_PIN);
  Serial.print(stav);
  Serial.print("  ");

  // pauza pro přehlednější výpis
  delay(1000);
}
