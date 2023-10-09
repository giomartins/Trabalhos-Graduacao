// Declaração de Variáveis
int botao_Pino = 13;
int led_Pino = 2;
int estado_Botao = LOW;

void setup() {
  	// Pino do Botão
	pinMode(botao_Pino, INPUT);
  	// Pino do Led
  	pinMode(led_Pino, OUTPUT);
}

void loop() {
  // Leitura do Estado da Chave
  estado_Botao = digitalRead(botao_Pino);
  
  // A chave foi pressionada
  if(estado_Botao == HIGH) {
    // Aguarda a liberação da Chave
    while(digitalRead(botao_Pino) == HIGH) {} // Passo 1
    
    // Acende o Led
    digitalWrite(led_Pino, HIGH); // Passo 2
    delay(1000);
    // Desliga o Led
    digitalWrite(led_Pino, LOW); // Passo 3
    delay(2000);
    
    // Pisca o Led - Passo 4
    digitalWrite(led_Pino,HIGH);
    delay(250);
    digitalWrite(led_Pino, LOW);
    delay(250);
  }
  // Fim do Loop - Passo 5
}

