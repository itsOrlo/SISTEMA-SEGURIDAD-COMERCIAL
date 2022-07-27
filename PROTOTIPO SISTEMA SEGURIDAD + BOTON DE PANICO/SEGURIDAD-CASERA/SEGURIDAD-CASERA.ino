
/* SISTEMA DE SEGURIDAD + BOTÓN DE PÁNICO */

// Librerías usadas para módulo específico.
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// SSID y Password Wifi
const char* ssid = "FLIA CANO";
const char* password = ".Jeremy23";

// Token Telegram
#define BOTtoken "5460291640:AAFaTuaJdguqxV-PDzK4H811uCfMBoOcwkk"

// IDBot
#define CHAT_ID "1056292998"
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Verifica intervalo de mensajes.
int botRequestDelay = 500;
unsigned long lastTimeBotRan;

// LEDS
const int ledOn = D0; //Rele
const int ledOff = D1; // Apagado
const int ledEmergencia = D2; // Alarma

// Ultrasónico
const int Trig = D3; // Trig
const int Echo = D4; // Echo
long t; // Tiempo respuesta ECO
long d; // Distancia

// Infrarojo
const int infra = D5;
const int sensorPir = D6;

// Remoto
const int encenderB1 = D7;

//control activador
boolean activador = false;

void setup() {
  Serial.begin(100);

#ifdef ESP8266
  configTime(0, 0, "pool.ntp.org");      // Tiempo por Protocolo NTP
  client.setTrustAnchors(&cert); // Certificado api.telegram.org
#endif

  // Remoto
  pinMode(encenderB1, INPUT);

  //leds
  pinMode(ledOn, OUTPUT);
  pinMode(ledOff, OUTPUT);
  pinMode(ledEmergencia, OUTPUT);
  digitalWrite(ledOn, LOW);
  digitalWrite(ledOff, LOW);
  digitalWrite(ledEmergencia, LOW);
  
  // Ultrasónico
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Echo, LOW);
  //infrarojo
  pinMode(infra, INPUT);
  //PIR
  pinMode(sensorPir, INPUT_PULLUP);
  int pir = 0;

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

#ifdef ESP32
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Agregamos el certificado raiz para api.telegram.org
#endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  
  bot.sendMessage(CHAT_ID, "Modulo conectado a internet, puede empezar a usar el bot /start", "");

}

void loop() {

  if(digitalRead(encenderB1) == HIGH){

      bot.sendMessage(CHAT_ID, "Emergencia!!!!! botón de pánico activado!", "");
    
  }
  
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    //activar
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(Trig, LOW);

    //distancias
    t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
    d = t * (0.034 / 2);         //escalamos el tiempo a una distancia en cm

    //infra
    int pir = digitalRead(infra);

    if (activador == true) {
      //sonico
      if (d < 27 || d > 35) {
        bot.sendMessage(CHAT_ID, "Emergencia!!!!! revise su puerta", "");
        digitalWrite(ledOn, LOW);
        digitalWrite(ledOff, LOW);
        digitalWrite(ledEmergencia, HIGH);
      }
      //infrarrojo
      if (pir != 1) {
        bot.sendMessage(CHAT_ID, "Emergencia!!!!! revise su ventana", "");
        digitalWrite(ledOn, LOW);
        digitalWrite(ledOff, LOW);
        digitalWrite(ledEmergencia, HIGH);
      }

    }

    while (numNewMessages) {
      Serial.println("");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}

/* MÉTODOS */

// Maneja lo que Sucede Cuando se recibe un nuevo mensaje
void handleNewMessages(int numNewMessages) {
  
    for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);

    // Imprime el mensaje recibido
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Bienvenido, " + from_name + ".\n";
      welcome += "Use los siguientes comandos para controlar tu sistema de seguridad.\n\n";
      welcome += "/on -> activar el sistema \n";
      welcome += "/off -> desactivar el sistema \n";
      welcome += "/state -> obtener informacion del estado actual del sistema \n";
      welcome += "/emergencia -> entrar en modo emergencia \n";

      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/on") {
      bot.sendMessage(chat_id, "Sistema encendido", "");
      digitalWrite(ledOn, HIGH);
      digitalWrite(ledOff, LOW);
      digitalWrite(ledEmergencia, LOW);
  
      //acivador
      activador = true;

    } else if (text == "/off") {
      bot.sendMessage(chat_id, "Sistema desactivado", "");
      digitalWrite(ledOn, LOW);
      digitalWrite(ledOff, HIGH);
      digitalWrite(ledEmergencia, LOW);
      
      // Activador
      activador = false;

    } else if (text == "/emergencia") {
      
      // Activador
      activador = true;

      bot.sendMessage(chat_id, "Emergencia!!", "");
      digitalWrite(ledOn, LOW);
      digitalWrite(ledOff, LOW);
      digitalWrite(ledEmergencia, HIGH);

    } else if (text == "/state") {
      if (digitalRead(ledOn)) {
        bot.sendMessage(chat_id, "Sistema encendido", "");

      } else if (digitalRead(ledOff)) {
        bot.sendMessage(chat_id, "Sistema apagado", "");

      } else if (digitalRead(ledEmergencia)) {
        bot.sendMessage(chat_id, "Emergencia activa", "");

      } else {
        bot.sendMessage(chat_id, "Sistema desactivado", "");
      }
    }
  }
}
