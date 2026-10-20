/*
 * ARQUIVO: Teste.h
 * OBJETIVO: Módulo de testes unitários para validação de integridade do sistema.
 * FUNÇÃO: Executa uma bateria de verificações automáticas durante a inicialização (setup).
 *         Garante que as configurações de hardware (pinos), software (comandos IR) 
 *         e estados de variáveis estejam corretos antes do loop principal rodar, 
 *         facilitando a depuração e prevenindo falhas silenciosas.
 */

// Evita que este arquivo seja incluído mais de uma vez durante a compilação
#pragma once

// Inclui as funções básicas do Arduino e os dados do projeto necessários para os testes
#include <Arduino.h>
#include "Comandos.h"
#include "Variaveis.h"

// Imprime no monitor serial se a validação do código passou ou falhou
void rodarTeste(bool condicao, const char* nomeDoTeste) {
  // Avalia a condição e exibe a etiqueta correspondente
  if (condicao) {
    Serial.print("[PASSOU] ");
  } else {
    Serial.print("[FALHOU] ");
  }
  
  // Exibe a descrição do que foi testado logo após o resultado
  Serial.println(nomeDoTeste);
}

// Executa em lote todas as validações de integridade do código
void executarTodosOsTestes() {
  // Imprime o cabeçalho indicando o início das verificações
  Serial.println("...A INICIAR TESTES...");
  
  // Calcula o total de botões dividindo o tamanho total da lista pelo tamanho de um único item
  int qtdBotoes = sizeof(botoes) / sizeof(Comando);
  
  // TESTE 1: Valida se a quantidade de comandos cadastrados atende ao novo formato (agora 7 comandos)
  rodarTeste(qtdBotoes == 7, "Existem exatamente 7 comandos configurados na memoria.");
  
  // TESTE 2: Assegura que as ações de energia estão nas posições exigidas pela lógica do sensor
  bool nomesCorretos = (strcmp(botoes[0].nome, "Ligar") == 0 && strcmp(botoes[1].nome, "Desligar") == 0);
  rodarTeste(nomesCorretos, "Os comandos nos indices 0 e 1 sao 'Ligar' e 'Desligar'.");
  
  // TESTE 3: Garante que o código hexadecimal do botão Mudo foi devidamente ajustado (busca dinamicamente o último item)
  bool mudoCorrigido = (botoes[qtdBotoes - 1].comando == 0x14);
  rodarTeste(mudoCorrigido, "O comando 'Mudo' (ultimo da lista) tem o valor hexadecimal correto (0x14).");
  
  // TESTE 4: Varre toda a lista assegurando que não misturamos protocolos de controles diferentes
  bool todosSony = true;
  for(int i = 0; i < qtdBotoes; i++) {
    if(botoes[i].protocolo != SONY) {
      todosSony = false;
      break; // Interrompe imediatamente se achar um protocolo intruso
    }
  }
  rodarTeste(todosSony, "Todos os botoes utilizam o protocolo SONY.");

  // TESTE 5: Garante que a emissão está focada no mesmo aparelho (TV) usando o mesmo endereço
  bool enderecoCorreto = true;
  for(int i = 0; i < qtdBotoes; i++) {
    if(botoes[i].endereco != 0x1) {
      enderecoCorreto = false;
      break; // Interrompe imediatamente se o endereço não for da TV
    }
  }
  rodarTeste(enderecoCorreto, "Todos os botoes partilham o mesmo endereco (0x1).");

  // TESTE 6: Valida se os pinos de comunicação IR estão mapeados onde o hardware exige
  bool pinosIrCorretos = (PINO_RECEPTOR == 2 && PINO_EMISSOR == 3);
  rodarTeste(pinosIrCorretos, "O Receptor (Pino 2) e o Emissor (Pino 3) estao corretos.");

  // TESTE 7: Verifica as portas dedicadas ao envio e retorno do pulso ultrassônico
  bool pinosSensorCorretos = (PINO_TRIG == 4 && PINO_ECHO == 8);
  rodarTeste(pinosSensorCorretos, "Os pinos do Sensor Ultrassonico (Trig: 4, Echo: 8) estao corretos.");

  // TESTE 8: Assegura que o feedback visual está ligado nas saídas digitais planejadas
  bool pinosLedsCorretos = (PINO_LED_EMISSOR == 12 && PINO_LED_RECEPTOR == 13);
  rodarTeste(pinosLedsCorretos, "Os pinos dos LEDs (Emissor: 12, Receptor: 13) estao corretos.");

  // TESTE 9: Cruza as informações dos pinos para impedir curto-circuito lógico (pinos repetidos)
  bool semConflito = (PINO_RECEPTOR != PINO_EMISSOR && PINO_TRIG != PINO_ECHO && PINO_RECEPTOR != PINO_TRIG);
  rodarTeste(semConflito, "Nao ha pinos duplicados nas definicoes principais.");

  // TESTE 10: Garante que o estado das variáveis permite a leitura do controle e do sensor logo ao ligar
  bool variaveisIniciaisOk = (temCodigo == false && horarioUltimoEnvio == 0);
  rodarTeste(variaveisIniciaisOk, "As variaveis de controle de estado iniciaram com valores padrao (zeradas).");

  // Imprime o rodapé indicando que a rotina de avaliação foi concluída
  Serial.println("...FIM DOS TESTES...\n");
}