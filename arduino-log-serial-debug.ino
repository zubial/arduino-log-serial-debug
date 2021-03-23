/*
  Log serial debug module

*/
#include <LiquidCrystal.h>

// Hardware settings
const int displayLines = 2;
const int displayLineSymbols = 16;
const int displayRsPin = 12, displayEnPin = 11, displayD4Pin = 5, displayD5Pin = 4, displayD6Pin = 3, displayD7Pin = 2;
const int repeatButtonPin = 8;

// Init variables
LiquidCrystal lcd(displayRsPin, displayEnPin, displayD4Pin, displayD5Pin, displayD6Pin, displayD7Pin);

String displayString = "";
String lastDisplayString = "";


void setup() {
  lcd.begin(displayLineSymbols, displayLines);

  displayText("Log serial debug module", 0);
  
  pinMode(repeatButtonPin, INPUT);
  
  Serial.begin(9600);
}


void loop() {
  if (Serial.available()) {
    delay(100);

    while (Serial.available() > 0) {
      int inChar = Serial.read();
      
      // if you get a newline, print the string, then the string's value:
      if (inChar == '\n') {
        displayText(displayString, 1);
        lastDisplayString = displayString;
        
        // clear the string for new input
        displayString = "";
      } else {
        displayString += (char)inChar;
      }
    }
  }
  // Check pushButton for repeat display.
  if (digitalRead(repeatButtonPin) == LOW) {
    Serial.println("pushed");
    displayText(lastDisplayString, 1);
  }
}

void displayText(String text, int line) {
  if (text.length() > displayLineSymbols) {
    for (int i = 0; i < (text.length()-(displayLineSymbols-5)); i++) {
      clearLine(line);
      lcd.print(text.substring(i));
      Serial.println(text.substring(i));
      delay(500);
    }
    clearLine(line);
    lcd.print(text);
  } else {
    clearLine(line);
    lcd.print(text);
  }
}

void clearLine(int line) {
  for(int n = 0; n < displayLineSymbols; n++) {
   lcd.setCursor(n,line);
   lcd.print(" ");
  }
  lcd.setCursor(0,line);
}

