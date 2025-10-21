// Define the pins for each segment (D0 to D6)
const int segmentA = 3; // D3
const int segmentB = 2; // D2
const int segmentC = 8; // D8
const int segmentD = 7; // D7
const int segmentE = 6; // D6
const int segmentF = 4; // D4
const int segmentG = 5; // D5

// Define button pins
const int incrementButton = 10; // Button to increment count
const int resetButton = 11;    // Button to reset count

// Define debounce delay
const unsigned long debounceDelay = 50;
unsigned long lastButtonPress = 0;

int currentCount = 0; // Variable to store the current count

void setup() {
  // Initialize the segment pins as OUTPUTs
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  
  // Initialize the button pins as INPUT_PULLUP (using internal pull-up resistors)
  pinMode(incrementButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check if the increment button is pressed
  if (digitalRead(incrementButton) == LOW && (currentMillis - lastButtonPress) > debounceDelay) {
    currentCount++;
    if (currentCount > 9) {
      currentCount = 0;  // Reset to 0 after 9
    }
    lastButtonPress = currentMillis;
    delay(200); // Delay to avoid bouncing
  }

  // Check if the reset button is pressed
  if (digitalRead(resetButton) == LOW && (currentMillis - lastButtonPress) > debounceDelay) {
    currentCount = 0;
    lastButtonPress = currentMillis;
    delay(200); // Delay to avoid bouncing
  }

  // Display the current count on the 7-segment display
  displayNumber(currentCount);
}

void displayNumber(int number) {
  // Turn off all segments before displaying a new number
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
  
  switch (number) {
    case 0:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      break;
    case 1:
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      break;
    case 2:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, HIGH);
      break;
    case 3:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 4:
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 5:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 6:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 7:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      break;
    case 8:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 9:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
  }
}
