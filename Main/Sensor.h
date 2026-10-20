// Evita que este arquivo seja incluído mais de uma vez durante a compilação
#pragma once

// Bibliotecas base para o funcionamento do Arduino e emissão infravermelha
#include <Arduino.h>
#include <IRremote.h>

// Importa as configurações globais, lista de comandos e mensagens centralizadas
#include "Variaveis.h"
#include "Comandos.h"

// Prepara os pinos do sensor ultrassônico na inicialização do sistema
void iniciarSensor() {
  // Configura o pino Trigger como saída para poder emitir o pulso sonoro
  pinMode(PINO_TRIG, OUTPUT);
  
  // Configura o pino Echo como entrada para poder ouvir o retorno do som
  pinMode(PINO_ECHO, INPUT);
}

// Dispara o pulso sonoro, mede a distância e aciona a TV caso detecte o gesto
void verificarSensorUltrassonico() {
  // Garante que o pino TRIG esteja sem energia (nível baixo) antes do disparo
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);

  // Dispara o pulso sonoro ativando a energia no pino TRIG
  digitalWrite(PINO_TRIG, HIGH);
  
  // Mantém o disparo ativo por 10 microssegundos (tempo exigido pelo sensor HC-SR04)
  delayMicroseconds(10);
  
  // Desliga o disparo, finalizando a emissão do pulso
  digitalWrite(PINO_TRIG, LOW);

  // Mede o tempo exato que o sinal levou para bater no obstáculo e voltar ao Echo
  long duracao = pulseIn(PINO_ECHO, HIGH);
  
  // Converte o tempo do som em distância real (centímetros), dividindo por 2 (ida e volta)
  float distancia = duracao * 0.0343 / 2;
  
  // Captura o tempo atual de funcionamento do Arduino para controlar o atraso entre gestos
  unsigned long agora = millis();
  
  // Se a mão estiver entre 5 e 10 cm E já tiverem passado 10 segundos desde o último envio
  if (distancia > 5 && distancia <= 10 && (agora - horarioUltimoEnvio >= 10000)) {
    // Exibe o aviso no monitor serial centralizado informando a detecção
    Serial.println("Movimento detectado: Enviando Ligar_Desligar");
    
    // Pausa a recepção IR temporariamente para evitar falhas de interferência
    IrReceiver.stop();
    
    // Dispara o sinal do primeiro comando da lista (posição 0 = Ligar_Desligar)
    IrSender.sendSony(botoes[0].endereco, botoes[0].comando, 2);
    
    // Reativa a recepção IR para voltar a ler o controle remoto físico
    IrReceiver.start();
    
    // Atualiza o contador de tempo para impedir que o comando seja enviado repetidamente
    horarioUltimoEnvio = agora;
  }
}