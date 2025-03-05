
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 char auth[] = "IJJwfmjZTEoDaMcG89iPpTiSBJ5uh6OY";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Thu Thao";
char pass[] = "12052002";
#include <EEPROM.h>
#define rx 12
#define tx 2
void EEPROM_put(char add, String data);
String EEPROM_get(char add);
int doi =0,dangnhap=0;
String matkhau,mk;
WidgetTerminal terminal(V3);
BLYNK_WRITE(V0) {
  matkhau = param.asStr(); 
  terminal.println(F("HAY NHAN DANG NHAP"));
  terminal.flush();
 // Serial.println(matkhau);
}
BLYNK_WRITE(V1) {
  doi = param.asInt();
  if(doi == 1){
    mk = matkhau;
    Serial.println("DOI MAT KHAU");
   EEPROM_put(0,mk);
  Serial.println(mk);
  delay(100);
  Serial.println(EEPROM_get(0));
  terminal.println(F("DOI MAT KHAU THANH CONG"));
  terminal.flush();
  }
}
BLYNK_WRITE(V2) {
  dangnhap = param.asInt();
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
EEPROM.begin(512);
pinMode(rx, INPUT);
pinMode(tx, OUTPUT);
delay(1000);
mk = EEPROM_get(0);
Blynk.begin(auth, ssid, pass,"blynk-server.com",8080);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
if(dangnhap == 1 ){
 // Serial.println(mk);
    if(matkhau == mk){
      digitalWrite(tx, HIGH);
      terminal.println(F("DANG NHAP THANH CONG"));
      Serial.println("DANG NHAP THANH CONG");
       terminal.flush();
    }
    else {digitalWrite(tx, LOW);
    terminal.println(F("SAI MAT KHAU DANG NHAP"));
    Serial.println("DANG NHAP KHONG THANH CONG");
  terminal.flush();
  }
}
else digitalWrite(tx, LOW);
}


void EEPROM_put(char add, String data)
{
  int _size = data.length();
  int i;
  for (i = 0; i < _size; i++)
  {
    EEPROM.write(add + i, data[i]);
  }
  EEPROM.write(add + _size, '\0'); //Add termination null character for String Data
  EEPROM.commit();
}
String EEPROM_get(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len = 0;
  unsigned char k;
  k = EEPROM.read(add);
  while (k != '\0' && len < 500) //Read until null character
  {
    k = EEPROM.read(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}
