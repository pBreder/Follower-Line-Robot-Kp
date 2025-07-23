#include <PETEletrica.h>

// o sensor retorna algo proximo de 1000 ao ler a fita preta e 0 so ler o branco
// as variáveis que devem ser testadas são: kp e vel_ref
// para o calculo da posição usa-se a media ponderada dos motores com pesos 0, 1, 2, 3, 4. Exemplificando, se somente o sensor a da direita for lido será retornado 4000
/* para o calculo para deteção da tag é feito uma média simples das leituras. Como todos os sensores estão sobre a fita, entao temos (5*1000)/5 = 1000. No entanto, 
   há alguns fatores que podem levar essa leitura há outros números. Dessa forma, utilizamos como parâmetro 650, mas também é um valor que pode ser alterado*/

// Ultrassonico
int trig = 4;
int echo = 8; 
int distancia = 0; // distancia lida pelo ultrassonico
float mediaSensores; // media dos valores lidos pelo IR
SensorUltrassonico ultrassonico(trig, echo); // declaração do sensor ultrassonico

// Infravermelho
const unsigned char pin_sensor[] = {A0, A1, A2, A3, A4};
SensorInfravermelhoRC qtr(pin_sensor, 5, 2000, QTR_NO_EMITTER_PIN); // declaração do sensor IR
unsigned int sensores[5]; 

// Motores
Motores motor(5,6,9,10);

// Variaveis 
float kp = 0.0675; // constante de proporcionalidade, a qual será usada para o calculo do valor a se alterar na velocidade em cada roda (variavel u)
float ajuste = 0;
float erro; // compara a diferenca entre onde o carrinho deveria estar (posição correta) com a posição que ele de fato está
float vel_ref = 120; // velocidade que deve ser definida através de testes a fim de encontrar o melhor valor, é o valor de referência aos motores
int sensor_ref = 2000; // caso o carrinho esteja esteja na posição correta será o valor retornado da posição pelos IR's é 2000, como desejamos que ele esteja sempre na posição correta, esse é nosso parâmetro de posição
float a0, a1, a2, a3, a4;
bool alerta; // variavel que ajudará no caso da deteção de uma tag (ativa um modo de alerta ao obstaculo)

void setup() {
  Serial.begin(9600); // estabelece a comunicação
  // calibra o IR
  for(int i = 0; i < 100; i++){
      qtr.calibrate();
      delay(10);
  }
}

void loop() {
  // leitura dos sensores infravermelhos para calculo da media
  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);
  a4 = analogRead(A4);

  mediaSensores = ((a0 + a1 + a2 + a3 + a4)/5); // calculo da media para indetificação da tag

  unsigned int position = qtr.readLine(sensores); // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
  erro = sensor_ref - position;
  ajuste = kp * erro;
  motor.set_motors(vel_ref + ajuste, vel_ref - ajuste); // define a velocidade em cada motor

  if(mediaSensores > 650){ // se ler a tag
    alerta = true; // ativa o modo alerta
    while(alerta){ // enquanto estiver no modo alerta
      // comeca a busca pelo obstaculo
      long intervalo = ultrassonico.timing();
      distancia = ultrassonico.convert(intervalo, SensorUltrassonico::CM); // mede a distancia ate o objeto

      // continua andando, de forma que se aproxime suficientemente do obstaculo
      unsigned int position = qtr.readLine(sensores); // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
      erro = sensor_ref - position;
      ajuste = kp * erro;
      motor.set_motors(vel_ref + ajuste, vel_ref - ajuste); // define a velocidade em cada motor

      if(distancia <= 25){ // se aproximou o sufciente do obstaculo

        // faz a curva
        motor.set_motors(-120,30); // faz a curva indo para a esquerda
        delay(1000);
        motor.set_motors(30,-120); // alinha na curva
        delay(500);
        motor.set_motors(120,120); // reto
        delay(1000);
        motor.set_motors(30, -120); // desfazer a curva, indo para a direita
        delay(1000);
        motor.set_motors(-120, -30); // alinha no caminho
        delay(500);

        alerta = false; // desativa o modo alerta
      }
    }
  }
}