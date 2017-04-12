#include <Wire.h>
#include <ArduinoJson.h>
#define Relay_pin_a_1  7
#define Relay_pin_a_2  8
#define Relay_pin_a_3  9
#define Relay_pin_b_1  10
#define Relay_pin_b_2  11
#define Relay_pin_b_3  12
void outv(uint32_t V);
void outvG(uint32_t V);
float smooth(float alfa, float new_data, float old_data);
void myPID();
float limit(float input, int32_t min_limit, int32_t max_limit);
byte c[17];
////////////////////////////////////////////
int32_t O_rawv = 0, O_rawa = 0, O_raw0a = 0, O_raw00a = 0;
int32_t O_rawv_b = 0, O_rawa_b = 0, O_raw0a_b = 0, O_raw00a_b = 0;
/////////////////////
byte type;
int32_t start_new ;
int32_t stop_new ;
int32_t incvement;
int16_t a_max;
int32_t ib_vg1;
int32_t ib_vg2;
int32_t ib_vg3;
int32_t ib_vg4;
int32_t ib_vg5;
int32_t ib_vg6;
int32_t ib_vg7;
int32_t ib_vg8;
int32_t ib_vg9;
int32_t ib_vg10;
////////////////////
int32_t rawv = 0;
float rawv_b = 0;
int32_t rawa = 0;
float rawa_b = 0;
int32_t raw0a = 0;
float raw0a_b = 0;
int32_t raw00a = 0;
float raw00a_b = 0;
//////////////////////
int32_t rawv_B = 0;
float rawv_b_B = 0;
int32_t rawa_B = 0;
float rawa_b_B = 0;
int32_t raw0a_B = 0;
float raw0a_b_B = 0;
int32_t raw00a_B = 0;
float raw00a_b_B = 0;
/////////////////////
float v_se = 0;
float a3_se = 0;
float a03_se = 0;
float a003_se = 0;
////////////////////
float v_se_B = 0;
float a3_se_B = 0;
float a03_se_B = 0;
float a003_se_B = 0;
///////////////////
float kpt = 1.5f, kit = 1.0f, kdt = 0.0;
float Input, Output, Input_b;
float errSum, dErr, error, lastErr;
float ref_t = 0.0f;
uint32_t vol = 0;

#include "ReadV_A.h"

void setup() {
  delay(100);
   pinMode(13, OUTPUT);
  pinMode(Relay_pin_a_1, OUTPUT);
  pinMode(Relay_pin_a_2, OUTPUT);
  pinMode(Relay_pin_a_3, OUTPUT);
  digitalWrite(Relay_pin_a_1, LOW);  //สลับขั้ว 0=ขั้วบวก  1 = ขั้วลบ
  digitalWrite(Relay_pin_a_2, LOW);  //  L  H  = เล้ง 1   H  L  = เล้ง 2  H  H  = เล้ง 3
  digitalWrite(Relay_pin_a_3, LOW);  //
  pinMode(Relay_pin_b_1, OUTPUT);
  pinMode(Relay_pin_b_2, OUTPUT);
  pinMode(Relay_pin_b_3, OUTPUT);
  digitalWrite(Relay_pin_b_1, LOW);  //สลับขั้ว 0=ขั้วบวก  1 = ขั้วลบ
  digitalWrite(Relay_pin_b_2, LOW);  //  L  H  = เล้ง 1   H  L  = เล้ง 2  H  H  = เล้ง 3
  digitalWrite(Relay_pin_b_3, LOW);  //
  Serial.begin(115200);
  Serial.setTimeout(100);
  Wire.begin();
  outv((uint32_t)9640 + 65 + (uint32_t)000);
  outvG((uint32_t)9554 + (uint32_t)29 + (uint32_t)0);
  delay(5000);
  //  outv(9640 + 0);
  //  delay(1000);
  //  outv(9640 + 1000);
  //  delay(1000);

  for (int i = 0; i < 1000; i++) {
    readV_A_O();
    readV_A_O_B();
    O_rawv += rawv;
    O_rawa += rawa;
    O_raw0a += raw0a;
    O_raw00a += raw00a;
    O_rawv_b += rawv_b_B;
    O_rawa_b += rawa_b_B;
    O_raw0a_b += raw0a_b_B;
    O_raw00a_b += raw00a_b_B;
    delay(1);
  }

  O_rawv = O_rawv / 1000.00f;
  O_rawa = O_rawa / 1000.00f;
  O_raw0a = O_raw0a / 1000.00f;
  O_raw00a = O_raw00a / 1000.00f;
  O_rawv_b = O_rawv_b / 1000.00f;
  O_rawa_b = O_rawa_b / 1000.00f;
  O_raw0a_b = O_raw0a_b / 1000.00f;
  O_raw00a_b = O_raw00a_b / 1000.00f;
  //        while(1){
  //         readV_A_O();
  //  Serial.print(O_rawv_b);
  //  Serial.print(" ");
  //  Serial.print(O_rawa_b);
  //  Serial.print(" ");
  //  Serial.print(O_raw0a_b);
  //  Serial.print(" ");
  //  Serial.print(O_raw00a_b);
  //  Serial.println(" ");
  //        }
  Serial.println("start");
  uint32_t q = ((uint32_t)9554 + (uint32_t)29 + (uint32_t)35000);
  delay(1);
  outvG(q);
  delay(1000);
  outv((uint32_t)9640 + 65 + (uint32_t)(24));
}
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
char buffer[18];
uint32_t  tong;


byte MODE = 0;
uint16_t zxcv1 = 100000;
StaticJsonBuffer<200> jsonBuffer;
void loop() {
  uint16_t zxcv[zxcv1];
  while (MODE == 0) {
    zxcv1 = 50000;
    if (Serial.available() > 0) {
      String DATA_FROM = Serial.readString();
      char json[] = "{\"data\":[1,0,50000,1000,1000,10000,2,3,4,5,6,7,8,9,10]}";
      //char json[] = "{"data":[1,0,50000,1000,1000,10000,2,3,4,5,6,7,8,9,10]}";
      JsonObject& root = jsonBuffer.parseObject(DATA_FROM);
      if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
      }
      type = root["data"][0];
      start_new = root["data"][1];
      stop_new = root["data"][2];
      incvement = root["data"][3];
      a_max = root["data"][4];
      ib_vg1 = root["data"][5];
      ib_vg2 = root["data"][6];
      ib_vg3 = root["data"][7];
      ib_vg4 = root["data"][8];
      ib_vg5 = root["data"][9];
      ib_vg6 = root["data"][10];
      ib_vg7 = root["data"][11];
      ib_vg8 = root["data"][12];
      ib_vg9 = root["data"][13];
      ib_vg10 = root["data"][14];
      jsonBuffer = StaticJsonBuffer<200>();
      Serial.println(type);
    }
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis3 >= 500) {
      previousMillis3 = currentMillis;
      digitalWrite(13, !digitalRead(13));
    }
    if (currentMillis - previousMillis2 >= 1000) {
      previousMillis2 = currentMillis;

      //        Serial.print(rawv_b_B);
      //        Serial.print("B ");
      //        Serial.print(rawa_b_B);
      //        Serial.print("B ");
      //        Serial.print(raw0a_b_B);
      //        Serial.print(" ");
      //        Serial.print(raw00a_b_B);
      //        Serial.print(" ");
      //        Serial.print(raw00a_b_B - O_raw00a_b);
      //        Serial.println(" ");

      //    แสดงผล  30v
      //        Serial.print(v_se_B);
      //        Serial.print(" ");
      //        Serial.print(a3_se_B,4);
      //        Serial.print(" ");
      //        Serial.print(a03_se_B);
      //        Serial.print(" ");
      //        Serial.print(a003_se_B);
      //        Serial.println(" ");
      //
      //    แสดงผล  50v
      //    Serial.print(v_se);
      //    Serial.print(" ");
      //    Serial.print(a3_se, 3);
      //    Serial.print(" ");
      //    Serial.print(a03_se, 3);
      //    Serial.print(" ");
      //    Serial.print(a003_se);
      //    Serial.print(" ");
      //    Serial.print(raw00a);
      //    Serial.print(" ");
      //    Serial.println(" ");
    }
  }
  while (MODE == 1) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 30) {
      previousMillis = currentMillis;
      ref_t = abs(start_new);
      if (start_new < 0) {
        digitalWrite(Relay_pin_a_1, HIGH);
      }
      else {
        digitalWrite(Relay_pin_a_1, LOW);
      }
      readV_A();
      myPID();
      if (a3_se>1.00) {
        MODE = 0;
        outv((uint32_t)9640 + 65 + (uint32_t)(0));
      }
      if ((int32_t)v_se == (int32_t)ref_t) {
        if (start_new < stop_new) {
          JsonObject& root = jsonBuffer.createObject();
          JsonArray& data = root.createNestedArray("data");
          data.add(start_new);
          if (digitalRead(Relay_pin_a_2) == 0 && digitalRead(Relay_pin_a_3) == 0) {
            data.add(a3_se * 1000);
          } else if (digitalRead(Relay_pin_a_2) == 1 && digitalRead(Relay_pin_a_3) == 0) {
            data.add(a03_se);
          } else if (digitalRead(Relay_pin_a_2) == 1 && digitalRead(Relay_pin_a_3) == 1) {
            data.add(a003_se / 1000, 3);
          }
          root.printTo(Serial);
          jsonBuffer = StaticJsonBuffer<200>();
          start_new = start_new + incvement;
        } else {
          JsonObject& root = jsonBuffer.createObject();
          JsonArray& data = root.createNestedArray("dataend");
          data.add(start_new);
          if (digitalRead(Relay_pin_a_2) == 0 && digitalRead(Relay_pin_a_3) == 0) {
            data.add(a3_se * 1000);
          } else if (digitalRead(Relay_pin_a_2) == 1 && digitalRead(Relay_pin_a_3) == 0) {
            data.add(a03_se);
          } else if (digitalRead(Relay_pin_a_2) == 1 && digitalRead(Relay_pin_a_3) == 1) {
            data.add(a003_se / 1000, 3);
          }
          root.printTo(Serial);
          jsonBuffer = StaticJsonBuffer<200>();
          MODE = 0;
          ref_t = 0;
          outv((uint32_t)9640 + 65 + (uint32_t)(0));
        }

      }

      //    outv(Output);

    }
    if (currentMillis - previousMillis3 >= 1000) {
      previousMillis3 = currentMillis;
      digitalWrite(13, !digitalRead(13));
    }
  }
  while (MODE == 2) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 30) {
      previousMillis = currentMillis;

      readV_A();
      readV_B();

      myPID();
      if (v_se == 1) {

      }
      //    outv(Output);

    }
  }
  while (MODE == 3) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 30) {
      previousMillis = currentMillis;

      readV_A();
      readV_B();

      myPID();
      if (v_se == 1) {

      }
      //    outv(Output);

    }
  }

}
void outv(uint32_t V) {
  uint32_t V1 = V;
  byte v[6] = {};
  v[0] = V1 >> 16;
  v[1] = V1 >> 8;
  v[2] = V1;
  v[3] = 0;
  v[4] = 0;
  v[5] = 0;
  Wire.beginTransmission(1); // transmit to device #8
  Wire.write(v, 6);             // sends one byte
  Wire.endTransmission();    // stop transmitting
}
void outvG(uint32_t V) {
  uint32_t V1 = V;
  byte v56[6] = {};
  v56[0] = V >> 16;
  v56[1] = V >> 8;
  v56[2] = V;
  v56[3] = 0;
  v56[4] = 0;
  v56[5] = 0;
  Wire.beginTransmission(11); // transmit to device #8
  Wire.write(v56, 6);             // sends one byte
  Wire.endTransmission();    // stop transmitting
}

float smooth(float alfa, float new_data, float old_data)
{
  return (old_data + alfa * (new_data - old_data));
}

void myPID()
{
  lastErr = error;
  error = ref_t - v_se;
  dErr = (error - lastErr) * 2.0f;
  errSum = limit(errSum + (error * 1.0f), 0, 262143 - (9640 + 60));

  Input = limit((kpt * error) + (kit * errSum) + (kdt * dErr), 0, 262143 - 9640);
  Output = limit(Input + Input_b, 0, 262143 - 9640);
}
float limit(float input, int32_t min_limit, int32_t max_limit)
{
  if (input > max_limit)input = max_limit;
  if (input < min_limit)input = min_limit;
  return input;
}
