const int pinoLed = 2;
const int pinoBotao = 13;
int estadoBotao = 0;

enum Estados { AGUARDANDO, LED_ACESO, LED_APAGADO, PISCANDO, FINALIZANDO };
Estados estado = AGUARDANDO;

volatile bool botaoPressionado = false;
volatile bool temporizadorExpirado = false;

unsigned long millisAnterior = 0;
int contagemPiscadas = 0;  // Contador para o número de piscadas

const unsigned long intervaloTemporizador = 250;  // Intervalo do temporizador em milissegundos

void setup() {
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoBotao, INPUT);

  // Configurar a interrupção para o pino do botão
  attachInterrupt(digitalPinToInterrupt(pinoBotao), botaoInterrupcao, RISING);

  // Configurar o temporizador
  setupTemporizador();
}

void loop() {
  unsigned long millisAtual = millis();

  // Verificar se o temporizador expirou
  if (temporizadorExpirado) {
    temporizadorExpirado = false;

    switch (estado) {
      case PISCANDO:
        digitalWrite(pinoLed, !digitalRead(pinoLed)); // Inverter o estado do LED
        break;
    }
  }

  // Restante do seu código permanece inalterado
  switch (estado) {
    case AGUARDANDO:
      estadoBotao = digitalRead(pinoBotao);
      if (estadoBotao == HIGH) {
        delay(50); // Debounce
        while(digitalRead(pinoBotao) == HIGH); // Espera liberar
        estado = LED_ACESO;
        millisAnterior = millisAtual;
      }
      break;

    case LED_ACESO:
      digitalWrite(pinoLed, HIGH);
      if (millisAtual - millisAnterior >= 1000) {
        estado = LED_APAGADO;
        millisAnterior = millisAtual;
      }
      break;

    case LED_APAGADO:
      digitalWrite(pinoLed, LOW);
      if (millisAtual - millisAnterior >= 2000) {
        estado = PISCANDO;
        millisAnterior = millisAtual;
      }
      break;

    case PISCANDO:
      if ((millisAtual - millisAnterior >= 250) && (contagemPiscadas < 6)) {
        digitalWrite(pinoLed, !digitalRead(pinoLed)); // Inverte o estado do LED
        millisAnterior = millisAtual;
        contagemPiscadas++;
      }
      if (contagemPiscadas >= 6) {
        contagemPiscadas = 0; // Reinicia o contador de piscadas
        estado = FINALIZANDO;
      }
      break;

    case FINALIZANDO:
      digitalWrite(pinoLed, LOW);
      estado = AGUARDANDO;
      break;
  }
}

// Função de interrupção para o botão
void botaoInterrupcao() {
  botaoPressionado = true;
}

// Configurar o temporizador
void setupTemporizador() {
  noInterrupts();  // Desabilitar interrupções durante a configuração

  // Configurar o temporizador 1 (para Arduino Uno)
  TCCR1A = 0;      // Modo normal
  TCCR1B = 0;      // Limpar registrador de controle
  TCNT1 = 0;       // Zerar contador

  // Calcular o valor para OCR1A (com base no clock do Arduino Uno de 16MHz)
  OCR1A = (intervaloTemporizador * 16) - 1;

  // Configurar o temporizador para operar no modo CTC (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);

  // Selecionar o prescaler (1024 para intervalo de 250ms)
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Habilitar a interrupção de comparação A
  TIMSK1 |= (1 << OCIE1A);

  interrupts();  // Habilitar interrupções após a configuração
}

// Rotina de interrupção para o temporizador
ISR(TIMER1_COMPA_vect) {
  temporizadorExpirado = true;
}
