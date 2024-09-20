#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo sg90;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  sg90.attach(3);  //Servo Pin Number
  sg90.write(0);
  delay(5000);
  sg90.write(180);
  

  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
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
  if ((content.substring(1) == "41 CC 5F 20") || //change here the UID of the card/cards that you want to give access
  (content.substring(1) == "B9 84 A7 63"))
  {
    sg90.write(0);
    
    
    Serial.println("Authorized access");
    delay(5000);
    sg90.write(180);
    Serial.println();
    delay(3000);
  }
 
 else   {
    sg90.write(0);
    Serial.println(" Access denied");
    delay(3000);
  }
}
