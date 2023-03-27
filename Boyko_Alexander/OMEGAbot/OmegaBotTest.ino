
#define BUT_PIN 11
#define SOUND_PIN 10

#define SEN_PIN_R A0
#define SEN_PIN_L A1

#define MOT_SPEED_PIN_R 5
#define MOT_SPEED_PIN_L 6
#define MOT_DIR_PIN_R 4
#define MOT_DIR_PIN_L 7

enum STATE {both_w,one_b,both_b};
enum MODE {search_line,set_line,extra_set_line,smooth_line,turn_line,arc_line,back_line};
enum SENS {left,right};

int last_on_black = 0;
int current_mode = search_line;
float current_curvature = 0.0;
const float DELTA_CURVATURE = 0.01;
int black_val = 750;

float P_koef = 2;
float I_koef = 0.0;
float D_koef = 0.0;

const float IDLE_SPEED = 90;
const float SPEED = 100;
int max_val = 300;

bool is_on_line = false;
bool is_ON = false;
float balance;
float left_balance;
float right_balance;


float time = 0.0;

void setup() {
  Serial.begin(9600);
  //balance = float(analogRead(A1))/float(analogRead(A0));
  balance =(analogRead(SEN_PIN_L) - analogRead(SEN_PIN_R));
  left_balance = analogRead(SEN_PIN_L);
  right_balance = analogRead(SEN_PIN_R);
  analogWrite(SOUND_PIN,200);
  delay(200);
  analogWrite(SOUND_PIN,0);
}

void readLight(){
  Serial.print("Right ");
  Serial.print(analogRead(A0));  
  Serial.print(" Left ");
  Serial.print(analogRead(A1));
}


void black_white(){
  int mode = 0;

  mode = check_line();
  set_mode(mode);

  delay(200);
}

void set_mode(int new_mode){
  switch(new_mode){
    case search_line:
      search();
      break;
    case set_line:
      turn_on_line();
      break;
    case extra_set_line:
      turn_on_line();
      break;
    case smooth_line:
      straight_line();
      break;
    case back_line:
      back();
      break;
    default:
      stop();
      break;
  }
  current_mode = new_mode;
  Serial.print(new_mode);
}

int check_line(){

  int sen_state = check_black(analogRead(SEN_PIN_L)) + check_black(analogRead(SEN_PIN_R));
  
  switch(current_mode){
    case search_line:
      switch(sen_state){
        case one_b:
          return set_line;
        case both_b:
          return smooth_line;
        default:
          return current_mode;
      }
      break;
    case set_line:
      switch(sen_state){
        case both_b:
          return smooth_line;
        //case both_w:
          //change_mode(back_line);
        default:
          return current_mode;
      }
      break;
    case smooth_line:
      switch(sen_state){
        case both_w:
          return back_line;
        //case one_b:
          //change_mode(turn_line);
        default:
          return current_mode;
      }
      break;
    case back_line:
      switch(sen_state){
        case both_b:
          return smooth_line;
        case one_b:
          return smooth_line;
      }
      break;
    default:
      return search_line;
    delay(10);
  }

  Serial.print("LeftSen ");
  Serial.print(analogRead(SEN_PIN_L));
  Serial.print(" RightSen ");
  Serial.print(analogRead(SEN_PIN_R));
  Serial.print(" Is on line ");
  Serial.print(sen_state);
}

bool check_black(int sensor){
  int val;
  if (sensor == left){
    val = analogRead(SEN_PIN_L);
  } 
  if (sensor == right){
    val = analogRead(SEN_PIN_R);
  }

  if (val >= black_val){
    last_on_black = sensor;
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
  int val_l = -IDLE_SPEED;
  int val_r = -IDLE_SPEED;

  run_motor(val_l,val_r);
}

void search(){
  int val_l = IDLE_SPEED;
  int val_r = IDLE_SPEED;

  run_motor(val_l,val_r);
}

void turn_on_line(){
  float diff = analogRead(SEN_PIN_L) - analogRead(SEN_PIN_R) - balance;
  diff = float(constrain(diff,-max_val,max_val) / max_val);
  float diff_old = diff;
  diff = pow(diff,1.4);
  
  int val_l = map(int(255 * (diff)),-255,255,0,2*IDLE_SPEED);
  int val_r = map(int(255 * (-diff)),-255,255,0,2*IDLE_SPEED);


  run_motor(val_l,val_r);
  
}

void straight_line(){
  float diff = analogRead(SEN_PIN_L) - analogRead(SEN_PIN_R) - balance;
  diff = float(constrain(diff,-max_val,max_val) / max_val);
  float diff_old = diff;
  
  int val_l = map(int(255 * (-diff)),-255,255,0,2*IDLE_SPEED);
  int val_r = map(int(255 * (diff)),-255,255,0,2*IDLE_SPEED);

  run_motor(val_l,val_r);
}

void arc(){
  if (last_on_black == left){
    current_curvature += DELTA_CURVATURE;
  }
  else{
    current_curvature -= DELTA_CURVATURE;
  }

  int val_l = map(int(255 * (-current_curvature)),-255,255,0,2*IDLE_SPEED);
  int val_r = map(int(255 * (current_curvature)),-255,255,0,2*IDLE_SPEED);

  run_motor(val_l,val_r);  
}

void peep(){
  digitalWrite(SOUND_PIN,HIGH);
  delay(200);
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

  Serial.print(" Left ");
  Serial.print(val_l);
  Serial.print(" Right ");
  Serial.println(val_r);

  digitalWrite(MOT_DIR_PIN_L,dir_l);
  digitalWrite(MOT_DIR_PIN_R,dir_r);

  analogWrite(MOT_SPEED_PIN_L, abs(val_l));
  analogWrite(MOT_SPEED_PIN_R, abs(val_r));
}

void loop() {
  if (digitalRead(BUT_PIN) == HIGH){
    is_ON = not is_ON;
    current_mode = 0;
    delay(1000);
  }
  
  

  if (is_ON){
    black_white();
  }
  else{
    digitalWrite(6,LOW);
    digitalWrite(5,LOW);
  }
}
