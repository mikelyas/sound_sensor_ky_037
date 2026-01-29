const int MIC_AO_PIN = A0;
const int LED_PIN = 13;

// How often to sample the mic (ms)
const unsigned long sampleIntervalMs = 5;   // 200 Hz sampling
// How often to print values (ms)
const unsigned long printIntervalMs  = 200; // 5 prints/sec

// Baseline tracking (simple low-pass filter)
float baseline = 512.0f;       // start near mid-scale
const float baselineAlpha = 0.02f; // smaller = slower baseline adaptation

// Clap detection
int clapThreshold = 60;              // deviation threshold (tune this!)
const unsigned long clapLockoutMs = 300;

bool ledState = false;
unsigned long lastSampleMs = 0;
unsigned long lastPrintMs = 0;
unsigned long lastClapMs = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println("KY-037 AO clap detector (software threshold)");
  Serial.println("Columns: raw, baseline, deviation");
}

void loop() {
  unsigned long now = millis();

  // Sample mic at a fixed rate
  if (now - lastSampleMs >= sampleIntervalMs) {
    lastSampleMs = now;

    int raw = analogRead(MIC_AO_PIN);

    // Update baseline slowly (tracks ambient noise / DC offset)
    baseline = (1.0f - baselineAlpha) * baseline + baselineAlpha * raw;

    // "Sound level": how far raw is from baseline
    int deviation = abs(raw - (int)baseline);

    // Clap detection with lockout
    if (deviation >= clapThreshold && (now - lastClapMs) >= clapLockoutMs) {
      lastClapMs = now;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      Serial.println("CLAP!");
    }

    // Periodic printing (doesn't spam the serial port)
    if (now - lastPrintMs >= printIntervalMs) {
      lastPrintMs = now;

      Serial.print(raw);
      Serial.print(", ");
      Serial.print((int)baseline);
      Serial.print(", ");
      Serial.println(deviation);
    }
  }
}
