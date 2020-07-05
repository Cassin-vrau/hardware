#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA

RF24 radio(9, 10); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)

const byte address[6] = "00002"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openReadingPipe(0, address); //DEFINE O ENDEREÇO PARA RECEBIMENTO DE DADOS VINDOS DO TRANSMISSOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.startListening(); //DEFINE O MÓDULO COMO RECEPTOR (NÃO ENVIA DADOS)
}

void loop() {
      int peao[5]; //VARIÁVEL RESPONSÁVEL POR ARMAZENAR OS DADOS RECEBIDOS
  if (radio.available()) { //SE A COMUNICAÇÃO ESTIVER HABILITADA, FAZ
    radio.read(&peao, sizeof(peao)); //LÊ OS DADOS RECEBIDOS
        Serial.println(peao[0]);
        Serial.println(peao[1]);
        Serial.println("-------");
    if(peao[1] == 1){ // SEM máscara
      enviar_Raspberry();
      Serial.println("SEM MASCACA");
      Serial.println(peao[1]);
      Serial.println("-------");
    }
  
  } 
  delay(250);
} 


void enviar_Raspberry(){
  
}
