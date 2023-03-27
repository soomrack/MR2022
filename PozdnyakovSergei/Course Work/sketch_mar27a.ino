#include <Servo.h>

const int schoPin = 19;
const int trigPin = 18;
const int buttonPin = 8;
bool val;
int buttonState;

Servo D5, D4;
Servo D6, D7;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  val = false;
  buttonState = 0;

  D5.attach(5), D4.attach(4);
  D6.attach(6), D7.attach(7);
}


void checkButton() {  // Функция для проверки состояния кнопки
//    int buttonState = 0;
//    bool val = false;
    buttonState = digitalRead(buttpnPin);
    if (buttonState = HIGH) {
      val = !val;
      }
      return val;
}


void sensor() {
  int dur, sm;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  dur = pulseIn(echoPin, HIGH);
  sm = dur / 58;
  Serial.print("Distance is ");
  Serial.print(sm);
  Serial.print("sm");
  delay(100);
  sm = map(sm, 0, 350, 0, 255);
}


void motors() {
  int left_speed, right_speed;
  if (val == true) {
    if (sm > 50) {
       left_speed = sm;
       right_speed = sm;
      }
      else {
        left_speed = 0;
        right_speed = 0
        }
      D5.write(left_speed);
      D4.write(left_speed);
      D6.write(right_speed);
      D7.write(right_speed);
    }  
}


void loop() {
  check_button();
  sensor();
  motors();
}
