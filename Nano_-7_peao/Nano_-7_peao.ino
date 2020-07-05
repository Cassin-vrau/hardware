#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA

RF24 radio(9, 10); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)
////////////////////////////variáveis////////////////////////////
int matricula = 129; // matricula para identificar a pessoa
byte mascara = 0; // variavel da máscara
byte distancia = 0; // variavel da distancia
int amigo = 0; // variavel para salvar a matricula da pessoa que estiver em ranger inferior a 1,5 

int botao = 3; // pino do botão do descanso de orelha
int led = 2; // pino sinalizando que ta ligado 
const byte address[6] = "00002"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)
////////////////////////////////////////////////////////////////

void setup() {
  pinMode(led, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  Serial.begin(9600);
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openWritingPipe(address); //DEFINE O ENDEREÇO PARA ENVIO DE DADOS AO RECEPTOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.stopListening(); //DEFINE O MÓDULO COMO TRANSMISSOR (NÃO RECEBE DADOS)

}

void loop() {
int peao[5] = {matricula, mascara, distancia, amigo}; //VARIÁVEL RECEBE A MENSAGEM A SER TRANSMITIDA
int estado = digitalRead(botao);// LER B1
Serial.println("1-");
 Serial.println(peao[1]);
   radio.write(&peao, sizeof(peao)); //ENVIA AO RECEPTOR A MENSAGEM

  if(estado == HIGH){ // sem máscara - peao recebe 1 e manda 0
    peao[1] = 1;// dá um valor a posição peao[1]
   
 Serial.println("2-");
 Serial.println(peao[1]);

   radio.write(&peao, sizeof(peao)); //ENVIA AO RECEPTOR A MENSAGEM
    peao[1] = 0; // zera a posição peao[1]
     for(int x = 0; x<4; x++){ // faz o efeito do led piscar
      digitalWrite(led, 1);
      delay(50);
      digitalWrite(led, 0);
      delay(50);
    }
  }
  else if(estado == LOW){ // Com máscara - peao manda 0
   peao[1] = 0; // zera a posição peao[1]
  radio.write(&peao, sizeof(peao)); //ENVIA AO RECEPTOR A MENSAGEM
Serial.println("3-");
 Serial.println(peao[1]);

  }
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
