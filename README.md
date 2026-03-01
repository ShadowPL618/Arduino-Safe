# Arduino-Safe
An interactive security system that uses a 3-digit button sequence to control a servo motor. The system features visual and auditory feedback, as well as an automatic security timeout.

🔑 Project Overview
This project simulates a digital combination lock. A user must enter the correct sequence using three push buttons. If the code is correct, the servo "unlocks"; if incorrect, the system triggers an alarm and remains locked.

🛠 Hardware Components
Arduino Uno

Servo Motor: Acts as the locking mechanism (connected to Pin 9).

3x Push Buttons: Used for passcode entry (Pins 2, 3, 4).

Piezo Buzzer: Provides audio feedback for success/failure (Pin 5).

LEDs: Red (Pin 11) for Access Denied; Green (Pin 10) for Access Granted.

<img width="1445" height="502" alt="Screenshot 2026-03-01 170421" src="https://github.com/user-attachments/assets/e1021703-059a-4424-99ae-e5722734c2ab" />


⚙️ Core Features
1. Passcode Logic
The system is programmed with a hardcoded array passcode[] = {2, 3, 2}.

Button 1: Digit 1

Button 2: Digit 2

Button 3: Digit 3

2. Smart Inactivity Timeout
The code uses millis() to track the lastActivityTime. If no button is pressed for 10 seconds, the system automatically:

Resets the entry position to 0.

Moves the Servo back to the 0° (Locked) position.
This ensures the "door" doesn't stay unlocked indefinitely.

3. Feedback Sequences
Access Granted: Servo rotates to 180°, the buzzer plays three ascending tones, and the Green LED flashes.

Access Denied: Servo stays at 0°, the buzzer emits a long low-pitch "error" tone, and the Red LED flashes.

💻 Code Structure
The sketch is optimized for reliability:

State Tracking: Uses boolean variables (button1Pressed, etc.) to ensure a button press is only counted once per click, preventing "double-entry" errors.

Internal Pull-ups: Uses INPUT_PULLUP to simplify wiring, eliminating the need for external resistors on the buttons.

Serial Debugging: Prints real-time status to the Serial Monitor (9600 baud) to track digit entry and system timeouts.
