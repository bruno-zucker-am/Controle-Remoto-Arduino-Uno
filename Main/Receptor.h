// Evita que este arquivo seja incluído mais de uma vez durante a compilação
#pragma once

// Biblioteca principal para o funcionamento do módulo receptor infravermelho
#include <IRremote.h>

// Importa as dependências do projeto para acesso a variáveis globais e mensagens centralizadas
#include "Variaveis.h"
#include "Comandos.h"

// Configura os pinos e inicia a escuta do módulo receptor IR
void iniciarReceptor() {
  // Inicia o módulo no pino configurado e ativa o feedback visual padrão da biblioteca
  IrReceiver.begin(PINO_RECEPTOR, ENABLE_LED_FEEDBACK);
  
  // Configura o pino do LED indicador de recepção como saída de energia
  pinMode(PINO_LED_RECEPTOR, OUTPUT);
  
  // Exibe a mensagem de instrução inicial no monitor serial
  Serial.println("Pronto. Aponte o controle para o receptor...");
}

// Verifica constantemente se há novos sinais chegando e processa os dados recebidos
void lerReceptor() {
  // Confirma se um sinal infravermelho foi detectado e convertido pela biblioteca
  if (IrReceiver.decode()) {
    
    // Verifica se o protocolo do controle remoto (ex: NEC, SONY) é reconhecido
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      // Exibe os dados detalhados (protocolo, endereço e comando) em formato hexadecimal
      Serial.print("Protocolo: ");
      Serial.print(getProtocolString(IrReceiver.decodedIRData.protocol));
      Serial.print(" | Endereço: 0x");
      Serial.print(IrReceiver.decodedIRData.address, HEX);
      Serial.print(" | Comando: 0x");
      Serial.println(IrReceiver.decodedIRData.command, HEX);
      
      // Salva os dados do sinal na variável global para possibilitar o reenvio futuro
      ultimoCodigo = IrReceiver.decodedIRData;
      
      // Sinaliza (flag) para o resto do sistema que um novo código válido está disponível
      temCodigo = true;
      
    } else if (IrReceiver.decodedIRData.rawlen > 6) {
      // Se for um sinal não reconhecido, mas tiver tamanho suficiente para não ser apenas ruído
      Serial.print("Protocolo desconhecido (sinal bruto):");
      
      // Exibe os tempos brutos de pulso e pausa (RAW) para análise e depuração
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    
    // Pisca o LED indicador por 50 milissegundos para dar um retorno visual ao usuário
    digitalWrite(PINO_LED_RECEPTOR, HIGH);
    delay(50);
    digitalWrite(PINO_LED_RECEPTOR, LOW);
    
    // Limpa a leitura atual e libera o módulo receptor para escutar o próximo botão
    IrReceiver.resume();
  }
}