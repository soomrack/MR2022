#include <Servo.h>
//#include <Ultrasonik.h>


#define echoPin 19  // приемник
#define trigPin 18  // источник

#define buttonPin 8  // кнопка включения и отключения
#define note_pin 10  // оповещение о приближении

#define speed_pin_r 5  // скорость правых моторов
#define speed_pin_l 6  // скорость левых моторов
#define dur_pin_r 4  // направление правых моторов
#define dur_pin_l 7  // направление левых моторов

bool is_on = false;  // для кнопки включения
bool button_state = false;
float time = 0.0;
int sound_time = 0;  // время оповещения
float filt_param = 0.2;  // параметр для фильтрации
float dist_filt = 0;  // отфильтрованный выход
float dur_param = 29.1;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);

  analogWrite(note_pin, 200);
  delay(200);
  analogWrite(note_pin, 0);

}


void start_motors () {

}


int get_distance() {
  long dur, sm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
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


int dist_filtered() {
  int dist = get_distance();
  dist_filt += (dist - dist_filt) * filt_param;
  return (dist_filt);
}


int sound_tim() {
  int sound = dist_filtered();
  int sound_time = map(sound, 0, 255, 700, 100);
  analogWrite(note_pin, sound_time);
  return (sound_time);
}


void sound() {
  int tim = sound_tim();
  analogWrite(note_pin, 200);
  delay(tim);
  analogWrite(note_pin, 0);
  delay(tim);
}


bool check_button() {
  if (digitalRead (buttonPin) == HIGH) {
    button_state = not button_state;
    delay(100);
  }
  return button_state;
}


void loop() {
  bool is_on = check_button();

  if (is_on) {
    start_motors();
  }
  
  else {
    digitalWrite(speed_pin_r, LOW);
    digitalWrite(speed_pin_l, LOW);
    digitalWrite(dur_pin_r, LOW);
    digitalWrite(dur_pin_l, LOW);
    }
}