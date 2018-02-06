//bibliotecas utilizadas para o controlo carro
#include <Ultrasonic.h> //biblioteca do sensor de ultra sons
#include <Servo.h> //biblioteca do servo motor
#include <AFMotor.h> //biblioteca dos motores do carro

//definir o pino A0 como sendo o que vai ler a tensão de entrada no arduino
#define inputVoltage A0

//indicação das variaveis dos motores
AF_DCMotor backEsquerda(1);
AF_DCMotor backDireita(2);
AF_DCMotor frontEsquerda(4);
AF_DCMotor frontDireita(3);

//indicação do servo
Servo  myservo;
//indicação do sensor de ultrasons
Ultrasonic myusonic(19,18);

long duty = 0;
int x = 0;
long d1 = 0;
long d2 = 0;
int distanciaFrente = 21;
int distanciaEsquerda = 0;
int distanciaDireita = 0;
// variaveis de movimento

const int delay_arranque = 250;
const int delay_visao = 350;
const int verEsquerda = 0;
const int verDireita = 170;
const int verFrente = 80;
const int chegatras = 200;
const int distanciadet = 44;
void setup() {
  myservo.attach(10); //o servo está ligado ao pino 10
  //velocidade();
  Serial.begin(115200);
  myservo.write(verFrente); //ver obstáculos em frente
}

void loop() {
  distancia();
  //Serial.print(distanciaFrente);
  if(distanciaFrente < distanciadet){mudarDirecao();}
  else{
    andarFrente();
    myservo.write(verFrente); //ver obstáculos em frente
    }
  velocidade();
}

void distancia(){
  distanciaFrente = myusonic.distanceRead(CM);
}

void velocidade(){ 
  x = analogRead(inputVoltage);
  d1=(x-1024)>>3;
  d2=((x-1024)*(x-1024))>>9;
  duty=128-d1+d2;
  backEsquerda.setSpeed(duty);
  backDireita.setSpeed(duty);
  frontEsquerda.setSpeed(duty);
  frontDireita.setSpeed(duty); 
}

void andarFrente(){ //andar para a frente
  backEsquerda.run(FORWARD);
  backDireita.run(FORWARD);
  frontEsquerda.run(FORWARD);
  frontDireita.run(FORWARD);
}

void andarTras(){ //andar para tras
  backEsquerda.run(BACKWARD);
  backDireita.run(BACKWARD);
  frontEsquerda.run(BACKWARD);
  frontDireita.run(BACKWARD);  
}

void rodarEsquerda(){ //rodar o carro para a esquerda
  backEsquerda.run(BACKWARD);
  backDireita.run(FORWARD);
  frontEsquerda.run(BACKWARD);
  frontDireita.run(FORWARD);  
}

void rodarDireita(){ //rodar o carro para a direita
  backEsquerda.run(FORWARD);
  backDireita.run(BACKWARD);
  frontEsquerda.run(FORWARD);
  frontDireita.run(BACKWARD);    
}

void parar(){ //parar o carro
  backEsquerda.run(RELEASE);
  backDireita.run(RELEASE);
  frontEsquerda.run(RELEASE);
  frontDireita.run(RELEASE);   
}

void mudarDirecao(){
  parar();
  myservo.write(verDireita); //ver obstáculos a direita
  delay(delay_arranque);
  distanciaDireita = myusonic.distanceRead(CM); //ler a distancia
  if(distanciaDireita > distanciadet){
    andarTras();
    delay(chegatras);
    rodarDireita();
    delay(delay_visao);
    myservo.write(verFrente); //ver obstaculos em frente
    andarFrente();
    return;
  }
  myservo.write(verEsquerda); //ver obstáculos a esquerda
  delay(delay_arranque);
  distanciaEsquerda = myusonic.distanceRead(CM);
  if(distanciaEsquerda > distanciadet){
    andarTras();
    delay(chegatras);
    rodarEsquerda();
    delay(delay_visao);
    myservo.write(verFrente); //ver obstaculos em frente
    andarFrente();
    return;
  }
  myservo.write(verFrente); //ver obstáculos em frente
  delay(delay_arranque);
  distanciaFrente = myusonic.distanceRead(CM);
  if(distanciaFrente < distanciadet){
    andarTras();
    delay(chegatras);
    rodarEsquerda();
    delay(delay_visao * 1);
    myservo.write(verFrente); //ver obstaculos em frente
    andarFrente();
    return;
  }
} 



