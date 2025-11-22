#include <WiFi.h>
#include <PubSubClient.h>

// Credenciais para acesso à rede e ao MQTT mosquitto
const char* ssid        = "Wokwi-GUEST";
const char* password    = "";
const char* mqtt_server = "test.mosquitto.org";

// Define os pinos dos componentes
#define POTENCIOMETRO 34
#define ledg 5   // verde
#define ledy 2   // amarelo
#define ledr 15  // vermelho

int leitura_pot = 0;
int pot         = 0;      // valor mapeado do potenciômetro

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando em ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Função para reconectar ao MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    String clientId = "Skillink-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando em 5 segundos...");
      delay(5000);
    }
  }
}

// publica leitura e status no MQTT
void sendMQTT(int pot, const char* status) {
  char payload[80];
  // exemplo de JSON simples
  snprintf(payload, sizeof(payload),
           "{\"batimentos\":%d,\"status\":\"%s\"}", pot, status);

  client.publish("skillink/batimentos", payload);
  Serial.print("MQTT -> ");
  Serial.println(payload);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledg, OUTPUT);
  pinMode(ledy, OUTPUT);
  pinMode(ledr, OUTPUT);
  pinMode(POTENCIOMETRO, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);

  randomSeed(micros());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();   // mantém a conexão MQTT

  // leitura do potenciômetro
  leitura_pot = analogRead(POTENCIOMETRO);      
  pot = map(leitura_pot, 0, 4095, 0, 1023);     

  const char* status;

  if (pot < 60) {
    // frequencia baixa -> LED amarelo
    digitalWrite(ledy, HIGH);
    digitalWrite(ledr, LOW);
    digitalWrite(ledg, LOW);
    status = "BAIXO";
  }
  else if (pot > 100) {
    // frequencia alta -> LED vermelho
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, LOW);
    digitalWrite(ledy, LOW);
    status = "ALTO";
  }
  else {
    // frequencia normal -> LED verde
    digitalWrite(ledg, HIGH);
    digitalWrite(ledy, LOW);
    digitalWrite(ledr, LOW);
    status = "NORMAL";
  }

  // envia a informação via MQTT
  sendMQTT(pot, status);
  delay(1000); 
}
