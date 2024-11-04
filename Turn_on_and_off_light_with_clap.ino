// Pin definitions
const int soundSensorPin = 2;  // Pin connected to the sound sensor
const int ledPin = 13;         // Pin connected to the LED (using built-in LED on pin 13)

// State variables
int ledState = LOW;                  // To track the LED state
unsigned long lastClapTime = 0;      // To track the last clap time
const unsigned long clapCooldown = 500; // Minimum time between claps (500 ms)

// State machine flags
bool clapDetected = false;           // To track if a clap was detected
bool waitForSilence = false;         // Flag to wait for silence after a clap

void setup() {
  pinMode(soundSensorPin, INPUT);  // Set the sound sensor pin as input
  pinMode(ledPin, OUTPUT);         // Set the LED pin as output
  digitalWrite(ledPin, LOW);       // Initially, turn off the LED
  Serial.begin(9600);              // Optional: for debugging
}

void loop() {
  // Read the sound sensor output
  int soundDetected = digitalRead(soundSensorPin);

  // State machine logic
  if (!waitForSilence && soundDetected == HIGH && (millis() - lastClapTime) > clapCooldown) {
    // A clap has been detected, set the clapDetected flag
    clapDetected = true;
    waitForSilence = true;             // Enable waiting for silence
    lastClapTime = millis();           // Record the time of this detection

    // Optional: Print debug info to serial monitor
    Serial.println("Clap detected, waiting for silence...");
  }

  // Check if we need to wait for silence after a clap detection
  if (waitForSilence && soundDetected == LOW) {
    // If silence is detected, toggle the LED
    if (clapDetected) {
      ledState = !ledState;            // Toggle LED state
      digitalWrite(ledPin, ledState);  // Apply the LED state
      Serial.println("LED toggled!");
    }
    // Reset flags after handling the clap
    clapDetected = false;
    waitForSilence = false;
  }
}
