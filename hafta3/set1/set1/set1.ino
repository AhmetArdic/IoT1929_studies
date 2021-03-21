
#include <SPI.h>
#include <MFRC522.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "LelloisPerfect"
#define WIFI_PASSWORD "deneme123456"
#define FIREBASE_HOST "rfid-8b5ed-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "J1HZMVI9m1VSAVON2XdvEludJhISW3fgrq1mdulm"

#define RST_PIN D1
#define SS_PIN D2
#define red D3
#define green D0

FirebaseData rfid_id;
FirebaseData rfid_name;
FirebaseData rfid_no;

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(green, OUTPUT); //green
  pinMode(red, OUTPUT); //red
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {

  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  String path = String("/") + String(uid2string()) + String("/");
  String name_path = path + String("isim");
  String no_path = path + String("daire");
  
  if(Firebase.get(rfid_id, path)) {
    //COOOOOOOL
    if(Firebase.getString(rfid_name, name_path)){
     //KART bulundu
     ledYak(green);
     
     Firebase.getInt(rfid_no, no_path);
     Serial.print(rfid_no. intData());
     Serial.print(". daireden ");
     Serial.print(rfid_name.stringData());
     Serial.println(", Hosgeldiniz.."); 
    }
    else {
      //KART veritabaninda yok
      ledYak(red);
      
      Serial.println("Yetkisiz Kart: Bu kart tanimli degildir..");
      ekranaYazdir();
      Serial.println("");
    }
  }
  else {
    //HATA
    Serial.println("Veritabani ile iletisim sorunlu.. ");
  }
 
  rfid.PICC_HaltA();
}

String uid2string() {
  String ID_string;
  for (byte i = 0; i < rfid.uid.size; i++) {
    ID_string += String(rfid.uid.uidByte[i], DEC);
  }
  return ID_string;
}

void ekranaYazdir() {
  Serial.print("ID Numarasi: ");
  for (int sayac = 0; sayac < 4 ; sayac++) {
    Serial.print(rfid.uid.uidByte[sayac]);
  }
  Serial.println("");
}

void ledYak(int pin) {
  //RGB led ortak anot oldugu icin GND olunca aktif oluyor
  if (pin == D0) {
    digitalWrite(green, LOW);
    delay(500);
    digitalWrite(green, HIGH);
    digitalWrite(red, HIGH);
  }
  else {
    digitalWrite(red, LOW);
    delay(500);
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
  }
}
