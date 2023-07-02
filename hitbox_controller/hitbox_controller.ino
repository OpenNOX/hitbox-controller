#define BUILT_IN_LED_PIN 13
#define UP_BUTTON_PIN 22
#define UP_LED_PIN 23
#define DOWN_BUTTON_PIN 24
#define DOWN_LED_PIN 25
#define LEFT_BUTTON_PIN 26
#define LEFT_LED_PIN 27
#define RIGHT_BUTTON_PIN 28
#define RIGHT_LED_PIN 29
#define BOTTOM_ACTION_1_BUTTON_PIN 30
#define BOTTOM_ACTION_1_LED_PIN 31
#define BOTTOM_ACTION_2_BUTTON_PIN 32
#define BOTTOM_ACTION_2_LED_PIN 33
#define BOTTOM_ACTION_3_BUTTON_PIN 34
#define BOTTOM_ACTION_3_LED_PIN 35
#define BOTTOM_ACTION_4_BUTTON_PIN 36
#define BOTTOM_ACTION_4_LED_PIN 37
#define TOP_ACTION_1_BUTTON_PIN 38
#define TOP_ACTION_1_LED_PIN 39
#define TOP_ACTION_2_BUTTON_PIN 40
#define TOP_ACTION_2_LED_PIN 41
#define TOP_ACTION_3_BUTTON_PIN 42
#define TOP_ACTION_3_LED_PIN 43
#define TOP_ACTION_4_BUTTON_PIN 44
#define TOP_ACTION_4_LED_PIN 45
#define EXTRA_ACTION_1_BUTTON_PIN 46
#define EXTRA_ACTION_1_LED_PIN 47
#define EXTRA_ACTION_2_BUTTON_PIN 48
#define EXTRA_ACTION_2_LED_PIN 49
#define EXTRA_ACTION_3_BUTTON_PIN 50
#define EXTRA_ACTION_3_LED_PIN 51

void setup() {
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

bool upButtonPressed = false;
bool downButtonPressed = false;
int leftButtonState = 0;
int rightButtonState = 0;

void loop() {  
  upButtonPressed = digitalRead(UP_BUTTON_PIN) == HIGH;
  downButtonPressed = digitalRead(DOWN_BUTTON_PIN) == HIGH;
  leftButtonState = digitalRead(LEFT_BUTTON_PIN);
  rightButtonState = digitalRead(RIGHT_BUTTON_PIN);

  // clean vertical Simultaneous Opposing Cardinal Directions (SOCD)
  if ((upButtonPressed && downButtonPressed) || upButtonPressed) {
    digitalWrite(UP_LED_PIN, HIGH);
  } else if (downButtonPressed) {
    digitalWrite(DOWN_LED_PIN, HIGH);
  }

  // clean horizontal SOCD
  if (leftButtonState == LOW || rightButtonState == LOW) {
    digitalWrite(LEFT_LED_PIN, leftButtonState);
    digitalWrite(RIGHT_LED_PIN, rightButtonState);
  }

  digitalWrite(BOTTOM_ACTION_1_LED_PIN, digitalRead(BOTTOM_ACTION_1_BUTTON_PIN));
  digitalWrite(BOTTOM_ACTION_2_LED_PIN, digitalRead(BOTTOM_ACTION_2_BUTTON_PIN));
  digitalWrite(BOTTOM_ACTION_3_LED_PIN, digitalRead(BOTTOM_ACTION_3_BUTTON_PIN));
  digitalWrite(BOTTOM_ACTION_4_LED_PIN, digitalRead(BOTTOM_ACTION_4_BUTTON_PIN));
  digitalWrite(TOP_ACTION_1_LED_PIN, digitalRead(TOP_ACTION_1_BUTTON_PIN));
  digitalWrite(TOP_ACTION_2_LED_PIN, digitalRead(TOP_ACTION_2_BUTTON_PIN));
  digitalWrite(TOP_ACTION_3_LED_PIN, digitalRead(TOP_ACTION_3_BUTTON_PIN));
  digitalWrite(TOP_ACTION_4_LED_PIN, digitalRead(TOP_ACTION_4_BUTTON_PIN));
  digitalWrite(EXTRA_ACTION_1_LED_PIN, digitalRead(EXTRA_ACTION_1_BUTTON_PIN));
  digitalWrite(EXTRA_ACTION_2_LED_PIN, digitalRead(EXTRA_ACTION_2_BUTTON_PIN));
  digitalWrite(EXTRA_ACTION_3_LED_PIN, digitalRead(EXTRA_ACTION_3_BUTTON_PIN));
}
