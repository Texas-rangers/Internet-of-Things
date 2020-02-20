#define Peizo D8
//pass #define SoundSensor
#define LED 13
#define Button 8
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "7EmtwU9JoL84T-HHzFArr6Wh553rVUia";
char ssid[] = "Heartk";
char pass[] = "2345679pp";

unsigned long long FDetect=0,LDetect;
int btn;
BlynkTimer timer;

void play(){
  tone(Peizo,1000,500);
}
BLYNK_WRITE(V1){
  btn = param.asInt();
}
void Main(){
  //pass volume = digitalRead(SoundSensor);
  if(/*volume > 100*/btn == HIGH){
      digitalWrite(LED,HIGH);
      LDetect = millis();
      if(FDetect == 0){
        FDetect = millis();
      }
      if(LDetect - FDetect > 3000){
        play();
      }
  }else{
      if(millis() - LDetect < 1500){
          digitalWrite(LED,LOW);
          FDetect = 0;
      } 
  }
}

void setup(){
  Serial.begin(9600);
  //pass pinMode(SoundSensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT);
  Blynk.begin(auth, ssid ,pass);
  timer.setInterval(500L, Main);
}

void loop(){
  Blynk.run();
  timer.run();
}
