// 4 LED, 2 Push Button, 1 Potensiometer
// Button 1 = ubah kecepatan (cepat, sedang, lambat)
// Button 2 = ubah mode (semua nyala / bergantian)

int led[] = {2, 3, 4, 5};
int buttonSpeed = 6;
int buttonMode = 7;
int pot = A0;

int mode = 1;          // mode LED: 1 = semua nyala, 2 = bergantian
int speedMode = 1;     // 1=cepat, 2=sedang, 3=lambat
bool lastSpeedState = HIGH;
bool lastModeState = HIGH;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
  }
  pinMode(buttonSpeed, INPUT_PULLUP);
  pinMode(buttonMode, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("=== Sistem Lampu Pintar Aktif ===");
}

void loop() {
  int potValue = analogRead(pot);
  int brightness = map(potValue, 0, 1023, 0, 255);

  bool currentSpeed = digitalRead(buttonSpeed);
  bool currentMode = digitalRead(buttonMode);

  // ===== Tombol Speed =====
  if (currentSpeed == LOW && lastSpeedState == HIGH) {
    speedMode++;
    if (speedMode > 3) speedMode = 1;
    Serial.print("Kecepatan: ");
    if (speedMode == 1) Serial.println("Cepat");
    else if (speedMode == 2) Serial.println("Sedang");
    else Serial.println("Lambat");
    delay(250); // debounce ringan
  }
  lastSpeedState = currentSpeed;

  // ===== Tombol Mode =====
  if (currentMode == LOW && lastModeState == HIGH) {
    mode++;
    if (mode > 2) mode = 1;
    Serial.print("Mode: ");
    if (mode == 1) Serial.println("SEMUA NYALA");
    else Serial.println("BERGANTIAN");
    delay(250); // debounce ringan
  }
  lastModeState = currentMode;

  // ===== Tentukan delay berdasarkan speedMode =====
  int delayTime;
  if (speedMode == 1) delayTime = 100;   // cepat
  else if (speedMode == 2) delayTime = 300; // sedang
  else delayTime = 600;                   // lambat

  // ===== Mode LED =====
  if (mode == 1) {
    for (int i = 0; i < 4; i++) {
      analogWrite(led[i], brightness);
    }
  } 
  else if (mode == 2) {
    for (int i = 0; i < 4; i++) {
      analogWrite(led[i], brightness);
      delay(delayTime);
      analogWrite(led[i], 0);
    }
  }
}