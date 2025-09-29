#include <PETEletrica.h>

// Infravermelho
const unsigned char pin_sensor[] = {A0, A1, A2, A3, A4};
SensorInfravermelhoRC qtr(pin_sensor, 5, 2000, QTR_NO_EMITTER_PIN); // declaração do sensor IR
unsigned int sensores[5]; 

// Motores
Motores motor(10,11,6,5);

// Variaveis
float kp = 0.051; // constante de proporcionalidade, a qual será usada para o calculo do valor a se alterar na velocidade em cada roda (variavel u)
float ajuste = 0; // atua como um "delta" a se adicionar ou subtrair da velocidade de referencia
float erro = 0; // compara a diferenca entre onde o carrinho deveria estar (posição correta) com a posição que ele de fato está
int vel_ref = 153; // velocidade que deve ser definida através de testes a fim de encontrar o melhor valor, é o valor de referência aos motores
int sensor_ref = 2000; // caso o carrinho esteja esteja na posição correta será o valor retornado da posição pelos IR's é 2000, como desejamos que ele esteja sempre na posição correta, esse é nosso parâmetro de posição

void setup() {
  Serial.begin(9600); // estabelece a comunicação
  // calibra o IR
  for(int i = 0; i < 200; i++){ 
      qtr.calibrate();
      delay(10);
  }
}

void loop() {
  unsigned int position = qtr.readLine(sensores); // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
  Serial.println(position); // printa posição do carrinho em relação a fita
  erro = sensor_ref - position; // calculo do erro
  ajuste = kp * erro; // calculo do ajuste

  // (x, y) => x motor direito, y motor esquerdo
  // x vai para frente com + e para tras com -
  // y vai para frente com - e para tras com + 

  motor.set_motors(vel_ref - ajuste, -vel_ref - ajuste); // define a velocidade em cada motor

}