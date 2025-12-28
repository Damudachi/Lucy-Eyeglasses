const int trigPin = 12; // Trigger pin of the ultrasonic sensor
const int echoPin = 11; // Echo pin of the ultrasonic sensor
const int ledPin = 13; // Pin for the LED light bulb
const long interval = 60000; // 20-minute interval in milliseconds
const int blinkDelay = 500; // Blink delay in milliseconds
const int distanceThreshold = 100; // Distance threshold in centimeters

unsigned long previousMillis = 0;
bool timerOn = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    timerOn = true;
    unsigned long timerStartMillis = millis();
    while (timerOn && (millis() - timerStartMillis <= 5000)) {
      digitalWrite(ledPin, HIGH);
      int distance = measureDistance();
      if (distance < distanceThreshold) {
        blinkLED();
        timerStartMillis = millis();
      }
    }
    if(timerOn) {
      resetTimer();
    }
  }
  else if (timerOn) {
    int distance = measureDistance();
    if (distance < distanceThreshold) {
      blinkLED();
    }
  }
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void blinkLED() {
  digitalWrite(ledPin, LOW);
  delay(blinkDelay);
  digitalWrite(ledPin, HIGH);
  delay(blinkDelay);
}

void resetTimer() {
  timerOn = false;
  digitalWrite(ledPin, LOW);
}
