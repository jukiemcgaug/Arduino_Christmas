#include <Servo.h>
#include <LiquidCrystal.h>

const int ON_BUTTON_PIN = 2;

const int LIGHT_BUTTON_PIN = 3;
const int SAVE_PIN = 4;

const int RED_PIN = 5;
const int GREEN_PIN = 6;
const int YELLOW_PIN = 7;

const int CHAR_1_PIN = 8;
const int LADDER_PIN = 9;
const int ROPE_PIN = 10;

Servo char1;
Servo ladder;
Servo rope;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int onButton = 1;
int onState = 0;

int lightButton = 1;
int lightState = 0;

int saveButton = 1;
int saveState = 0;

int char1Pos = 40;
int ladderPos = 0;
int ropePos = 92;

void setup() {
  char1.attach(CHAR_1_PIN);
  char1.write(char1Pos);

  ladder.attach(LADDER_PIN);
  ladder.write(ladderPos);

  rope.attach(ROPE_PIN);
  rope.write(ropePos);

  pinMode(ON_BUTTON_PIN, INPUT_PULLUP);

  pinMode(LIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);

  pinMode(SAVE_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Press red button");

  lcd.setCursor(0, 1);
  lcd.print(" to start/stop. ");
}

void loop() {

  onButton = digitalRead(ON_BUTTON_PIN);
  lightButton = digitalRead(LIGHT_BUTTON_PIN);
  saveButton = digitalRead(SAVE_PIN);

  digitalWrite(RED_PIN, lightState);
  digitalWrite(GREEN_PIN, lightState);
  digitalWrite(YELLOW_PIN, lightState);

  if (onButton == LOW) {
    onState = 1;
  }

  while (onState == 1) {
    while (lightState == 0) {
      if (saveState == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Goals: save man");

        lcd.setCursor(0, 1);
        lcd.print("+ keep lights on");
      }

      for (char1Pos = 40; char1Pos >= 0; char1Pos -= 1) {
        char1.write(char1Pos);
        delay(15);
      }

      for (long i = 0; i < 40000; i++) {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(YELLOW_PIN, HIGH);

        lightButton = digitalRead(LIGHT_BUTTON_PIN);
        if (lightButton == LOW) {
          lightState = 1;
          break;
        }
      }

      if (lightState == 0) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(YELLOW_PIN, LOW);

        for (char1Pos = 0; char1Pos <= 40; char1Pos += 1) {
          char1.write(char1Pos);
          delay(15);
        }
      }
    }

    saveButton = digitalRead(SAVE_PIN);

    if (saveButton == LOW) {
      saveState = 1;
    } 

    if (saveState == 1) {
      for (ladderPos = 0; ladderPos <= 40; ladderPos += 1) {
        ladder.write(ladderPos);
        delay(15);
      }

      delay(1000);
      
      for (int i = 1000; i >= 0; i -= 10) {
        rope.writeMicroseconds(i);
        delay(25);
      }
      rope.write(92);

      saveState = 0;

      lcd.setCursor(0, 0);
      lcd.print("    Success!    ");

      lcd.setCursor(0, 1);
      lcd.print("Happy holidays!!");
    }

    onButton = digitalRead(ON_BUTTON_PIN);

    if (onButton == LOW) {
      reset();
      delay(1000);
    }
  }
}

void reset() {
  onState = 0;
  lightState = 0;
  saveState = 0;

  for (ladderPos = 0; ladderPos <= 40; ladderPos -= 1) {
    ladder.write(ladderPos);
    delay(15);
  }

  for (char1Pos = 0; char1Pos <= 40; char1Pos += 1) {
    char1.write(char1Pos);
    delay(15);
  }


  lcd.setCursor(0, 0);
  lcd.print("Press red button");

  lcd.setCursor(0, 1);
  lcd.print(" to start/stop. ");
}