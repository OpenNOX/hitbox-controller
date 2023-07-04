// define button pins
#define UP_BUTTON_PIN 22
#define DOWN_BUTTON_PIN 24
#define LEFT_BUTTON_PIN 26
#define RIGHT_BUTTON_PIN 28
#define BOTTOM_ACTION_1_BUTTON_PIN 30
#define BOTTOM_ACTION_2_BUTTON_PIN 32
#define BOTTOM_ACTION_3_BUTTON_PIN 34
#define BOTTOM_ACTION_4_BUTTON_PIN 36
#define TOP_ACTION_1_BUTTON_PIN 38
#define TOP_ACTION_2_BUTTON_PIN 40
#define TOP_ACTION_3_BUTTON_PIN 42
#define TOP_ACTION_4_BUTTON_PIN 44
#define EXTRA_ACTION_1_BUTTON_PIN 46
#define EXTRA_ACTION_2_BUTTON_PIN 48
#define EXTRA_ACTION_3_BUTTON_PIN 50

// define LED pins
#define BUILT_IN_LED_PIN 13
#define UP_LED_PIN 23
#define DOWN_LED_PIN 25
#define LEFT_LED_PIN 27
#define RIGHT_LED_PIN 29
#define BOTTOM_ACTION_1_LED_PIN 31
#define BOTTOM_ACTION_2_LED_PIN 33
#define BOTTOM_ACTION_3_LED_PIN 35
#define BOTTOM_ACTION_4_LED_PIN 37
#define TOP_ACTION_1_LED_PIN 39
#define TOP_ACTION_2_LED_PIN 41
#define TOP_ACTION_3_LED_PIN 43
#define TOP_ACTION_4_LED_PIN 45
#define EXTRA_ACTION_1_LED_PIN 47
#define EXTRA_ACTION_2_LED_PIN 49
#define EXTRA_ACTION_3_LED_PIN 51

// define output key codes
#define UP_KEY 0x61
#define DOWN_KEY 0x62
#define LEFT_KEY 0x63
#define RIGHT_KEY 0x64
#define BOTTOM_ACTION_1_KEY 0x65
#define BOTTOM_ACTION_2_KEY 0x66
#define BOTTOM_ACTION_3_KEY 0x67
#define BOTTOM_ACTION_4_KEY 0x68
#define TOP_ACTION_1_KEY 0x69
#define TOP_ACTION_2_KEY 0x6A
#define TOP_ACTION_3_KEY 0x6B
#define TOP_ACTION_4_KEY 0x6C
#define EXTRA_ACTION_1_KEY 0x6D
#define EXTRA_ACTION_2_KEY 0x6E
#define EXTRA_ACTION_3_KEY 0x6F

// initialize run environment
void setup() {
  // setup serial communication
  Serial.begin(9600);

  // initialize the built-in LED pin as an output
  pinMode(BUILT_IN_LED_PIN, OUTPUT);

  // turn built-in LED off
  digitalWrite(BUILT_IN_LED_PIN, LOW);

  // initialize button switch pins as inputs
  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);
  pinMode(LEFT_BUTTON_PIN, INPUT);
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(BOTTOM_ACTION_1_BUTTON_PIN, INPUT);
  pinMode(BOTTOM_ACTION_2_BUTTON_PIN, INPUT);
  pinMode(BOTTOM_ACTION_3_BUTTON_PIN, INPUT);
  pinMode(BOTTOM_ACTION_4_BUTTON_PIN, INPUT);
  pinMode(TOP_ACTION_1_BUTTON_PIN, INPUT);
  pinMode(TOP_ACTION_2_BUTTON_PIN, INPUT);
  pinMode(TOP_ACTION_3_BUTTON_PIN, INPUT);
  pinMode(TOP_ACTION_4_BUTTON_PIN, INPUT);
  pinMode(EXTRA_ACTION_1_BUTTON_PIN, INPUT);
  pinMode(EXTRA_ACTION_2_BUTTON_PIN, INPUT);
  pinMode(EXTRA_ACTION_3_BUTTON_PIN, INPUT);

  // initialize button LED pins as outputs
  pinMode(UP_LED_PIN, OUTPUT);
  pinMode(DOWN_LED_PIN, OUTPUT);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(BOTTOM_ACTION_1_LED_PIN, OUTPUT);
  pinMode(BOTTOM_ACTION_2_LED_PIN, OUTPUT);
  pinMode(BOTTOM_ACTION_3_LED_PIN, OUTPUT);
  pinMode(BOTTOM_ACTION_4_LED_PIN, OUTPUT);
  pinMode(TOP_ACTION_1_LED_PIN, OUTPUT);
  pinMode(TOP_ACTION_2_LED_PIN, OUTPUT);
  pinMode(TOP_ACTION_3_LED_PIN, OUTPUT);
  pinMode(TOP_ACTION_4_LED_PIN, OUTPUT);
  pinMode(EXTRA_ACTION_1_LED_PIN, OUTPUT);
  pinMode(EXTRA_ACTION_2_LED_PIN, OUTPUT);
  pinMode(EXTRA_ACTION_3_LED_PIN, OUTPUT);
}

// initialize cardinal direction button states
bool upButtonPressed = false;
bool downButtonPressed = false;
bool leftButtonPressed = false;
bool rightButtonPressed = false;

// initialize keyboard buffer
uint8_t keyboardBuffer[8] = { 0 };

// run main program loop
void loop() {
  upButtonPressed = digitalRead(UP_BUTTON_PIN) == HIGH;
  downButtonPressed = digitalRead(DOWN_BUTTON_PIN) == HIGH;
  leftButtonPressed = digitalRead(LEFT_BUTTON_PIN) == HIGH;
  rightButtonPressed = digitalRead(RIGHT_BUTTON_PIN) == HIGH;

  // clean vertical Simultaneous Opposing Cardinal Directions (SOCD)
  handleButton(UP_LED_PIN, UP_KEY, (upButtonPressed && downButtonPressed) || upButtonPressed);
  handleButton(DOWN_LED_PIN, DOWN_KEY, !upButtonPressed && downButtonPressed);

  // clean horizontal SOCD
  handleButton(LEFT_LED_PIN, LEFT_KEY, leftButtonPressed && !rightButtonPressed);
  handleButton(RIGHT_LED_PIN, RIGHT_KEY, rightButtonPressed && !leftButtonPressed);

  handleButton(BOTTOM_ACTION_1_LED_PIN, BOTTOM_ACTION_1_KEY, digitalRead(BOTTOM_ACTION_1_BUTTON_PIN) == HIGH);
  handleButton(BOTTOM_ACTION_2_LED_PIN, BOTTOM_ACTION_2_KEY, digitalRead(BOTTOM_ACTION_2_BUTTON_PIN) == HIGH);
  handleButton(BOTTOM_ACTION_3_LED_PIN, BOTTOM_ACTION_3_KEY, digitalRead(BOTTOM_ACTION_3_BUTTON_PIN) == HIGH);
  handleButton(BOTTOM_ACTION_4_LED_PIN, BOTTOM_ACTION_4_KEY, digitalRead(BOTTOM_ACTION_4_BUTTON_PIN) == HIGH);
  handleButton(TOP_ACTION_1_LED_PIN, TOP_ACTION_1_KEY, digitalRead(TOP_ACTION_1_BUTTON_PIN) == HIGH);
  handleButton(TOP_ACTION_2_LED_PIN, TOP_ACTION_2_KEY, digitalRead(TOP_ACTION_2_BUTTON_PIN) == HIGH);
  handleButton(TOP_ACTION_3_LED_PIN, TOP_ACTION_3_KEY, digitalRead(TOP_ACTION_3_BUTTON_PIN) == HIGH);
  handleButton(TOP_ACTION_4_LED_PIN, TOP_ACTION_4_KEY, digitalRead(TOP_ACTION_4_BUTTON_PIN) == HIGH);
  handleButton(EXTRA_ACTION_1_LED_PIN, EXTRA_ACTION_1_KEY, digitalRead(EXTRA_ACTION_1_BUTTON_PIN) == HIGH);
  handleButton(EXTRA_ACTION_2_LED_PIN, EXTRA_ACTION_2_KEY, digitalRead(EXTRA_ACTION_2_BUTTON_PIN) == HIGH);
  handleButton(EXTRA_ACTION_3_LED_PIN, EXTRA_ACTION_3_KEY, digitalRead(EXTRA_ACTION_3_BUTTON_PIN) == HIGH);
}

// handle button inputs
void handleButton(int* ledPin, uint8_t* keyCode, bool isPushed) {
  if (isPushed) {
    digitalWrite(ledPin, HIGH);

    // send keyboard input
    keyboardBuffer[2] = keyCode;
    Serial.write(keyboardBuffer, 8);

    // end keyboard buffer data stream
    keyboardBuffer[2] = 0;
    Serial.write(keyboardBuffer, 8);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
