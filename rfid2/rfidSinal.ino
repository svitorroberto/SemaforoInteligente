#include <Ethernet.h>
#include <SPI.h>

//pin output
#define LED1G  4
#define LED1Y  3
#define LED1R  2
#define LED2G  7
#define LED2Y  6
#define LED2R  5

boolean reading = false;
int count = 0;
boolean pino = false;

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte ip[] = {10, 62, 2, 3};    //Manual setup only

// if need to change the MAC address (Very Rare)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
String tempo = "";
String sem1 = "";
String sem2 = "";
int t1 = 0;
int t2 = 0;
int tempoAmarelo = 9;
int semaforo = 0;
EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println(Ethernet.localIP());

  // put your setup code here, to run once:
  pinMode(LED1R, OUTPUT);
  pinMode(LED1Y, OUTPUT);
  pinMode(LED1G, OUTPUT);
  pinMode(LED2R, OUTPUT);
  pinMode(LED2Y, OUTPUT);
  pinMode(LED2G, OUTPUT);

}

void loop() {
  checkForClient();

}

/////////////////////////////////////////////////////
//CICLO DOS SINAIS SEMPRE COMECANDO PELO SEMAFORO 1//
/////////////////////////////////////////////////////
void ciclo(int semaforo, int tempo){
    for (int i = tempo; i >= (tempoAmarelo+1) ; i--) {
    Serial.println();
    if(semaforo==1){
      Serial.print("Semaforo 1 Verde: ");
      Serial.print(i);
      digitalWrite(LED1R, LOW);
      digitalWrite(LED1Y, LOW);
      digitalWrite(LED1G, HIGH);
      //s2
      digitalWrite(LED2R, HIGH);
      digitalWrite(LED2Y, LOW);
      digitalWrite(LED2G, LOW);
      delay(500);
    }
    else{
      Serial.print("Semaforo 2 Verde: ");
      Serial.print(i);
      digitalWrite(LED2R, LOW);
      digitalWrite(LED2Y, LOW);
      digitalWrite(LED2G, HIGH);
      //s2
      digitalWrite(LED1R, HIGH);
      digitalWrite(LED1Y, LOW);
      digitalWrite(LED1G, LOW);
      delay(500);
      t1=0;
    }

  }
  if(t1>0){
    transicao(1);
  }
  else{
    transicao(2);
  }
  
}
void transicao(int semaforo){
  for (int i = tempoAmarelo; i >= 0 ; i--) {
    Serial.println();
    
  if(semaforo==1){
    Serial.print("Semaforo 1 Amarelo : ");
    Serial.print(i);
      digitalWrite(LED1R, LOW);
      digitalWrite(LED1Y, HIGH);
      digitalWrite(LED1G, LOW);
      //s2
      digitalWrite(LED2R, HIGH);
      digitalWrite(LED2Y, LOW);
      digitalWrite(LED2G, LOW);
      delay(500);
    }
    else{
      Serial.print("Semaforo 2 Amarelo : ");
      Serial.print(i);
      digitalWrite(LED2R, LOW);
      digitalWrite(LED2Y, HIGH);
      digitalWrite(LED2G, LOW);
      //s2
      digitalWrite(LED1R, HIGH);
      digitalWrite(LED1Y, LOW);
      digitalWrite(LED1G, LOW);
      delay(500);
    }
  }
  if(t1>0){
    ciclo(2,t2);
  }
  else{
      digitalWrite(LED2R, LOW);
      digitalWrite(LED2Y, LOW);
      digitalWrite(LED2G, LOW);
      //s2
      digitalWrite(LED1R, LOW);
      digitalWrite(LED1Y, LOW);
      digitalWrite(LED1G, LOW);
  }
}
/////////////////////////////////////////////////////
///////////////////////////////
//RECEBER TEMPO PELA URL//////
//////////////////////////////
void checkForClient() {

  EthernetClient client = server.available();
  int contador = 0;
  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;

    while (client.connected()) {
      if (client.available()) {

        if (!sentHeader) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          sentHeader = true;
        }

        char c = client.read();

        if (c == '!') reading = false;
        if (c == '?') reading = true; //found the ?, begin reading the info
        
        if (reading) {
          tempo += c;
          switch (c) {
            case '0': triggerPin(0, client);
              break;
            case '1': triggerPin(1, client);
              break;
            case '2':  triggerPin(2, client);
              break;
            case '3':  triggerPin(3, client);
              break;
            case '4': triggerPin(4, client);
              break;
            case '5': triggerPin(5, client);
              break;
            case '6':  triggerPin(6, client);
              break;
            case '7': triggerPin(7, client);
              break;
            case '8': triggerPin(8, client);
              break;
            case '9': triggerPin(9, client);
              break;
            case '-': separador('-', client);
              break;
          }
          count++;
          contador++;
          if (count > 7 && contador == 1) {

            t1 = sem1.toInt();
            t2 = sem2.toInt();

            client.println("Iniciando o cilo 1");
            ciclo(1,t1);
            

            tempo = "";
            count = 0;
            sem1 = "";
            sem2 = "";
            pino = false;
            contador = 0;
          }
        }

        if (c == '\n' && currentLineIsBlank)  break;

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  }

}
/////////////////////////////////////////////////////
///////////////////////////////
//RECEBER TEMPO PELA URL//////
//////////////////////////////
void triggerPin(int pin, EthernetClient client) {
  //blink a pin - Client needed just for HTML output purposes.
  client.print("Turning on pin ");
  client.println(pin);
  client.print("<br>");
  if (!pino) {
    sem1 += pin;
  } else {
    sem2 += pin;
  }

}
void separador(char pin, EthernetClient client) {
  //blink a pin - Client needed just for HTML output purposes.
  client.print("Separador ");
  client.println(pin);
  client.print("<br>");

  pino = true;

}





