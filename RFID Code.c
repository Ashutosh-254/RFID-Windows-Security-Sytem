//RFID Based Windows PC Unlocking System

//Include Libraries 
#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

//Set pen connections as needed
#define RST_PIN 9          
#define SS_PIN 10          
MFRC522 mfrc522(SS_PIN, RST_PIN);   

//Add the card and include the UID
String read_rfid;                  
String ok_rfid = "e5e1a420";      
int lock = 2;                       

int a = 0;
int b = 0;
int c = 0;
int d = 0;

//Set reuired baud rate
void setup() {
  Serial.begin(9600);         
  SPI.begin();               
  mfrc522.PCD_Init();        

  //Choose which lock below:
  pinMode(lock, OUTPUT);
    digitalWrite(lock, HIGH);
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  read_rfid = "";
  for (byte i = 0; i < bufferSize; i++) {
    read_rfid = read_rfid + String(buffer[i], HEX);
  }
}

void loop() {

  // Look for new cards and select the one
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(read_rfid);

  if ((read_rfid == ok_rfid) && (a == 0)) 
  {  
    digitalWrite(lock, LOW);
    Serial.println("open relay");
    a++;
    Serial.println(a);
    delay(1000);
    read_rfid = "";
  }

  //Enter the password to your computer
  if ((read_rfid == ok_rfid) && (a == 1)) 
  {
    Serial.println("cc");
     Keyboard.write('2');
     delay (20);
     Keyboard.write('0');
     delay (20);
     Keyboard.write('2');
     delay (20);
     Keyboard.write('2');
     delay (20);
    Serial.println("close relay");
    a = 0;
    Serial.println(a);
    delay(1000);
  }

  read_rfid = "";
}
