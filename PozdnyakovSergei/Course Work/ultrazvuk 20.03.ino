#include <Servo.h>

const int echoPin = 19;  // Цифровой порт для подачи сигнала
const int triggerPin = 18;  // Цифровой порт для снятия сигнала
const int buttonPin = 11;
bool val;
int buttonState;


Servo D5, D4;  // Right
Servo D6, D7;  // Left


void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (buttonPin, INPUT);
  val = false;
  buttonState = 0;


  D5.attach(5), D4.attach(4);  // Правые двигатели
  D6.attach(6), D7.attach(7);  // Левые двигатели
}


//int checkButton() {
//  int buttonState = 0;
//  byte val = false;
//  buttonState = digitalRead(buttonPin);
//  if (buttonState == HIGH){
//    val = !val;
//    }
//    return val;
//}


void loop() {
  
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
     val = !val;
     
  if (val == true){
    
  int dur, sm;
  int left_speed, right_speed;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  dur = pulseIn(echoPin, HIGH);
  sm = dur / 58;  // можно добавить -4 с учетом расстояния до бампера
  Serial.print("Distance is ");
  Serial.print(sm);
  Serial.println(" sm");  // Выводит расстояние до препятствия по прямой, но пока корректно работает при перпендекулярных препятствиях
  delay(100);

  if (sm > 2) {
    D5.write(sm);
    D4.write(sm);
    D6.write(sm);
    D7.write(sm);
  }
  }

  else {
    D5.write(LOW);
    D4.write(LOW);
    D6.write(LOW);
    D7.write(LOW);
    }
    }
}
