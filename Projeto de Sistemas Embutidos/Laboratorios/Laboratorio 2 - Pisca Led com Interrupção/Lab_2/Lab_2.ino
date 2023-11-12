#include <Arduino.h>

const int chavePin = 13;  // Pino da chave no Arduino Uno
const int ledPin = 2;   // Pino do LED no Arduino Uno

enum Estados { ESPERA, CHAVE_PRESSIONADA, CHAVE_LIBERADA, LED_ACESO, LED_APAGADO, LED_PISCANDO };
Estados estado = ESPERA;

unsigned long inicioEstado;
const long duracaoPulso = 250; // 250 ms


void setup() {
  Serial.begin(9600);
  pinMode(chavePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  switch (estado) {
    case ESPERA:
      Serial.println("Teste");
      if (chavePressionada()) {
        estado = CHAVE_PRESSIONADA;
        inicioEstado = millis();
      }
      break;

    case CHAVE_PRESSIONADA:
      Serial.println("Chave pressionada");
      if (!chavePressionada()) {
        estado = CHAVE_LIBERADA;
        inicioEstado = millis();
      }
      break;

    case CHAVE_LIBERADA:
      Serial.println("Chave solta");
      if (millis() - inicioEstado >= duracaoPulso) {
        estado = LED_ACESO;
        digitalWrite(ledPin, HIGH);
        inicioEstado = millis();
      }
      break;

    case LED_ACESO:
      Serial.println("1 Led");
      if (millis() - inicioEstado >= 1000) {
        estado = LED_APAGADO;
        digitalWrite(ledPin, LOW);
        inicioEstado = millis();
      }
      break;

    case LED_APAGADO:
      Serial.println("Led apagado");
      if (millis() - inicioEstado >= 2000) {
        estado = LED_PISCANDO;
        inicioEstado = millis();
      }
      break;

    case LED_PISCANDO:
      Serial.println(millis() - inicioEstado);
      if (millis() - inicioEstado >= 500) {
        delay(400);
        Serial.println("1");
        digitalWrite(ledPin, !digitalRead(ledPin)); // Inverte o estado do LED
      }
      if (millis() - inicioEstado >= 2000) {
        Serial.println("2");
        estado = ESPERA;
        digitalWrite(ledPin, LOW); // Garante que o LED está desligado no final
      }
      break;
  }
}

bool chavePressionada() {
  // Leitura da chave com debounce simples
  static bool ultimaLeitura = HIGH; // Estado anterior da chave
  bool leituraAtual = digitalRead(chavePin);
  if (leituraAtual != ultimaLeitura) {
    delay(5); // Debounce de 5 ms
    leituraAtual = digitalRead(chavePin);
    return true;
  }
  ultimaLeitura = leituraAtual;
  return false; // Retorna true no ciclo de descida
}