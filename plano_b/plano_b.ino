#include <PETEletrica.h>

// o sensor retorna algo proximo de 1000 ao ler a fita preta e 0 so ler o branco
// as variáveis que devem ser testadas são: kp, vel_ref, media da tag e os delays
// para o calculo da posição usa-se a media ponderada dos motores com pesos 0, 1, 2, 3, 4. Exemplificando, se somente o sensor a da direita for lido será retornado 4000
/* para o calculo para deteção da tag é feito uma média simples das leituras. Como todos os sensores estão sobre a fita, entao temos (5*1000)/5 = 1000. No entanto, 
   há alguns fatores que podem levar essa leitura há outros números. Dessa forma, utilizamos como parâmetro 650, mas também é um valor que pode ser alterado*/

// Ultrassonico
int trig = 4;
int echo = 8;
int distancia = 0;                            // distancia lida pelo ultrassonico
float mediaSensores;                          // media dos valores lidos pelo IR
SensorUltrassonico ultrassonico(trig, echo);  // declaração do sensor ultrassonico

// Infravermelho
const unsigned char pin_sensor[] = { A0, A1, A2, A3, A4 };
SensorInfravermelhoRC qtr(pin_sensor, 5, 2000, QTR_NO_EMITTER_PIN);  // declaração do sensor IR
unsigned int sensores[5];

// Motores
Motores motor(10, 11, 6, 5);
String lado = "esq"; // MUDAR AQUI PARA 'dir' CASO A CURVA DEVA SER FEITA PARA A DIREITA

// Variaveis
float kp = 0.051;  // constante de proporcionalidade, a qual será usada para o calculo do valor a se alterar na velocidade em cada roda (variavel u)
float ajuste = 0;
float erro = 0;               // compara a diferenca entre onde o carrinho deveria estar (posição correta) com a posição que ele de fato está
float vel_ref = 153;      // velocidade que deve ser definida através de testes a fim de encontrar o melhor valor, é o valor de r+++++++++++++++eferência aos motores
float sensor_ref = 2000;  // caso o carrinho esteja esteja na posição correta será o valor retornado da posição pelos IR's é 2000, como desejamos que ele esteja sempre na posição correta, esse é nosso parâmetro de posição
float a0, a1, a2, a3, a4;
bool alerta = false;  // variavel que ajudará no caso da deteção de uma tag (ativa um modo de alerta ao obstaculo)

void setup() {
  Serial.begin(9600);  // estabelece a comunicação
  // calibra o IR
  for (int i = 0; i < 200; i++) {
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

  mediaSensores = ((a0 + a1 + a2 + a3 + a4) / 5);  // calculo da media para indetificação da tag

  unsigned int position = qtr.readLine(sensores);  // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
  erro = sensor_ref - position;
  ajuste = kp * erro;
  motor.set_motors(vel_ref - ajuste, -vel_ref - ajuste);  // define a velocidade em cada motor

  if (mediaSensores > 350) {  // se ler a tag
    alerta = true;            // ativa o modo alerta
    while (alerta) {          // enquanto estiver no modo alerta
      // comeca a busca pelo obstaculo
      long intervalo = ultrassonico.timing();
      distancia = ultrassonico.convert(intervalo, SensorUltrassonico::CM);  // mede a distancia ate o objeto

      // continua andando, de forma que se aproxime suficientemente do obstaculo
      unsigned int position = qtr.readLine(sensores);  // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
      erro = sensor_ref - position;
      ajuste = kp * erro;
      motor.set_motors(vel_ref - ajuste, -vel_ref - ajuste);  // define a velocidade em cada motor

      if (distancia <= 27) {  // se aproximou o sufciente do obstaculo

        // (x, y) => x motor direito, y motor esquerdo
        // x vai para frente com + e para tras com -
        // y vai para frente com - e para tras com +  

        if (lado == "esq") { // iniciando a curva para esquerda
          motor.set_motors(100, 100); // embica para esquerda
          delay(550);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(200, -200);  // vai reto
          delay(750);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(-100, -130);  // alinha na curva virando para direita
          delay(400);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(200, -200);  // vai reto
          delay(600);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(-100, -100);  // embica para direita
          delay(500);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(100, -100);  // vai reto
          delay(800);
        }
        else if (lado == "dir") { // iniciando a curva para direita
          motor.set_motors(-100, -100); // embica para direita
          delay(500);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(200, -200);  // vai reto
          delay(400);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(100, 100);  // alinha na curva virando para esquerda
          delay(400);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(200, -200);  // vai reto
          delay(400);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(100, 100);  // embica para esquerda
          delay(500);
          motor.set_motors(0,0);
          delay(80);

          motor.set_motors(100, -100);  // vai reto
          delay(500);
        } 

        alerta = false;  // desativa o modo alerta
      }
    }
  }
}