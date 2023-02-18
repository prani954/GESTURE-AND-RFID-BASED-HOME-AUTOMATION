#include <SPI.h>
#include <MFRC522.h>
#define SS_1_PIN 10
#define SS_2_PIN 2
#define RST_PIN 9
int relay1=6; 
int relay2=5; 
int buzzer = 7;
MFRC522 mfrc522(SS_1_PIN, RST_PIN); // Instance of the class
MFRC522 mfrc522a(SS_2_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
// Init array that will store new NUID 
byte nuidPICC[3];
void setup() { 
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init(); 
  mfrc522a.PCD_Init();  // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
void loop() {
RFID();
RFID1(); 
}
void RFID()
{
  //Serial.println("pirmais");
    if ( ! mfrc522.PICC_IsNewCardPresent())  { return;}
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {return; }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "11 23 CE 26") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();  
    digitalWrite(relay1, HIGH);
   digitalWrite(buzzer, LOW);
    delay(3000);
    digitalWrite(relay1, LOW); 
  } 
 else   {
    Serial.println(" Access denied");
    digitalWrite(relay1, LOW); 
    digitalWrite(buzzer, HIGH);
    delay(3000); 
    digitalWrite(buzzer, LOW);     
  }
}
void RFID1()
{
  if ( ! mfrc522a.PICC_IsNewCardPresent()) {return; }
  // Select one of the cards
  if ( ! mfrc522a.PICC_ReadCardSerial()) {return; }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522a.uid.size; i++) 
  {
     Serial.print(mfrc522a.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522a.uid.uidByte[i], HEX);
     content.concat(String(mfrc522a.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522a.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "01 48 3F 26") //Change the UID of the card/cards that you want accessto
  { Serial.println("Authorized access");
    Serial.println();   
    digitalWrite(relay2, HIGH);
    digitalWrite(buzzer, LOW);
    delay(3000);
    digitalWrite(relay2, LOW);  } 
 else   {
    Serial.println(" Access denied"); 
    digitalWrite(relay2, LOW); 
    digitalWrite(buzzer, HIGH);
    delay(3000); 
    digitalWrite(buzzer, LOW);    
  }
}
