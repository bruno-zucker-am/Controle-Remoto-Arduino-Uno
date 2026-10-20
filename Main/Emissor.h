// Evita que este arquivo seja incluído mais de uma vez durante a compilação
#pragma once

// Bibliotecas base para o funcionamento do Arduino e do emissor infravermelho
#include <Arduino.h>
#include <IRremote.h>

// Importa as configurações, a lista de comandos e as mensagens centralizadas do sistema
#include "Variaveis.h"
#include "Comandos.h"

// Configura os pinos e prepara o módulo emissor IR para funcionar
void iniciarEmissor() {
  // Inicia o módulo emissor no pino especificado pelas configurações globais
  IrSender.begin(PINO_EMISSOR);
  
  // Configura o pino do LED indicador de envio como saída de energia
  pinMode(PINO_LED_EMISSOR, OUTPUT);
}

// Procura o comando pelo nome recebido e dispara o sinal infravermelho correspondente
void enviarComando(const char* nomeDoBotao) {

  // Percorre toda a lista de comandos cadastrados para tentar encontrar uma correspondência
  for (int posicao = 0; posicao < sizeof(botoes) / sizeof(Comando); posicao++) {

    // Verifica se o nome digitado é exatamente igual ao nome do comando atual da lista
    if (strcmp(botoes[posicao].nome, nomeDoBotao) == 0) {
      
      // Exibe no monitor serial qual comando está sendo enviado
      Serial.print("Enviando: ");
      Serial.println(nomeDoBotao);
      
      // Desativa temporariamente o receptor para evitar interferência cruzada durante a emissão
      IrReceiver.stop();
      
      // Acende o LED para dar um retorno visual de que o sinal está sendo disparado
      digitalWrite(PINO_LED_EMISSOR, HIGH);
      
      // Dispara o sinal IR (protocolo SONY), enviando endereço e código com 2 repetições
      IrSender.sendSony(botoes[posicao].endereco, botoes[posicao].comando, 2);
      
      // Mantém o LED aceso por 100 milissegundos para que o brilho seja perceptível
      delay(100);
      digitalWrite(PINO_LED_EMISSOR, LOW);
      
      // Reativa o receptor para voltar a escutar os sinais do controle físico
      IrReceiver.start();
      
      // Encerra a função imediatamente, pois o comando já foi encontrado e executado
      return;
    }
  }
  
  // Exibe um aviso centralizado caso a busca termine sem encontrar o nome digitado
  Serial.println("Comando não encontrado...");
}