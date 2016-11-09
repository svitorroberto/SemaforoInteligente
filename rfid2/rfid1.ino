#include <ConnectionConfig.h>
#include <KPMqtt.h>
#include <Listener4SIBCommandMessageNotifications.h>
#include <Listener4SIBIndicationNotifications.h>
#include <SSAPBodyJoinUserAndPasswordMessage.h>
#include <SSAPBodyOperationMessage.h>
#include <SSAPBodyQueryMessage.h>
#include <SSAPBodyReturnMessage.h>
#include <SSAPBodySubscribeMessage.h>
#include <SSAPBodyUnsubscribeMessage.h>
#include <SSAPMessage.h>
#include <SSAPMessageGenerator.h>
#include <Ethernet.h>
#include <MFRC522.h>
#include <SPI.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};//Arduino MAC
IPAddress ip(10,62,2,3);// Arduino IP
// ThingSpeak Settings
IPAddress server(10,62,2,2);
//char thingSpeakAddress[] = "10.62.2.3";
boolean joined = false;
unsigned long uid = 1LL;


#define RST_PIN         8           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;

void setup() {
  Serial.begin( 9600 );
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  Ethernet.begin(mac, ip);

}

// Initialize Arduino Ethernet Client
EthernetClient client;


void loop() { 
  // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

  String id_antena = "1";
  String id_veiculo;
  String id_cruzamento = "1";
  
  //Pegando ID do cartão em HEX
  for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
      }

  Serial.println("-new Loop-");

  //Pegando ID do cartão em DECIMAL
  //uid = getID();
  id_veiculo = getID();
  Serial.print("Cadastrando o ID:");
  Serial.println(uid);
  
  //Establishing a connection
  if (client.available())
{
    Serial.println("-Conectado-");
    char c = client.read();
    Serial.print(c);
  }

  if (!joined) {
    Serial.println();

      updateThingSpeak("idantena="+id_antena+"&idveiculo="+id_veiculo);
    
    }
  

    
    Serial.println("-End of Loop-");
    delay(2000);

}



/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
unsigned long getID(){
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}

void updateThingSpeak(String tsData)
{
  if (client.connect(server, 9000))
  {
  client.print("GET /?"+tsData+" HTTP/1.1\n");
  client.print("Host: localhost\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(tsData.length());
  client.print("\n\n");
  
  client.print(tsData);
  
  lastConnectionTime = millis();
  
  if (client.connected())
  {
  Serial.println("Connecting to ThingSpeak...");
    Serial.println();
  
    failedCounter = 0;
    }
    else
    {
    failedCounter++;
  
    Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");
    Serial.println();
    }
  
  }
  else
  {
  failedCounter++;
  
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");
    Serial.println();
  
    lastConnectionTime = millis();
    }   
    client.stop();
}
