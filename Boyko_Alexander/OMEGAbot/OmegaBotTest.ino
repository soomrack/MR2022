
#define BUT_PIN 11
#define SOUND_PIN 10

#define SEN_PIN_R A0
#define SEN_PIN_L A1

#define MOT_SPEED_PIN_R 5
#define MOT_SPEED_PIN_L 6
#define MOT_DIR_PIN_R 4
#define MOT_DIR_PIN_L 7

enum STATE {both_w, one_b, both_b};
enum MODE {search_line, set_line, smooth_line, turn_line, arc_line, back_line};
enum SENS {left, right};

void search();
void get_on_line();
void straight();
void stop();
void arc();
void back();

void (*(actions[6]))() = {search, get_on_line, straight, stop, arc, back};

int LAST_ON_BLACK = 0;
int CURRENT_MODE = search_line;
float CURRENT_CURVATURE = 0.0;
const float DELTA_CURVATURE = 0.01;
int BLACK_VAL = 750;

const int STOP_SPEED = -50; 
const int IDLE_SPEED = 90;
const int SPEED = 225;
int MAX_VAL = 300;

bool IS_ON = false;
float BALANCE_SENSORS;

void setup() {
  Serial.begin(9600);
  //BALANCE_SENSORS = float(analogRead(A1))/float(analogRead(A0));
  BALANCE_SENSORS =(analogRead(SEN_PIN_L) - analogRead(SEN_PIN_R));
  //BLACK_VAL = (analogRead(SEN_PIN_L) + analogRead(SEN_PIN_R)) / 2;
  peep();
}


void readLight(){
  Serial.print("Right ");
  Serial.print(analogRead(A0));  
  Serial.print(" Left ");
  Serial.print(analogRead(A1));
}

int check_state(){
  int sen_state = check_black(left) + check_black(right);
  
  delay(10);
  return sen_state;
}


bool check_black(int sensor){
  int val = 0.0;
  if (sensor == left){
    val = analogRead(SEN_PIN_L);
  } 
  if (sensor == right){
    val = analogRead(SEN_PIN_R);
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
  int val_l = 0;
  int val_r = 0;

  run_motor(val_l,val_r); 
}


void back(){

  static int iterations = 0;

  int val_l = -IDLE_SPEED;
  int val_r = -IDLE_SPEED;

  run_motor(val_l,val_r);

  iterations++;

  if(iterations >= 50){
    CURRENT_MODE = search_line;
    iterations = 0;
    return;
  }

  switch(check_state()){
    case both_b:
      CURRENT_MODE = smooth_line;
      iterations = 0;
      break;
    case one_b:
      CURRENT_MODE = smooth_line;
      iterations = 0;
      break;
  }
}


void search(){
  static float motor_speed = 20.0;

  run_motor(IDLE_SPEED * 2,motor_speed);
  motor_speed = constrain(motor_speed + 0.05, 0.0, IDLE_SPEED);

  switch(check_state()){
    case one_b:
      CURRENT_MODE = set_line;
      motor_speed = 20.0;
      break;
    case both_b:
      CURRENT_MODE = smooth_line;
      motor_speed = 20.0;
      break;
  }
}


void get_on_line(){
  float diff = analogRead(SEN_PIN_L) - analogRead(SEN_PIN_R) - BALANCE_SENSORS;
  diff = float(constrain(diff,-MAX_VAL,MAX_VAL) / MAX_VAL);
  float diff_old = diff;
  diff = pow(diff,1.4);
  
  int val_l = map(int(255 * (diff)),-255,255,0,2*IDLE_SPEED);
  int val_r = map(int(255 * (-diff)),-255,255,0,2*IDLE_SPEED);


  run_motor(val_l,val_r);
  
  switch(check_state()){
    case both_b:
      CURRENT_MODE = smooth_line;
      break;
  }
}


void straight(){
  float diff = analogRead(SEN_PIN_L) - analogRead(SEN_PIN_R) - BALANCE_SENSORS;
  diff = float(constrain(pow(diff,1.5),-MAX_VAL,MAX_VAL) / MAX_VAL);
  float diff_old = diff;
  
  CURRENT_CURVATURE = diff;

  int val_l = map(int(255 * (-diff)), -255, 255, 0, SPEED);
  int val_r = map(int(255 * (diff)), -255, 255, 0, SPEED);

  run_motor(val_l,val_r);

  switch(check_state()){
    case one_b:
      CURRENT_MODE = arc_line;
      break;
    case both_w:
      CURRENT_MODE = back_line;
      break;
  }
}


void arc(){
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
      CURRENT_MODE = smooth_line;
      break;
    case both_w:
      CURRENT_MODE = back_line;
      break;
  }
}


void arc_old(){
  static float current_speed = STOP_SPEED;
  if (LAST_ON_BLACK == left){
    CURRENT_CURVATURE += DELTA_CURVATURE;
  }
  else{
    CURRENT_CURVATURE -= DELTA_CURVATURE;
  }
  CURRENT_CURVATURE = constrain(CURRENT_CURVATURE, -1, 1);

  int val_l = map(int(255 * (-CURRENT_CURVATURE)), -255, 255, -10, current_speed);
  int val_r = map(int(255 * (CURRENT_CURVATURE)), -255, 255, -10, current_speed);

  current_speed = constrain(current_speed, STOP_SPEED, 1.5*IDLE_SPEED);  

  Serial.print("CURRENT_CURVATURE ");
  Serial.print(CURRENT_CURVATURE, " ");

  run_motor(val_l, val_r);

  current_speed += 15;


  switch(check_state()){
    case both_b:
      CURRENT_MODE = smooth_line;
      current_speed = STOP_SPEED;
      break;
  }
}


void peep(){
  digitalWrite(SOUND_PIN,HIGH);
  delay(1000);
  digitalWrite(SOUND_PIN,LOW);
}

void run_motor(int val_l, int val_r){
  int dir_l;
  int dir_r;

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

  Serial.print(CURRENT_MODE);
  Serial.print(" LOB ");
  Serial.print(LAST_ON_BLACK);
  Serial.print(" Left ");
  Serial.print(val_l);
  Serial.print(" Right ");
  Serial.println(val_r);

  digitalWrite(MOT_DIR_PIN_L,dir_l);
  digitalWrite(MOT_DIR_PIN_R,dir_r);

  analogWrite(MOT_SPEED_PIN_L, abs(val_l));
  analogWrite(MOT_SPEED_PIN_R, abs(val_r));
}


void proceed(int mode){
  (*actions[mode])();
}


void loop() {
  if (digitalRead(BUT_PIN) == HIGH){
    IS_ON = not IS_ON;
    CURRENT_MODE = 0;
    delay(1000);
  }
  
  

  if (IS_ON){
    proceed(CURRENT_MODE);
  }
  else{
    digitalWrite(6,LOW);
    digitalWrite(5,LOW);
  }
}
