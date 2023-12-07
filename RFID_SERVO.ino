#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>   

#define RST_PIN   9
#define SS_PIN    10

Servo SG90;
MFRC522 rc522(SS_PIN, RST_PIN);

int sg90 = 6;
int i=0;

void setup(){
  Serial.begin(9600);
  SPI.begin();
  rc522.PCD_Init();
  
  SG90.attach(sg90);          
}

void loop(){

  if ( !rc522.PICC_IsNewCardPresent() || !rc522.PICC_ReadCardSerial() ) { 
    delay(500);
    return;
  }
  
  Serial.print("Card UID:");
  
  for (byte i = 0; i < 4; i++) {
    Serial.print(rc522.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  if(rc522.uid.uidByte[0]==0x73 && rc522.uid.uidByte[1]==0xA9 && rc522.uid.uidByte[2]==0xC1 
    && rc522.uid.uidByte[3]==0x0F) {
    
    Serial.println("<< OK !!! >>  Registered card...");
    
    for(i=0; i<=180; i++){        
      SG90.write(i);
      delay(10);
    }
    for(i=180; i>0; i--){         
      SG90.write(i);
    delay(10);
    }
    delay(500);
  }
  else{
    Serial.println("<< WARNING !!! >>  This card is not registered");
    delay(500);
  }

  delay(100);
}
