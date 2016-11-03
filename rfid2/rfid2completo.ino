#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>

//pin output
#define LED1G  24
#define LED1Y  25
#define LED1R  26
#define LED2G  28
#define LED2Y  29
#define LED2R  30

boolean reading = false;
int count = 0;
boolean pino = false;

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte ip[] = {10, 62, 2, 5};    //Manual setup only

// if need to change the MAC address (Very Rare)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
String tempo = "";
String sem1 = "";
String sem2 = "";
int t1 = 0;
int t2 = 0;
EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int qtd1 = 0;
int qtd2 = 0;

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

  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("S. C. T. ");
  lcd.setCursor(3, 1);
  lcd.print("| Time:");

}

void loop() {
  checkForClient();
  //
  //  qtd1 = random(20);
  //  qtd2 = random(20);
  //  // qtd1 = 10;
  //  //  qtd2 = 8;
  //
  //  Serial.print("\nSemaforo 1 | Quantidade de carro : ");
  //  Serial.print(qtd1);
  //  Serial.print("\nSemaforo 2 | Quantidade de carro : ");
  //  Serial.print(qtd2);
  //  Serial.println("\n");
  //  //  int qtd1  = 10; // Quantidade de carros 10 .... Semaforo 1
  //  //  int qtd2  = 15;// Quantidade de carros 10 .... Semaforo 2 e se este semaforo etiver cheio
  //
  //  if (qtd2 < qtd1) {
  //    s1_60(); //60 seg
  //
  //  } else if (qtd2 > qtd1) {
  //    s2_60();//60 seg
  //  }
}

//S1 60 segundos
void s1_60() {
  lcd.setCursor(0, 1);
  lcd.print("S1");
  for (int i = 60; i >= 10 ; i--) {
    lcd.setCursor(11, 1);
    lcd.print(i);
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s1
    digitalWrite(LED1R, LOW);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, HIGH);
    //s2
    digitalWrite(LED2R, HIGH);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, LOW);
    delay(500);
  }

  for (int i = 9; i >= 0; i--) {

    lcd.setCursor(11, 1);
    lcd.print("0");
    lcd.setCursor(12, 1);
    lcd.print(i);
    lcd.setCursor(13, 1);
    lcd.print(" ");
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s1
    digitalWrite(LED1R, LOW);
    digitalWrite(LED1Y, HIGH);
    digitalWrite(LED1G, LOW);
    //s2
    digitalWrite(LED2R, HIGH);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, LOW);
    delay(500);
  }

  s2_30();
}



//S1 30 segundos
void s1_30() {
  lcd.setCursor(0, 1);
  lcd.print("S1");
  for (int i = 30; i >= 10 ; i--) {
    lcd.setCursor(11, 1);
    lcd.print(i);
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s1
    digitalWrite(LED1R, LOW);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, HIGH);
    //s2
    digitalWrite(LED2R, HIGH);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, LOW);
    delay(500);
  }

  for (int i = 9; i >= 0; i--) {

    lcd.setCursor(11, 1);
    lcd.print("0");
    lcd.setCursor(12, 1);
    lcd.print(i);
    lcd.setCursor(13, 1);
    lcd.print(" ");
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s1
    digitalWrite(LED1R, LOW);
    digitalWrite(LED1Y, HIGH);
    digitalWrite(LED1G, LOW);
    //s2
    digitalWrite(LED2R, HIGH);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, LOW);
    delay(500);
  }

  for (int i = 15; i >= 9; i--) {

    if (i == 9) {
      for (int i = 9; i >= 0; i--) {
        lcd.setCursor(11, 1);
        lcd.print("0");
        lcd.setCursor(12, 1);
        lcd.print(i);
        lcd.setCursor(13, 1);
        lcd.print(" ");
        Serial.println();
        Serial.print("Tempo : ");
        Serial.print(i);
        //s2
        digitalWrite(LED2R, HIGH);
        digitalWrite(LED2Y, LOW);
        digitalWrite(LED2G, LOW);
        //s1
        digitalWrite(LED1R, HIGH);
        digitalWrite(LED1Y, LOW);
        digitalWrite(LED1G, LOW);
        delay(500);

      }

      break;
    }
    lcd.setCursor(11, 1);
    lcd.print(i);
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s2
    digitalWrite(LED2R, HIGH);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, LOW);
    //s1
    digitalWrite(LED1R, HIGH);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, LOW);
    delay(500);
  }
}

//s2 60 segundos
void s2_60() {
  lcd.setCursor(0, 1);
  lcd.print("S2");
  for (int i = 60; i >= 10 ; i--) {
    lcd.setCursor(11, 1);
    lcd.print(i);
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s2
    digitalWrite(LED2R, LOW);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, HIGH);
    //s1
    digitalWrite(LED1R, HIGH);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, LOW);
    delay(500);
  }

  for (int i = 9; i >= 0; i--) {

    lcd.setCursor(11, 1);
    lcd.print("0");
    lcd.setCursor(12, 1);
    lcd.print(i);
    lcd.setCursor(13, 1);
    lcd.print(" ");
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s2
    digitalWrite(LED2R, LOW);
    digitalWrite(LED2Y, HIGH);
    digitalWrite(LED2G, LOW);
    //s1
    digitalWrite(LED1R, HIGH);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, LOW);
    delay(500);
  }

  s1_30();
}


//s2 30 segundos
void s2_30() {
  lcd.setCursor(0, 1);
  lcd.print("S2");
  for (int i = 30; i >= 10 ; i--) {
    lcd.setCursor(11, 1);
    lcd.print(i);
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s2
    digitalWrite(LED2R, LOW);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, HIGH);
    //s1
    digitalWrite(LED1R, HIGH);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, LOW);
    delay(500);
  }

  for (int i = 9; i >= 0; i--) {

    lcd.setCursor(11, 1);
    lcd.print("0");
    lcd.setCursor(12, 1);
    lcd.print(i);
    lcd.setCursor(13, 1);
    lcd.print(" ");
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s2
    digitalWrite(LED2R, LOW);
    digitalWrite(LED2Y, HIGH);
    digitalWrite(LED2G, LOW);
    //s1
    digitalWrite(LED1R, HIGH);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, LOW);
    delay(500);
  }

  for (int i = 15; i >= 9; i--) {

    if (i == 9) {
      for (int i = 9; i >= 0; i--) {
        lcd.setCursor(11, 1);
        lcd.print("0");
        lcd.setCursor(12, 1);
        lcd.print(i);
        lcd.setCursor(13, 1);
        lcd.print(" ");
        Serial.println();
        Serial.print("Tempo : ");
        Serial.print(i);

        //s2
        digitalWrite(LED2R, HIGH);
        digitalWrite(LED2Y, LOW);
        digitalWrite(LED2G, LOW);
        //s1
        digitalWrite(LED1R, HIGH);
        digitalWrite(LED1Y, LOW);
        digitalWrite(LED1G, LOW);
        delay(500);

      }

      break;
    }
    lcd.setCursor(11, 1);
    lcd.print(i);
    Serial.println();
    Serial.print("Tempo : ");
    Serial.print(i);
    //s2
    digitalWrite(LED2R, HIGH);
    digitalWrite(LED2Y, LOW);
    digitalWrite(LED2G, LOW);
    //s1
    digitalWrite(LED1R, HIGH);
    digitalWrite(LED1Y, LOW);
    digitalWrite(LED1G, LOW);
    delay(500);
  }
}

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



        //

        if (c == '!') reading = false;
        if (c == '?') reading = true; //found the ?, begin reading the info

        if (reading) {
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
          if (count > 7 && contador == 1) {

            t1 = sem1.toInt();
            t2 = sem2.toInt();

            if (t2 < t1) {
              s1_60(); //60 seg

            } else if (t2 > t1) {
              s2_60();//60 seg
            }




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





