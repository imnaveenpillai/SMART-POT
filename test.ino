#define BLYNK_TEMPLATE_ID "TMPL3xfXa8-oa"
#define BLYNK_TEMPLATE_NAME "mini n"
#define BLYNK_AUTH_TOKEN "Hcv_sBn8twZ8tfzCrsK2Ro_CV1f7uBSs"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

// A0 is moisture sensor
// D5 is pump
// D6 is fan
// D7 is Ldr sensor
// D8 is LED

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Naveen";  
char pass[] = "ItypeMyPasswordHere";  

BlynkTimer timer;




void sendSensor()
{
  /*int soilmoisturevalue = analogRead(A0);
   soilmoisturevalue = map(soilmoisturevalue, 0, 1023, 0, 100);*/
   int value_moisture = analogRead(A0);
   int pump;
   int led;
  value_moisture = map(value_moisture,400,1023,100,0);

  if (value_moisture < 30){
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
    pump = 1;
  }
  else{
    digitalWrite(14, HIGH);
    digitalWrite(12, HIGH);
    pump = 0;
    
  }
  
  int value_ldr = digitalRead(13);
  // Serial.print("Ld value: ");
  //Serial.println(value_ldr);

if (value_ldr == 0){
  digitalWrite(15, LOW);
  led = 0;
}
else {
  digitalWrite(15, HIGH);
  led = 1;
}

    Blynk.virtualWrite(V0, value_moisture);
    Blynk.virtualWrite(V1, pump);
    Blynk.virtualWrite(V2, pump);
    Blynk.virtualWrite(V3, led);
    disease();
    
    

    //Serial.print("Soil Moisture : ");
    //Serial.println(value_moisture);
}
void setup()
{   
  
  Serial.begin(115200);
  
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(13, INPUT);
  pinMode(15, OUTPUT);


  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }

void disease(){
  int intval;
  if (Serial.available() > 0){
    //String data = Serial.readStringUntil('\n');
    intval = Serial.parseInt();
  }
  Serial.print("Disease: ");
  Serial.println(intval);
  Blynk.virtualWrite(V4, intval);
 } 