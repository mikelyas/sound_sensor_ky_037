const int MIC_PIN = 3;   // KY-037 DO pin
const int LED_PIN = 13;  // LED pin

bool ledState = false;
bool lastMicState = LOW;

unsigned long lastTriggerTime = 0;
const unsigned long debounceTime = 300; // ms

void setup() {
  pinMode(MIC_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println("Clap detector ready");
}

void loop() {
  bool micState = digitalRead(MIC_PIN);
  unsigned long currentTime = millis();

  // Detect rising edge (LOW → HIGH)
  if (micState == HIGH && lastMicState == LOW) {

    // Debounce / lockout time
    if (currentTime - lastTriggerTime > debounceTime) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);

      Serial.println("Clap detected!");
      lastTriggerTime = currentTime;
    }
  }

  lastMicState = micState;
}
