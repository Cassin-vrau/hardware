#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA

RF24 radio(9, 10); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)
////////////////////////////variáveis////////////////////////////
int matricula = 129; // matricula para identificar a pessoa
byte mascara = 0; // variavel da máscara
byte distancia = 0; // variavel da distancia
int amigo = 0; // variavel para salvar a matricula da pessoa que estiver em ranger inferior a 1,5 

int botao = 10; // pino do botão do descanso de orelha
int led = 9; // pino sinalizando que ta ligado 
const byte address[6] = "00002"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)
////////////////////////////////////////////////////////////////

void setup() {
  pinMode(led, OUTPUT);
  pinMode(botao, INPUT);
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openWritingPipe(address); //DEFINE O ENDEREÇO PARA ENVIO DE DADOS AO RECEPTOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.stopListening(); //DEFINE O MÓDULO COMO TRANSMISSOR (NÃO RECEBE DADOS)

}

void loop() {
  int peao[5] = {matricula, mascara, distancia, amigo}; //VARIÁVEL RECEBE A MENSAGEM A SER TRANSMITIDA
 int estado = digitalRead(botao); // ta salvando o estado do botão
  if(estado == HIGH){ // quando a máscara for retirara, irá mandar um sinal de 1(HIGH)
    peao[1] = 1; // salvando a posição [1] da máscara com o valor de 1
    radio.write(&peao, sizeof(peao)); //ENVIA AO RECEPTOR A MENSAGEM
    peao[1] = 0; // zerando a posição da máscara
  } 
  
  radio.write(&peao, sizeof(peao)); //ENVIA AO RECEPTOR A MENSAGEM
  
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
