// Обозначение пинов
#define PIN_BUTTON 11

#define PIN_SENS_R A0
#define PIN_SENS_L A1

#define PIN_MOTOR_SPEED_R 5
#define PIN_MOTOR_SPEED_L 6
#define PIN_MOTOR_DIR_R 4
#define PIN_MOTOR_DIR_L 7

enum STATE {both_w, one_b, both_b};
enum MODE {search_mode, take_pos_mode, straight_mode, turn_mode, back_mode};
enum SENS {left, right};

void search();
void take_pos();
void straight();
void turn();
void back();

void (*(actions[5]))() = {search, take_pos, straight, turn, back};

void stop();


// Глобальные переменные состояний
int LAST_ON_BLACK = 0;
int CURRENT_MODE = search_mode;

// Глобальные константы для настройки работы алгоритмов
const int BLACK_VAL = 750;
const int STOP_SPEED = -50; 
const int IDLE_SPEED = 110;
const int SPEED = 225;
int MAX_DIF = 300;

bool IS_ON = false;
float SENSORS_BALANCING;

void setup() {
  Serial.begin(9600);
  SENSORS_BALANCING =(analogRead(PIN_SENS_L) - analogRead(PIN_SENS_R));
}


int check_state(){
  int sen_state = check_black(left) + check_black(right);  
  delay(10);
  return sen_state;
}


bool check_black(int sensor){
  int val = 0.0;
  if (sensor == left){
    val = analogRead(PIN_SENS_L);
  } 
  if (sensor == right){
    val = analogRead(PIN_SENS_R);
  }

  if (val >= BLACK_VAL){
    LAST_ON_BLACK = sensor;
    return true;
  } 
  else{
    return false;
  }
}


void stop(){
  int val_l = STOP_SPEED;
  int val_r = STOP_SPEED;

  run_motor(val_l,val_r); 
  delay(100);
}


void back(){
  int val_l;
  int val_r;
  static int iterations = 0;
  if(LAST_ON_BLACK == left){
    val_l = -IDLE_SPEED;
    val_r = -IDLE_SPEED * 0.8;
  }
  else{
    val_l = -IDLE_SPEED * 0.8;
    val_r = -IDLE_SPEED;
  }
  run_motor(val_l,val_r);

  iterations++;

  if(iterations >= 50){
    CURRENT_MODE = search_mode;
    iterations = 0;
    return;
  }

  switch(check_state()){
    case both_b:
      CURRENT_MODE = straight_mode;
      iterations = 0;
      break;
    case one_b:
      CURRENT_MODE = turn_mode;
      iterations = 0;
      break;
  }
}


void search(){
  static float motor_koeff = 0.0;
  static float time = 0.0;
  static int period = 20;

  run_motor(SPEED, IDLE_SPEED * motor_koeff);
  
  time += 1.0;
  if(time > period){
    time = 0.0;
    motor_koeff = constrain(motor_koeff + 0.25 * (1 - motor_koeff), 0.0, 1.0);
    period *= 2;
  }


  switch(check_state()){
    case one_b:
      stop();
      CURRENT_MODE = take_pos_mode;
      motor_koeff = 0.0;
      period = 20;
      break;
    case both_b:
      stop();
      CURRENT_MODE = straight_mode;
      motor_koeff = 0.0;
      period = 20;
      break;
  }
  delay(100);
}


void take_pos(){
  float diff = analogRead(PIN_SENS_L) - analogRead(PIN_SENS_R) - SENSORS_BALANCING;
  diff = float(constrain(diff, -MAX_DIF, MAX_DIF) / MAX_DIF);
  diff = pow(diff, 1.4);
  
  int val_l = map(int(255 * (diff)), -255, 255, 0, 2*IDLE_SPEED);
  int val_r = map(int(255 * (-diff)), -255, 255, 0, 2*IDLE_SPEED);


  run_motor(val_l, val_r);
  
  switch(check_state()){
    case both_b:
      CURRENT_MODE = straight_mode;
      break;
    case both_w:
      CURRENT_MODE = back_mode;
  }
}


void straight(){
  float diff = analogRead(PIN_SENS_L) - analogRead(PIN_SENS_R) - SENSORS_BALANCING;
  diff = float(constrain(diff, -MAX_DIF, MAX_DIF) / MAX_DIF);

  int val_l = map(int(255 * (-diff)), -255, 255, 0, SPEED);
  int val_r = map(int(255 * (diff)), -255, 255, 0, SPEED);

  run_motor(val_l,val_r);

  switch(check_state()){
    case one_b:
      stop();
      CURRENT_MODE = turn_mode;
      break;
    case both_w:
      CURRENT_MODE = back_mode;
      break;
  }
}


void turn(){
  int val_l;
  int val_r;
  if (LAST_ON_BLACK == left){
    val_l = STOP_SPEED;
    val_r = SPEED;
  }
  else{
    val_l = SPEED;
    val_r = STOP_SPEED;
  }
  

  run_motor(val_l, val_r);

  switch(check_state()){
    case both_b:
      CURRENT_MODE = straight_mode;
      break;
    case both_w:
      CURRENT_MODE = back_mode;
      break;
  }
}


void run_motor(int val_l, int val_r){
  int dir_l;
  int dir_r;

  val_l = constrain(val_l, -250, 250);
  val_r = constrain(val_r, -250, 250);

  if (val_l > 0){
    dir_l = HIGH;
  }
  else{
    dir_l = LOW;
  }

  if (val_r > 0){
    dir_r = HIGH;
  }
  else{
    dir_r = LOW;
  }

  digitalWrite(PIN_MOTOR_DIR_L,dir_l);
  digitalWrite(PIN_MOTOR_DIR_R,dir_r);

  analogWrite(PIN_MOTOR_SPEED_L, abs(val_l));
  analogWrite(PIN_MOTOR_SPEED_R, abs(val_r));
}


void proceed(int mode){
  (*actions[mode])();
}


void loop() {
  // Считывание кнопки
  if (digitalRead(PIN_BUTTON) == HIGH){
    IS_ON = not IS_ON;
    CURRENT_MODE = 0;
    delay(1000);
  }
  
  // Обработка режима
  if (IS_ON){
    proceed(CURRENT_MODE);
  }
  else{
    // Выключение моторов
    digitalWrite(6,LOW);
    digitalWrite(5,LOW);
  }
}
