#include <ESP32_PWM.h>
#include <AnalogSensor.h>
#include <Equations.h>
#include <Filter.h>

const uint8_t SENSOR_PIN = 25,SENSOR_PIN2 = 27,PWM_PIN = 32,PWM_PIN2 = 15,dt_ms=10;
float coefficients[]={0.0f,0.000806f};
float b1[3]={0.0201,0.0402,0.0201};
float a1[3]={1.0,-1.561,0.6414};
float b2[2]={1,-1};
float a2[2]={1,-0.93};
float b3[4]={0.25,0.25,0.25,0.25};
float a3[1]={1};
volatile float X,DAC,F1,F2,F3;
AnalogSensor sensor1,sensor2;
PWM generadorSignal,generadorAnalog;
ulong current_time,prev_time;
Filter filter1(b1,a1,3,3), filter2(b2,a2,2,2), filter3(b3,a3,4,1);

void setup() {
  Serial.begin(115200);
  sensor1.setup(SENSOR_PIN,polynomial,coefficients,2);
  sensor2.setup(SENSOR_PIN2,polynomial,coefficients,2);
  generadorSignal.setup(PWM_PIN,1,2);
  generadorSignal.setDuty(50);
  generadorAnalog.setup(PWM_PIN2,6,40000);
  prev_time = millis();
}

void loop() {
  current_time = millis();
  if(current_time - prev_time > dt_ms)
  {
      prev_time = current_time;
      sensor1.read();
      X=sensor1.getMeasurement(SENSOR_MEASUREMENT);
      F1 = filter1.Filt(X);
      F2 = filter2.Filt(X);
      F3 = filter3.Filt(X);
      generadorAnalog.setDAC(F1);
      sensor2.read();
      DAC=sensor2.getMeasurement(SENSOR_MEASUREMENT);
      Serial.printf("%.3f, %.3f, %.3f, %.3f, %.3f\n",X,F1,F2,F3,DAC);
  }
}