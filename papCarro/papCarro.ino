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

void setup() {
  myservo.attach(10); //o servo está ligado ao pino 10
  //velocidade();
  Serial.begin(115200);
}

void loop() {
  distancia();
  //Serial.print(distanciaFrente);
  if(distanciaFrente < 40){mudarDirecao();}
  else{
    andarFrente();
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
  
  myservo.write(170);
  delay(500);
  distanciaDireita = myusonic.distanceRead(CM);
  if(distanciaDireita < 40){
    rodarDireita();
    delay(250);
    andarFrente();
    return;
  }
  myservo.write(0);
  delay(500);
  distanciaEsquerda = myusonic.distanceRead(CM);
  if(distanciaEsquerda < 40){
    rodarEsquerda();
    delay(250);
    andarFrente();
    return;
  }
  myservo.write(80);
  delay(500);
  distanciaFrente = myusonic.distanceRead(CM);
  if(distanciaFrente < 40){
    rodarEsquerda();
    delay(750);
    andarFrente();
    return;
  }
}
