# Glossário

Os termos abaixo estão organizados por arquivo, na ordem em que aparecem no código.

# 1. Main/Main.ino

Já explicados antes: nenhum.

## 1.1 `IRremote.h`
É a biblioteca usada para enviar e receber sinais infravermelhos no Arduino, permitindo que o projeto converse com o controle remoto e com o módulo IR.
Aparece em: `#include <IRremote.h>` em `Main/Main.ino` e em `Main/Variaveis.h`.
Exemplo: `IrReceiver.begin(PINO_RECEPTOR, ENABLE_LED_FEEDBACK);` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 1.2 `Serial.begin`
É a função que inicializa a comunicação serial, permitindo que o Arduino envie mensagens para o monitor serial do computador.
Aparece em: `Serial.begin(9600);` em `Main/Main.ino`.
Exemplo: `Serial.println("Pronto. Aponte o controle para o receptor...");` em `Main/Receptor.h`.
Referência: https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/

## 1.3 `iniciarReceptor`
É a rotina que configura o pino do receptor IR e o coloca em modo de escuta para captar sinais do controle remoto.
Aparece em: `iniciarReceptor();` em `Main/Main.ino` e a definição `void iniciarReceptor()` em `Main/Receptor.h`.
Exemplo: `IrReceiver.begin(PINO_RECEPTOR, ENABLE_LED_FEEDBACK);` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 1.4 `lerReceptor`
É a função de leitura do módulo IR: ela detecta um sinal, valida o protocolo e salva o código recebido para processamento.
Aparece em: `lerReceptor();` em `Main/Main.ino` e `void lerReceptor()` em `Main/Receptor.h`.
Exemplo: `if (IrReceiver.decode()) { ... }` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 1.5 `enviarComando`
É a rotina que busca um comando pelo nome informado e dispara o sinal infravermelho equivalente para a TV.
Aparece em: `enviarComando(entrada.c_str());` em `Main/Main.ino` e `void enviarComando(const char* nomeDoBotao)` em `Main/Emissor.h`.
Exemplo: `IrSender.sendSony(botoes[posicao].endereco, botoes[posicao].comando, 2);` em `Main/Emissor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 1.6 `verificarSensorUltrassonico`
É a rotina que dispara o pulso ultrassônico, calcula a distância e envia um comando quando o gesto da mão é detectado.
Aparece em: `verificarSensorUltrassonico();` em `Main/Main.ino` e `void verificarSensorUltrassonico()` em `Main/Sensor.h`.
Exemplo: `if (distancia > 5 && distancia <= 10 && (agora - horarioUltimoEnvio >= 10000))` em `Main/Sensor.h`.
Referência: https://docs.arduino.cc/learn/electronics/hc-sr04/

# 2. Main/Comandos.h

Já explicados antes: nenhum.

## 2.1 `Comando`
É a estrutura que guarda o nome, o protocolo, o endereço e o código de um botão do controle remoto.
Aparece em: `struct Comando { ... }` em `Main/Comandos.h`.
Exemplo: `{"Ligar", SONY, 0X1, 0X15}` em `Main/Comandos.h`.
Referência: https://www.arduino.cc/reference/en/language/variables/data-types/struct/

## 2.2 `botoes[]`
É o array que armazena todos os comandos cadastrados que podem ser enviados para a TV.
Aparece em: `Comando botoes[] = { ... };` em `Main/Comandos.h`.
Exemplo: `{"Volume+", SONY, 0X1, 0X12}` em `Main/Comandos.h`.
Referência: https://www.arduino.cc/reference/en/language/variables/array/

## 2.3 `SONY`
É o protocolo infravermelho usado para a comunicação dos comandos com a TV.
Aparece em: `{"Ligar", SONY, 0X1, 0X15}` em `Main/Comandos.h`.
Exemplo: `botoes[i].protocolo != SONY` em `Main/Teste.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

# 3. Main/Variaveis.h

Já explicados antes: nenhum.

## 3.1 `PINO_RECEPTOR`
É a constante que indica o pino digital usado pelo módulo receptor IR.
Aparece em: `#define PINO_RECEPTOR 2` em `Main/Variaveis.h`.
Exemplo: `IrReceiver.begin(PINO_RECEPTOR, ENABLE_LED_FEEDBACK);` em `Main/Receptor.h`.
Referência: https://www.arduino.cc/reference/en/language/structure/sketch/pinmode/

## 3.2 `PINO_EMISSOR`
É a constante que indica o pino digital usado pelo módulo emissor IR.
Aparece em: `#define PINO_EMISSOR 3` em `Main/Variaveis.h`.
Exemplo: `IrSender.begin(PINO_EMISSOR);` em `Main/Emissor.h`.
Referência: https://www.arduino.cc/reference/en/language/structure/sketch/pinmode/

## 3.3 `PINO_TRIG`
É o pino de disparo do sensor ultrassônico, usado para emitir o pulso sonoro.
Aparece em: `#define PINO_TRIG 4` em `Main/Variaveis.h`.
Exemplo: `digitalWrite(PINO_TRIG, HIGH);` em `Main/Sensor.h`.
Referência: https://docs.arduino.cc/learn/electronics/hc-sr04/

## 3.4 `PINO_ECHO`
É o pino de leitura do sensor ultrassônico, que recebe o eco do pulso emitido.
Aparece em: `#define PINO_ECHO 8` em `Main/Variaveis.h`.
Exemplo: `long duracao = pulseIn(PINO_ECHO, HIGH);` em `Main/Sensor.h`.
Referência: https://docs.arduino.cc/learn/electronics/hc-sr04/

## 3.5 `ultimoCodigo`
É a variável que guarda o último código IR recebido para diagnóstico ou reuso.
Aparece em: `IRData ultimoCodigo;` em `Main/Variaveis.h`.
Exemplo: `ultimoCodigo = IrReceiver.decodedIRData;` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 3.6 `temCodigo`
É a flag que indica se chegou um novo código infravermelho válido para processamento.
Aparece em: `bool temCodigo = false;` em `Main/Variaveis.h`.
Exemplo: `temCodigo = true;` em `Main/Receptor.h`.
Referência: https://www.arduino.cc/reference/en/language/variables/boolean/

## 3.7 `horarioUltimoEnvio`
É o tempo do último envio, usado para evitar disparos repetidos do sensor ultrassônico.
Aparece em: `unsigned long horarioUltimoEnvio = 0;` em `Main/Variaveis.h`.
Exemplo: `if (distancia > 5 && distancia <= 10 && (agora - horarioUltimoEnvio >= 10000))` em `Main/Sensor.h`.
Referência: https://www.arduino.cc/reference/en/language/functions/time/millis/

# 4. Main/Receptor.h

Já explicados antes: `IRremote.h (1.1)`, `Serial.begin (1.2)`, `iniciarReceptor (1.3)`, `lerReceptor (1.4)`.

## 4.1 `IrReceiver.begin`
É a função da biblioteca IRremote que inicializa o módulo receptor na porta escolhida e ativa a indicação visual de recepção.
Aparece em: `IrReceiver.begin(PINO_RECEPTOR, ENABLE_LED_FEEDBACK);` em `Main/Receptor.h`.
Exemplo: `IrReceiver.begin(PINO_RECEPTOR, ENABLE_LED_FEEDBACK);` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 4.2 `IrReceiver.decode`
É a função que verifica se chegou um sinal IR válido para ser processado pela biblioteca.
Aparece em: `if (IrReceiver.decode()) {` em `Main/Receptor.h`.
Exemplo: `if (IrReceiver.decodedIRData.protocol != UNKNOWN) {` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 4.3 `IrReceiver.resume`
É a chamada que libera o receptor para receber o próximo sinal após o processamento do código atual.
Aparece em: `IrReceiver.resume();` em `Main/Receptor.h`.
Exemplo: `IrReceiver.resume();` em `Main/Receptor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

# 5. Main/Emissor.h

Já explicados antes: `IRremote.h (1.1)`, `Comando (2.1)`, `botoes[] (2.2)`, `PINO_EMISSOR (3.2)`.

## 5.1 `IrSender.begin`
É a função que inicializa o pino do emissor infravermelho para que o Arduino possa enviar comandos.
Aparece em: `IrSender.begin(PINO_EMISSOR);` em `Main/Emissor.h`.
Exemplo: `IrSender.begin(PINO_EMISSOR);` em `Main/Emissor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

## 5.2 `strcmp`
É a função da biblioteca padrão C que compara duas strings em sequência, usada para localizar o nome do comando digitado pelo usuário.
Aparece em: `if (strcmp(botoes[posicao].nome, nomeDoBotao) == 0)` em `Main/Emissor.h`.
Exemplo: `strcmp(botoes[posicao].nome, nomeDoBotao)` em `Main/Emissor.h`.
Referência: https://en.cppreference.com/w/c/string/byte/strcmp

## 5.3 `IrSender.sendSony`
É a função que envia um código IR no protocolo SONY para a TV, com o número de repetições indicado.
Aparece em: `IrSender.sendSony(botoes[posicao].endereco, botoes[posicao].comando, 2);` em `Main/Emissor.h`.
Exemplo: `IrSender.sendSony(botoes[0].endereco, botoes[0].comando, 2);` em `Main/Sensor.h`.
Referência: https://github.com/Arduino-IRremote/Arduino-IRremote

# 6. Main/Sensor.h

Já explicados antes: `PINO_TRIG (3.3)`, `PINO_ECHO (3.4)`, `horarioUltimoEnvio (3.7)`, `IrSender.sendSony (5.3)`.

## 6.1 `pulseIn`
É a função da Arduino que mede quanto tempo o pino de entrada ficou em nível alto e permite calcular a distância do objeto.
Aparece em: `long duracao = pulseIn(PINO_ECHO, HIGH);` em `Main/Sensor.h`.
Exemplo: `float distancia = duracao * 0.0343 / 2;` em `Main/Sensor.h`.
Referência: https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/

## 6.2 `millis`
É a função que retorna o tempo em milissegundos desde a inicialização do Arduino, usada para controlar o intervalo entre os disparos do sensor.
Aparece em: `unsigned long agora = millis();` em `Main/Sensor.h`.
Exemplo: `if (distancia > 5 && distancia <= 10 && (agora - horarioUltimoEnvio >= 10000))` em `Main/Sensor.h`.
Referência: https://www.arduino.cc/reference/en/language/functions/time/millis/

## 6.3 `HC-SR04`
É o sensor ultrassônico usado para detectar uma mão e acionar o comando de ligar/desligar a TV.
Aparece em: `// Mantém o disparo ativo por 10 microssegundos (tempo exigido pelo sensor HC-SR04)` em `Main/Sensor.h`.
Exemplo: `float distancia = duracao * 0.0343 / 2;` em `Main/Sensor.h`.
Referência: https://docs.arduino.cc/learn/electronics/hc-sr04/

# 7. Main/Teste.h

Já explicados antes: `Comando (2.1)`, `SONY (2.3)`, `PINO_RECEPTOR (3.1)`, `PINO_EMISSOR (3.2)`, `PINO_TRIG (3.3)`, `PINO_ECHO (3.4)`, `temCodigo (3.6)`, `horarioUltimoEnvio (3.7)`.

## 7.1 `rodarTeste`
É a função que imprime no monitor serial se uma validação do sistema passou ou falhou.
Aparece em: `void rodarTeste(bool condicao, const char* nomeDoTeste)` em `Main/Teste.h`.
Exemplo: `Serial.print("[PASSOU] ");` em `Main/Teste.h`.
Referência: https://www.arduino.cc/reference/en/language/variables/data-types/bool/

## 7.2 `executarTodosOsTestes`
É a rotina principal de validação do projeto, que verifica número de comandos, protocolo, pinos e estado inicial do sistema.
Aparece em: `void executarTodosOsTestes()` em `Main/Teste.h`.
Exemplo: `rodarTeste(qtdBotoes == 7, "Existem exatamente 7 comandos configurados na memoria.");` em `Main/Teste.h`.
Referência: https://www.arduino.cc/reference/en/language/structure/sketch/function/

## 7.3 `sizeof`
É o operador que retorna o tamanho em bytes de um tipo ou de um array, usado para calcular o número de comandos no catálogo.
Aparece em: `int qtdBotoes = sizeof(botoes) / sizeof(Comando);` em `Main/Teste.h`.
Exemplo: `sizeof(botoes) / sizeof(Comando)` em `Main/Teste.h`.
Referência: https://en.cppreference.com/w/cpp/language/sizeof
