// Evita que este arquivo seja incluído mais de uma vez durante a compilação
#pragma once

// Biblioteca necessária para reconhecer os tipos de protocolos (decode_type_t)
#include <IRremote.h>

// Estrutura que agrupa as informações necessárias de cada botão do controle
struct Comando {
  const char* nome;        // Nome identificador do comando em formato de texto
  decode_type_t protocolo; // Família do protocolo de comunicação (NEC, SAMSUNG, SONY...)
  uint16_t endereco;       // Identifica o aparelho alvo; costuma ser igual para a mesma TV
  uint8_t comando;         // Código hexadecimal específico que executa a ação do botão
};

// Lista (array) contendo todos os comandos cadastrados que podem ser enviados
Comando botoes[] = {
  {"Ligar", SONY, 0X1, 0X15},
  {"Desligar", SONY, 0X1, 0X15},
  {"Volume+", SONY, 0X1, 0X12},
  {"Volume-", SONY, 0X1, 0X13},
  {"Canal+", SONY, 0X1, 0X10},
  {"Canal-", SONY, 0X1, 0X11},
  {"Mudo", SONY, 0X1, 0x14}
};