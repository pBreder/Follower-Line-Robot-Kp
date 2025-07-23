#include <PETEletrica.h>

int trig = 4; // pino trig do ultrassonico
int echo = 8; // pino echo do ultrassonico
int distancia = 0; // distancia lida pelo ultrassonico

SensorUltrassonico ultrassonico(trig, echo); // declaração do sensor ultrassonico

void setup() {
  Serial.begin(9600); // estabelece a comunicação
}

void loop() {
  long intervalo = ultrassonico.timing(); // mede o intervalo de tempo que a onda leva a sair do sensor ate retornar
  distancia = ultrassonico.convert(intervalo, SensorUltrassonico::CM); // mede a distancia ate o objeto por meio da velocdidade do som no ar e do intervalo de tempo medido
  Serial.println(distancia);
  delay(100);
}
