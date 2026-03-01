#include <Servo.h>

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int buzzer = 5;
const int greenLED = 10;
const int redLED = 11;
const int servoPin = 9; 

Servo myServo;

int passcode[] = {2, 3, 2};
int enteredCode[3];
int position = 0;

// Variables for timing
unsigned long lastActivityTime = 0;
const long timeoutLimit = 10000; 

// Variables to track button states
bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  myServo.attach(servoPin);
  myServo.write(0); // Initialize locked
  
  Serial.begin(9600);
  Serial.println("Security System Ready!");
  lastActivityTime = millis(); // Initialize timer
}

void loop() {
  // 10-second inactivity check: move servo to 0 degrees
  if (millis() - lastActivityTime >= timeoutLimit) {
    myServo.write(0);
    if (position > 0) {
      Serial.println("Timeout: Resetting entry...");
      position = 0;
    }
    lastActivityTime = millis(); // Refresh timer to prevent spamming
  }

  // Button 1 (left)
  if (digitalRead(button1) == LOW && !button1Pressed) {
    button1Pressed = true;
    lastActivityTime = millis(); // Reset timer on press
  }
  if (digitalRead(button1) == HIGH && button1Pressed) {
    enteredCode[position] = 1;
    Serial.print("Button 1 pressed - Digit ");
    Serial.print(position + 1);
    Serial.println("/3 entered");
    position++;
    button1Pressed = false;
    delay(50);
  }

  // Button 2 (middle)
  if (digitalRead(button2) == LOW && !button2Pressed) {
    button2Pressed = true;
    lastActivityTime = millis(); // Reset timer on press
  }
  if (digitalRead(button2) == HIGH && button2Pressed) {
    enteredCode[position] = 2;
    Serial.print("Button 2 pressed - Digit ");
    Serial.print(position + 1);
    Serial.println("/3 entered");
    position++;
    button2Pressed = false;
    delay(50);
  }

  // Button 3 (right)
  if (digitalRead(button3) == LOW && !button3Pressed) {
    button3Pressed = true;
    lastActivityTime = millis(); // Reset timer on press
  }
  if (digitalRead(button3) == HIGH && button3Pressed) {
    enteredCode[position] = 3;
    Serial.print("Button 3 pressed - Digit ");
    Serial.print(position + 1);
    Serial.println("/3 entered");
    position++;
    button3Pressed = false;
    delay(50);
  }
  
  if (position == 3) {
    checkCode();
    position = 0;
    lastActivityTime = millis(); // Reset timer after check
  }
}

void checkCode() {
  bool correct = true;
  
  Serial.print("Code entered: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(enteredCode[i]);
    if (i < 2) Serial.print("-");
  }
  Serial.println();
  
  for (int i = 0; i < 3; i++) {
    if (enteredCode[i] != passcode[i]) {
      correct = false;
    }
  }
  
  if (correct) {
    Serial.println("ACCESS GRANTED");
    myServo.write(180); // Move to 180 degrees
    
    // Buzzer: 3 beeps with ascending pitch
    tone(buzzer, 400, 150); delay(350);
    tone(buzzer, 600, 150); delay(350);
    tone(buzzer, 800, 150); delay(350);

    for (int i = 0; i < 6; i++) {
      digitalWrite(greenLED, HIGH);
      delay(250);
      digitalWrite(greenLED, LOW);
      delay(250);
    }
  } else {
    Serial.println("ACCESS DENIED");
    myServo.write(0); // Move to 0 degrees
    
    // Buzzer: Low tone for 1 second
    tone(buzzer, 150, 1000); 

    for (int i = 0; i < 6; i++) {
      digitalWrite(redLED, HIGH);
      delay(250);
      digitalWrite(redLED, LOW);
      delay(250);
    }
  }
}
