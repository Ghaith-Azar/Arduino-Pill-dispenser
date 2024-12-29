
#include <Servo.h>  
#include <LiquidCrystal.h>

Servo servo; // create servo object

// constant variables for pins
const int servoPin = 6;
const int buttonPin = 9;
const int ledPin = 7;
const int buzzerPin = 8;

// other variables
int angle = 0;
int angleIncrement = 30;  // default 30 degrees for 12 compartments (360/12 = 30)
int newAngle;
int buttonState;
int movementDelay = 50;
int debounceDelay = 1000;

// time variables
unsigned long previousMillis = 0;  // store last time check
const unsigned long oneSecond = 1000; // number of milliseconds in one second

int year = 2024;
int month = 12;
int day = 15;
int hour = 11;
int minutes = 49;
int seconds = 50;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() { 
  pinMode(buttonPin, INPUT); // set button pin as input
  pinMode(ledPin, OUTPUT);    // set LED pin as output
  pinMode(buzzerPin, OUTPUT); // set buzzer pin as output
  digitalWrite(ledPin, LOW);  // make sure LED is off
  digitalWrite(buzzerPin, LOW);  // make sure buzzer is off
  servo.attach(servoPin);    // attach servo object to servoPin
  servo.write(angle);        // set servo to initial angle
  Serial.begin(9600);        // initialize serial for debugging

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {  
  updateTime();  // update the current time 
  updateLCD();   // display the current date and time on the screen 
  
  buttonState = digitalRead(buttonPin); // read button state 
  Serial.println(angle); // print the servo angle for debugging





  if(seconds == 0){               // check for seconds = 0 (one minute intervals)
    newAngle = angle + angleIncrement; // increase angle by increment
    if (newAngle<=180){           // if the new angle is less than or equal to 180, increase angle
    	while(angle < newAngle){    // increase angle until it reaches the new angle
      	angle = angle + 1;        // increase angle by 1
      	servo.write(angle);       // move the servo
        Serial.println(angle);    // print the angle
      	delay(movementDelay);     // delay to slow down movement
    	}
      // flash LED and buzzer
      flashLED(4,150);    // flashLED(number of flashes, delay in milliseconds), see function below
    }
    else{ // if the new angle is greater than 180, reset angle to 0
      while(angle>0){         // decrease angle until it reaches 0
        angle = angle - 1;    // decrease angle by 1
        servo.write(angle);   // move the servo
        Serial.println(angle);// print the angle
        delay(movementDelay); // delay to slow down movement
      }
    }
  }











}

void flashLED(int numFlashes, int flashDelay) {  // alarm function to flash LED and sound buzzer
  lcd.clear();              // clear the LCD screen
  lcd.setCursor(0, 0);      // set cursor to top left
  lcd.print("Take medicine!");  // display message
  for (int i = 0; i < numFlashes; i++) {  // loop to flash LED/buzzer numFlashes times
    digitalWrite(ledPin, HIGH);         // turn LED on
    digitalWrite(buzzerPin, HIGH);      // turn buzzer on
    delay(flashDelay);                 // delay
    digitalWrite(ledPin, LOW);          // turn LED off
    digitalWrite(buzzerPin, LOW);       // turn buzzer off
    delay(flashDelay);  
     digitalWrite(ledPin, HIGH);         // turn LED on
    digitalWrite(buzzerPin, HIGH);      // turn buzzer on
    delay(flashDelay);                 // delay
    digitalWrite(ledPin, LOW);          // turn LED off
    digitalWrite(buzzerPin, LOW);       // turn buzzer off
    delay(flashDelay);
     digitalWrite(ledPin, HIGH);         // turn LED on
    digitalWrite(buzzerPin, HIGH);      // turn buzzer on
    delay(flashDelay);                 // delay
    digitalWrite(ledPin, LOW);          // turn LED off
    digitalWrite(buzzerPin, LOW);       // turn buzzer off
    delay(flashDelay);
     digitalWrite(ledPin, HIGH);         // turn LED on
    digitalWrite(buzzerPin, HIGH);      // turn buzzer on
    delay(flashDelay);                 // delay
    digitalWrite(ledPin, LOW);          // turn LED off
    digitalWrite(buzzerPin, LOW);       // turn buzzer off
    delay(flashDelay);                  // delay
  }
  // wait for button press - the code will get stuck in this loop until you press the button
  while (digitalRead(buttonPin) == LOW) {}; 
  delay(1000);    // delay before clearing screen
  lcd.clear();    // clear screen
}

void updateTime() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= oneSecond) {
    previousMillis = currentMillis;
    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60) {
      minutes = 0;
      hour++;
    }
    if (hour >= 24) {
      hour = 0;
      day++;
    }
    // Handle month-end dates here if desired, simple example for 30-day months:
    if (day > 30) {  
      day = 1;
      month++;
    }
    if (month > 12) {
      month = 1;
      year++;
    }
  }
}

void updateLCD() {  
  lcd.setCursor(0, 0);
  if (month < 10) lcd.print(" ");
  lcd.print(month);
  lcd.print("/");
  if (day < 10) lcd.print(" ");
  lcd.print(day);
  lcd.print("/");
  lcd.print(year);

  lcd.setCursor(0, 1);
  if (hour < 10) lcd.print("0");
  lcd.print(hour);
  lcd.print(":");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
}
