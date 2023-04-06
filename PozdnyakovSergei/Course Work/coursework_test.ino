#include <Servo.h>
//#include <Ultrasonik.h>


#define echoPin = 19  // приемник
#define trigPin = 18  // источник

#define buttonPin = 8  // кнопка включения и отключения
#define note_pin = 10  // оповещение о приближении

#define speed_pin_r = 5  // скорость правых моторов
#define speed_pin_l = 6  // скорость левых моторов
#define dur_pin_r = 4  // направление правых моторов
#define dur_pin_l = 7  // направление левых моторов

bool is_on = false;  // для кнопки включения
float time = 0.0;
int soudn_time = 0;  // время оповещения
float filt_param = 0.2;  // параметр для фильтрации
float dist_filt = 0;  // отфильтрованный выход
float dur_param = 29.1;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);

  note_pin = analogWrite(200);
  delay(200);
  note_pin = analogWrite(0);

}


void sound() {
  note_pin = analogWrite(200);
  delay(sound_time);
  note_pin = analogWrite(0);
  delay(sound_time);
}


void start_motors () {
}


float get_distance() {
  long dur, sm;
  trigPin = digitalWrite(LOW);
  delayMicroseconds(2);
  trigPin = digitalWrite(HIGH);
  delayMicroseconds(10);
  trigPin = digitalWrite(LOW);
  dur = pulseIn(echoPin, HIGH);
  sm = (dur / 2) / dur_param;  // перевод показаний датчика в сантиметры
  Serial.print("Distance is ");
  Serial.print(sm);
  Serial.print(" sm");
  delay(100);
  sm = map(sm, 0, 350, 0, 255);
  //sound_time = map(sm, 0, 255, 700, 100);
  return (sm);
}


void sound() {
  sm = dist_filtered();
  sound_time = map(sm, 0, 255, 700, 100);
  note_pin = analogWrite(sound_time);
  //returm (sound_time);
}


void dist_filtered() {
  float dist = get_distance();
  dist_filt += (dist - dist_filt) * filt_param;
  return (dist_filt);
}


void loop() {
  if (digitalRead (buttonPin) == HIGH) {
    is_on = not is_on;
    current mode = 0;
    delay(1000);
  }

  if (is_on) {
    start;
  }
  
  else {
    speed_pin_r = digitalWrite(LOW);
    speed_pin_l = digitalWrite(LOW);
  }
}