#define HUMIDITY_SENSOR_PIN A1
#define LDR_PIN A0
#define DHT_SENSOR_PIN 2
#define DHT_SENSOR_VCC_PIN 8

#define HEATER_PIN 4
#define WATER_PUMP_PIN 5
#define LED_STRIP_PIN 6
#define FAN_PIN 7

/* DHT21 (датчик влажности и температуры) общается через
 * цифровой порт 2 по специальному протоколу, который
 * можно реализовать с помощью сторонней библиотеки */

/* LDR выдает на цифроом пине A0 0 (светло) или 1 (темно)
 * LDR должен выдавать аналоговый сигнал от 0 (светло) до 1023 (темно) */

/* Датчик влажности дает на аналоговом пине A1 значение влажности,
 * где 1023 - сухо (нет контакта между проводниками),
 * 0 - влажно (проводники замкнуты) */

/* Пин D4 отвечает за нагревательный элемент
 * !!! (включение только одновременно с вентилятором) !!!
 * Пин D5 отвечает за водяную помпу полива
 * Пин D6 отвечает за светодиодную ленту
 * Пин D7 отвечает за вентилятор */

// Задание параметров для запуска программы конкретного вида растений
// Задержка между выводом (для аналоговых) и считываниями (для цифрового) сигналов с датчиков
const int DELAY = 2000;

// Граничное значение освещенности, выше которого включается фитолента
const int NORMAL_LIGHT_LVL = 500;

/* Граничные значения для температуры воздуха, ниже и выше которых должен быть
 * включен нагревательный элемент и/или вентилятор соответственно */
const float MIN_TEMP = 25.0;
const float MAX_TEMP = 40.0;

/* Граничное значения для относительной влажности почвы
 * в процентах, ниже которого должна быть включена помпа */
const int MIN_HUMIDITY = 70;
// Значения сухой и влажной почвы определяются экспериментально для расчета относительной влажности
const int DRY_SOIL_HUMID = 1023;
const int WET_SOIL_HUMID = 0;
// Время на полив и на ожидание распространения воды до датчика в миллисекундах
const unsigned long int WATERING_PERIOD = (unsigned long int)1 * 10 * 1000;
const unsigned long int WAITING_PERIOD = (unsigned long int)1 * 60 * 1000;

bool is_watering_need = false;
bool is_watering_ended = false;

#include <TroykaDHT.h>
// Подключение библиотеки для считывания данных с датчиков серии DHT
/* Создание объекта класса DHT с указанием номера цифрового
 * порта, куда подключен датчик и конкретной модели серии */
DHT dht_sensor(DHT_SENSOR_PIN, DHT21);

void setup() {
  Serial.begin(9600);
  dht_sensor.begin();
  pinMode(HUMIDITY_SENSOR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  for (int num = HEATER_PIN; num <= DHT_SENSOR_VCC_PIN; num++) {
    pinMode(num, OUTPUT);
  }
}

void loop() {
  if ((DELAY <= 0) || (MIN_HUMIDITY <= 0) || (NORMAL_LIGHT_LVL <= 0) || (MAX_TEMP <= MIN_TEMP)) {
    static unsigned long int last_error_print = 0;
    if ((millis() - last_error_print) > DELAY) {
      Serial.println("Given parameter have an unacceptable value!\n");
      last_error_print = millis();
    }
  } else {
    static unsigned long int last_report_print = 0;
    control_illumination(DELAY) /*, NORMAL_LIGHT_LVL)*/;

    control_humidity(DELAY, MIN_HUMIDITY, WATERING_PERIOD, WAITING_PERIOD);

    if (is_watering_need && !is_watering_ended) {
      digitalWrite(FAN_PIN, LOW);
      digitalWrite(HEATER_PIN, LOW);
      if ((millis() - last_report_print) > DELAY) {
        Serial.println("Soil is watering, temperature control is off.\n");
        last_report_print = millis();
      }
    } else {
      control_temperature(DELAY, MIN_TEMP, MAX_TEMP);
    }
  }
}

void control_temperature(const int read_delay, const int min_temp, const int max_temp) {
  static unsigned long int last_dht_read = 0;
  static float temperature = 0;
  static float air_humid = 0;
  if ((millis() - last_dht_read) > read_delay) {
    if (read_delay < 2000) {
      Serial.println("Delay between measurings of temperature is too short!\n");
    } else {
      dht_sensor.read();
      switch (dht_sensor.getState()) {
        case DHT_OK:
          temperature = dht_sensor.getTemperatureC();
          air_humid = dht_sensor.getHumidity();
          Serial.print("Temperature = ");
          Serial.print(temperature);
          Serial.println(" C \t");
          Serial.print("Air humidity = ");
          Serial.print(air_humid);
          Serial.println("% \t");
          break;
        case DHT_ERROR_CHECKSUM:
          Serial.println("Checksum error.\n");
          break;
        case DHT_ERROR_TIMEOUT:
          Serial.println("Time out error.\n");
          break;
        case DHT_ERROR_NO_REPLY:
          Serial.println("Sensor not connected.\n");
          break;
      }
      if (dht_sensor.getState() == DHT_OK) {
        if ((temperature <= min_temp) || (temperature >= max_temp)) {
          if (temperature <= min_temp) {
            Serial.println("Temperature is too low. Need to turn on fan and heater.\n");
          } else {
            Serial.println("Temperature is too high. Need to turn on fan.\n");
          }
        } else {
          Serial.println("Temperature is normal.\n");
        }
        if ((temperature <= min_temp) || (temperature >= max_temp)) {
          digitalWrite(FAN_PIN, HIGH);
          if (temperature <= min_temp) {
            digitalWrite(HEATER_PIN, HIGH);
          } else {
            digitalWrite(HEATER_PIN, LOW);
          }
        } else {
          digitalWrite(FAN_PIN, LOW);
          digitalWrite(HEATER_PIN, LOW);
        }
      } else {
        digitalWrite(FAN_PIN, LOW);
        digitalWrite(HEATER_PIN, LOW);
      }
    }
    last_dht_read = millis();
  }
}

void control_illumination(const int print_delay) { /*,const unsigned int normal_light_lvl) */
  static unsigned long int last_light_print = 0;   /*здесь и далее - при подключении датчика к аналоговому пину */
  bool light_lvl = 0;
  //  unsigned int light_lvl = 0;
  light_lvl = digitalRead(LDR_PIN);
  if ((millis() - last_light_print) > print_delay) {
    if (light_lvl) {
      Serial.println("It is dark. Need to turn on the light!\n");
    } else {
      Serial.println("It is bright. No need to turn on the light.\n");
    }
    //    if (light_lvl <= normal_light_lvl) {
    //      Serial.println("It is dark. Need to turn on the light!\n");
    //    } else {
    //      Serial.println("It is bright. No need to turn on the light.\n");
    //    }
    last_light_print = millis();
  }
  digitalWrite(LED_STRIP_PIN, light_lvl);
  //  if (light_lvl <= normal_light_lvl) {
  //    digitalWrite(LED_STRIP_PIN, HIGH);
  //  } else {
  //    digitalWrite(LED_STRIP_PIN, LOW);
  //  }
}

void control_humidity(const int print_delay, const unsigned int min_humidity, const unsigned long int watering_period, const unsigned long int waiting_period) {
  static unsigned long int last_humid_print = 0;
  static unsigned long int last_watering = 0;
  static unsigned long int last_waiting = 0;
  unsigned int humid_lvl = 0;
  unsigned int relative_humid_lvl = 0;
  humid_lvl = analogRead(HUMIDITY_SENSOR_PIN);
  relative_humid_lvl = map(humid_lvl, WET_SOIL_HUMID, DRY_SOIL_HUMID, 100, 0);
  if ((!is_watering_ended) && (!is_watering_need)) {
    if ((millis() - last_humid_print) > print_delay) {
      Serial.println("Soil humidity is normal and equal " + String(relative_humid_lvl) + "%\n");
      last_humid_print = millis();
    }
  }
  if ((!is_watering_need) && (relative_humid_lvl <= min_humidity)) {
    last_humid_print = 0;
    is_watering_need = true;
    last_watering = millis();
    if ((millis() - last_humid_print) > print_delay) {
      Serial.println("Soil humidity is equal " + String(relative_humid_lvl) + "%");
      Serial.println("Soil is dry. Need to turn on the water pump!\n");
      last_humid_print = millis();
    }
  }
  if (is_watering_need) {
    if ((millis() - last_watering) < watering_period) {
      digitalWrite(WATER_PUMP_PIN, HIGH);
      if ((millis() - last_humid_print) > print_delay) {
        Serial.println("Soil is watering... " + String(round(watering_period - (millis() - last_watering)) / 1000) + " seconds left before watering ends.\n");
        last_humid_print = millis();
      }
    } else {
      if (!is_watering_ended) {
        last_waiting = millis();
      }
      is_watering_ended = true;
      digitalWrite(WATER_PUMP_PIN, LOW);
      if (dht_sensor.getState() != DHT_OK) {
        Serial.println("Humidity sensor is reconnected.\n");
        digitalWrite(DHT_SENSOR_VCC_PIN, HIGH);
        delay(print_delay);
        digitalWrite(DHT_SENSOR_VCC_PIN, LOW);
        delay(print_delay);
      }
      if ((millis() - last_humid_print) > print_delay) {
        Serial.println("Soil humidity is equal " + String(relative_humid_lvl) + "%");
        Serial.println("Watering ended, waiting for spreading water.\n");
        last_humid_print = millis();
      }
    }
  }
  if ((is_watering_ended) && ((millis() - last_waiting) > waiting_period)) {
    last_humid_print = 0;
    if (relative_humid_lvl > min_humidity) {
      is_watering_need = false;
      is_watering_ended = false;
      if ((millis() - last_humid_print) > print_delay) {
        Serial.println("Soil humidity is equal " + String(relative_humid_lvl) + "%");
        Serial.println("Watering ended, water spread successfully.\n");
        last_humid_print = millis();
      }
    } else {
      is_watering_need = true;
      is_watering_ended = false;
      last_watering = millis();
      if ((millis() - last_humid_print) > print_delay) {
        Serial.println("Soil humidity is equal " + String(relative_humid_lvl) + "%");
        Serial.println("Watering didn't end, water spread unsuccessfully.\n");
        last_humid_print = millis();
      }
    }
  }
}
