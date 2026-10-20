// Biblioteca para comunicação infravermelha
#include <IRremote.h>
// Importa os módulos com a lógica e configurações do projeto
#include "Comandos.h"
#include "Variaveis.h"
#include "Receptor.h"
#include "Emissor.h"
#include "Sensor.h" 
#include "Teste.h"

void setup() {
  // Inicia a comunicação com o monitor serial
  Serial.begin(9600);
  
  // Configura o pino e inicializa o receptor IR
  iniciarReceptor();
  
  // Configura o pino e inicializa o emissor IR
  iniciarEmissor();
  
  // Configura os pinos do sensor ultrassônico
  iniciarSensor();
  
  // Faz uma leitura inicial para limpar o buffer do receptor
  lerReceptor();
  
  // Verifica se as configurações e a lista de comandos estão corretas
  executarTodosOsTestes();
  
  // Exibe a instrução de uso inicial no monitor serial
  Serial.println("Digite o nome de um comando (ex: Aumentar_Volume, Mudo) para testar...");
}

void loop() {
  // Fica ouvindo o controle remoto o tempo todo
  lerReceptor();
  
  // Verifica se o usuário digitou algum texto no monitor serial
  if (Serial.available()) {
    String entrada = Serial.readStringUntil('\n'); 
    entrada.trim(); 
    
    // Confirma se o texto recebido não está vazio
    if (entrada.length() > 0) {
      // Busca o comando pelo nome e dispara o sinal IR correspondente
      enviarComando(entrada.c_str());
    }
  }
  
  // Lê a distância do obstáculo e executa ações conforme a configuração
  verificarSensorUltrassonico();
}