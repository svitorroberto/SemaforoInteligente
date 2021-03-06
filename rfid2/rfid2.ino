//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY


#include <Ethernet.h>
#include <SPI.h>
boolean reading = false;
int count = 0;
boolean pino = false;
////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
  byte ip[] = {10, 62, 2, 5};   //Manual setup only
  //byte gateway[] = { 192, 168, 0, 1 }; //Manual setup only
  //byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  String tempo = "";
  String sem1 = "";
  String sem2 = "";
  int t1=0;
  int t2=0;
  EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);

 

  Ethernet.begin(mac, ip);
  //Ethernet.begin(mac, ip, gateway, subnet); //for manual setup

  server.begin();
  Serial.println(Ethernet.localIP());

}

void loop(){
  // listen for incoming clients, and process qequest.
  checkForClient();

  

}

void checkForClient(){

  EthernetClient client = server.available();
  int contador = 0;
  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;

    while (client.connected()) {
      if (client.available()) {

        if(!sentHeader){
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          sentHeader = true;
        }

        char c = client.read();
        
        

      //  

        if(c == '!') reading = false;
        if(c == '?') reading = true; //found the ?, begin reading the info

        if(reading){
//          Serial.println();
//          Serial.println("["+c+"]");
          tempo += c;
           switch (c) {
            case '0':
              //add code here to trigger on 0
              triggerPin(0, client);
              break;
            case '1':
              //add code here to trigger on 1
              triggerPin(1, client);
              break;
            case '2':
              //add code here to trigger on 2
              triggerPin(2, client);
              break;
            case '3':
            //add code here to trigger on 3
              triggerPin(3, client);
              break;
            case '4':
            //add code here to trigger on 4
              triggerPin(4, client);
              break;
            case '5':
            //add code here to trigger on 5
              triggerPin(5, client);
              break;
            case '6':
            //add code here to trigger on 6
              triggerPin(6, client);
              break;
            case '7':
            //add code here to trigger on 7
              triggerPin(7, client);
              break;
            case '8':
            //add code here to trigger on 8
              triggerPin(8, client);
              break;
            case '9':
            //add code here to trigger on 9
              triggerPin(9, client);
              break;
            case '-':
            //add code here to trigger on -
              separador('-', client);
              break;
          }
          count++;
          contador++;
          if(count>7 && contador==1){
 //           Serial.println();
 //           Serial.println("Tempo: "+tempo);
            t1=sem1.toInt();
            t2=sem2.toInt();
            Serial.println(t1);
            Serial.println(t2);

            tempo="";
            count=0;
            sem1="";
            sem2="";
            pino = false;
            contador = 0;
          }
        }

        if (c == '\n' && currentLineIsBlank)  break;

        if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}

void triggerPin(int pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  client.print("Turning on pin ");
  client.println(pin);
  client.print("<br>");
  if(!pino){
    sem1 += pin;
  }else{
    sem2 += pin;
  }
  
}
void separador(char pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  client.print("Separador ");
  client.println(pin);
  client.print("<br>");

  pino = true;

}
