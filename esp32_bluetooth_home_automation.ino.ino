#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define RED 14
#define BLUE 27
#define GREEN 13
#define WHITE 12

char mode = 0;

void showMainMenu() {
  SerialBT.println("\n=== MAIN MENU ===");
  SerialBT.println("1. Individual LED Control");
  SerialBT.println("2. LED Chasing");
  SerialBT.println("3. All LEDs Blinking");
  SerialBT.println("Select option:");
}

void setup() {
  Serial.begin(115200);

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(WHITE, OUTPUT);

  SerialBT.begin("ESP32_Menu_System");

  delay(1000);
  showMainMenu();
}

void loop() {

  // Read mode selection
  if (SerialBT.available()) {
    mode = SerialBT.read();
  }

  // -------- MODE 1: Individual Control --------
  if (mode == '1') {
    SerialBT.println("\nIndividual Control:");
    SerialBT.println("R/r, B/b, G/g, W/w");

    while (1) {
      if (SerialBT.available()) {
        char cmd = SerialBT.read();

        if (cmd == 'R') digitalWrite(RED, HIGH);
        else if (cmd == 'r') digitalWrite(RED, LOW);

        else if (cmd == 'B') digitalWrite(BLUE, HIGH);
        else if (cmd == 'b') digitalWrite(BLUE, LOW);

        else if (cmd == 'G') digitalWrite(GREEN, HIGH);
        else if (cmd == 'g') digitalWrite(GREEN, LOW);

        else if (cmd == 'W') digitalWrite(WHITE, HIGH);
        else if (cmd == 'w') digitalWrite(WHITE, LOW);

        else if (cmd == '0') { // Exit mode
          mode = 0;
          showMainMenu();
          break;
        }
      }
    }
  }

  // -------- MODE 2: LED CHASING --------
  else if (mode == '2') {
    SerialBT.println("\nLED Chasing Mode (press 0 to exit)");

    while (1) {

      digitalWrite(RED, HIGH); delay(300); digitalWrite(RED, LOW);
      digitalWrite(BLUE, HIGH); delay(300); digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, HIGH); delay(300); digitalWrite(GREEN, LOW);
      digitalWrite(WHITE, HIGH); delay(300); digitalWrite(WHITE, LOW);

      if (SerialBT.available()) {
        char cmd = SerialBT.read();
        if (cmd == '0') {
          mode = 0;
          showMainMenu();
          break;
        }
      }
    }
  }

  // -------- MODE 3: ALL BLINK --------
  else if (mode == '3') {
    SerialBT.println("\nBlinking Mode (press 0 to exit)");

    while (1) {

      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(WHITE, HIGH);
      delay(500);

      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(WHITE, LOW);
      delay(500);

      if (SerialBT.available()) {
        char cmd = SerialBT.read();
        if (cmd == '0') {
          mode = 0;
          showMainMenu();
          break;
        }
      }
    }
  }
}