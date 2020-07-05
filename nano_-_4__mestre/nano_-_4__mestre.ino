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
  if (radio.available()) { //SE A COMUNICAÇÃO ESTIVER HABILITADA, FAZ
    int peao[5]; //VARIÁVEL RESPONSÁVEL POR ARMAZENAR OS DADOS RECEBIDOS
    int nome;
    radio.read(&peao, sizeof(peao)); //LÊ OS DADOS RECEBIDOS
    
    if(peao[1] == 1){ // a posição [1] somente será 1, quando o trabalhador retirar a máscara
      nome = peao[0]; // ta salvando a matricula da pessoa(nome)
     Serial.print("A matricula é: ");
      Serial.println(nome);
       Serial.println("tirou a mascara");
      enviar(); // entra na fnução para enviar para a página web
      delay(25);
      peao[0] = 0;
    }


    
  } else Serial.println("erro");
}

void enviar(){
  
}
