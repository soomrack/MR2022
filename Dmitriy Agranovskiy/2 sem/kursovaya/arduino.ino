#define SENSOR_LED_PIN A0 //датчик освещенности 
// 0 - светло
// 1 - темно
#define LED_PIN 6 //светодиодная лента
#define SENSOR_HUMIDITRY_PIN A1//датчик влажности почвы 
// 0 - влажно
// 1023 - сухо
#define WATER_PUMP_PIN 5 //водяная помпа
#define SENSOR_DHT_PIN 2 //датчик влажности и температуры воздуха
#define HEAT_PIN 4 //нагревательный элемент вентилятора
#define FAN_PIN 7 //вентилятор
#include <TroykaDHT.h>
DHT dht_sensor(SENSOR_DHT_PIN, DHT21);

int TYPE;//тип растения 1, 2 или 3;

unsigned long DELAY = 2000;// задержка
int MIN_LIGHT; // меньше данной освещенности включается светодиодная лента если бы был аналоговый....
float MIN_T;// меньше данной температуры включается вентилятор+нагреватель
float MAX_T;// выше данной температуры включается вентилятор
int MIN_HUMIDITRY;// меньше данной относительной влажности почвы включается помпа
const int DRY_SOIL_HUMIDITRY = 0; //значение влажной почвы
const int WET_SOIL_HUMIDITRY = 1023; //значение сухой почвы
// 0 - влажно
// 1023 - сухо
const unsigned long int WATERING_TIME = 10000; //время полива 
const unsigned long int DELAY_TIME = 80000; //ожидание распространения воды

void setup() {
  Serial.begin(9600);
  dht_sensor.begin();
  
  pinMode(SENSOR_LED_PIN, INPUT);
  pinMode(SENSOR_HUMIDITRY_PIN, INPUT);
  pinMode(SENSOR_DHT_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(HEAT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

  Serial.println("Введите тип растения из списка:");
  Serial.println("1 - клубника");
  Serial.println("2 - огурцы");
  Serial.println("3 - арбуз");
  Serial.write(TYPE);

  switch(TYPE){
    case 1 : Serial.println("Тип 1 - клубника"); 
    MIN_LIGHT = 400;
    MIN_T = 20.0;
    MAX_T = 30.0;
    MIN_HUMIDITRY = 50;
    break;

    case 2 : Serial.println("Тип 2 - огурцы"); 
    MIN_LIGHT = 600;
    MIN_T = 15.0;
    MAX_T = 40.0;
    MIN_HUMIDITRY = 60;
    break;

    case 3 : Serial.println("Тип 3 - арбуз"); 
    MIN_LIGHT = 800;
    MIN_T = 35;
    MAX_T = 50;
    MIN_HUMIDITRY = 70;
    break;

    default : Serial.println("вы выбрали неверный тип, введите число от 1 до 3");
    break; 
  }
}

void loop() {
  DHT_function(DELAY, MIN_T, MAX_T);
  LED_function(DELAY);
  HUM_function(DELAY, MIN_HUMIDITRY, DRY_SOIL_HUMIDITRY, WET_SOIL_HUMIDITRY, WATERING_TIME, DELAY_TIME);
}

void DHT_function(unsigned long delay, float min_temp, float max_temp){
  dht_sensor.read();
  float temperature;
  float humid_air;
  unsigned long int time_dht_read = 0;
  // проверяем состояние данных
  switch(dht_sensor.getState()) {
    // всё OK
    case DHT_OK:
      // выводим показания влажности и температуры
      temperature = dht_sensor.getTemperatureC();
      humid_air = dht_sensor.getHumidity();
      Serial.print("Temperature = ");
      Serial.print(temperature);
      Serial.println(" C \t");
      Serial.print("Temperature = ");
      Serial.print(dht_sensor.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperature = ");
      Serial.print(dht_sensor.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Humidity = ");
      Serial.print(humid_air);
      Serial.println(" %");
      digitalWrite(HEAT_PIN, LOW);
      digitalWrite(FAN_PIN, LOW); 
      if(temperature <= min_temp){
        Serial.println("Temperature is too low. Need to turn on fan and heater.\n");
        digitalWrite(FAN_PIN, HIGH);
        digitalWrite(HEAT_PIN, HIGH);        
      } else {
        if(temperature >= max_temp){
          Serial.println("Temperature is too high. Need to turn on fan.\n");
          digitalWrite(FAN_PIN, HIGH);
        } else {
          Serial.println("Temperature is normal.\n");
        }
      }
      if (millis() - time_dht_read > delay){
        time_dht_read = millis();
        Serial.println("Waiting");
      }
      break;
    // ошибка контрольной суммы
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    // данных нет, датчик не реагирует или отсутствует
    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;
  }
}

void LED_function(unsigned long delay){
  unsigned long int time_led_read = 0;
  bool led_lvl = 0;
  led_lvl = digitalRead(SENSOR_LED_PIN);

  if (led_lvl == 0) {
    Serial.println("It is bright\n");
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("It is dark. Need to turn on the light\n");
    digitalWrite(LED_PIN, HIGH);
  }
  if (millis() - time_led_read > delay){
        time_led_read = millis();
        Serial.println("Waiting");
      }
}

void HUM_function(unsigned long delay, int min_humiditry, int dry_soil_humidity, int wet_soil_humidity, unsigned long int watering_time,  unsigned long int delay_time){
  unsigned long int time_hum_read = millis();
  unsigned int hum_lvl = 0;
  hum_lvl = digitalRead(SENSOR_HUMIDITRY_PIN);
  unsigned int countled;
  countled = map(hum_lvl, wet_soil_humidity, dry_soil_humidity, 0, 100);
  // индикация уровня влажности
  if (hum_lvl <= MIN_HUMIDITRY){
    digitalWrite(WATER_PUMP_PIN, HIGH);
    if (millis() - time_hum_read > watering_time){
        time_hum_read = millis();
        Serial.println("Watering in progress");
     }
    digitalWrite(WATER_PUMP_PIN, LOW);
    time_hum_read = millis();
    if (millis() - time_hum_read > delay_time){
        time_hum_read = millis();
        Serial.println("Waiting for the water to spread");
     }
  }

}

