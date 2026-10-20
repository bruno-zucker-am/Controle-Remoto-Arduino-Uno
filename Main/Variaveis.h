// Evita que este arquivo seja incluído mais de uma vez durante a compilação
#pragma once

// Biblioteca base para as estruturas de dados e comunicação infravermelha
#include <IRremote.h>

// Define o pino digital onde o módulo receptor IR está conectado
#define PINO_RECEPTOR 2

// Define o pino digital onde o módulo emissor IR está conectado
#define PINO_EMISSOR 3

// Define o pino do LED que acende para indicar o envio de um sinal
#define PINO_LED_EMISSOR 12

// Define o pino do LED que acende para indicar o recebimento de um sinal
#define PINO_LED_RECEPTOR 13 

// Define o pino Trigger que emite o pulso sonoro do sensor ultrassônico
#define PINO_TRIG 4

// Define o pino Echo que recebe o retorno (eco) do pulso ultrassônico
#define PINO_ECHO 8

// Armazena todas as propriedades estruturadas do último sinal capturado pelo receptor
IRData ultimoCodigo;

// Variável de controle (flag) que indica se um novo código foi recebido e aguarda processamento
bool temCodigo = false;

// Guarda o tempo (em milissegundos) do último acionamento para controlar o intervalo (delay) sem travar o código
unsigned long horarioUltimoEnvio = 0;