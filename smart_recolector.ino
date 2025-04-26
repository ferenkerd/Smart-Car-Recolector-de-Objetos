#include <ESP32Servo.h>

const int Trigger = 5;  // Pin digital 5 para el Trigger del sensor
const int Echo = 17;    // Pin digital 17 para el Echo del sensor

// Definición de pines
const int motorIzquierdoPWM = 23; //pwm
const int motorIzquierdo1 = 21;  // Pin de dirección 1 para el motor izquierdo
const int motorIzquierdo2 = 22;  // Pin de dirección 2 para el motor izquierdo

const int motorDerechoPWM = 15; //pwm
const int motorDerecho1 = 18;  // Pin de dirección 1 para el motor derecho
const int motorDerecho2 = 19;  // Pin de dirección 2 para el motor derecho

const int PWMFrecuencia = 1000; /* 1 KHz */
const int PWMResolucion = 8;
const int motorIzquierdoPWMCanal = 4;
const int motorDerechoPWMCanal = 5;

Servo miServoBase;       
Servo miServoArriba;     
Servo miServoPinza;      
int pinServoBase = 2;    
int pinServoArriba = 4;  
int pinServoPinza = 25;  

int pinPared = 14;


void setup() {
  Serial.begin(9600);

  pinMode(pinPared, INPUT_PULLUP);
  miServoBase.attach(pinServoBase);      // Conecta el servo Base
  miServoArriba.attach(pinServoArriba);  // Conecta el servo Arriba
  miServoPinza.attach(pinServoPinza);    // Conecta el servo Pinza

  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);

  pinMode(motorIzquierdoPWM, OUTPUT);
  pinMode(motorIzquierdo1, OUTPUT);
  pinMode(motorIzquierdo2, OUTPUT);
  pinMode(motorDerechoPWM, OUTPUT);
  pinMode(motorDerecho1, OUTPUT);
  pinMode(motorDerecho2, OUTPUT);

  ledcSetup(motorIzquierdoPWMCanal, PWMFrecuencia, PWMResolucion);
  ledcSetup(motorDerechoPWMCanal, PWMFrecuencia, PWMResolucion);
  ledcAttachPin(motorIzquierdoPWM, motorIzquierdoPWMCanal);
  ledcAttachPin(motorDerechoPWM, motorDerechoPWMCanal);

  ledcWrite(motorIzquierdoPWMCanal, abs(0));
  ledcWrite(motorDerechoPWMCanal, abs(0));

  brazoPosicionInicial();
}

void loop() {

  int distanciaObjeto = detectarObjeto();

  int pared = digitalRead(pinPared);
  Serial.println(pared);

  if (pared == 1) {
    Serial.println("Pared Encontrado");
    detener();
    delay(1000);
    atras();
    delay(3000);
    girar();
    delay(2000);
  } else if (distanciaObjeto <= 10) {
    Serial.println("Objeto Encontrado");
    Serial.println("Robot Detenido");
    detener();
    brazoAgarrarObjeto();
    brazoDepositarObjeto();
    brazoPosicionInicial();
    Serial.println("Objeto Agarrado");
  }else {
    brazoPosicionInicial();
    avanzar();
    Serial.println("Robot Avanzando");
  }
}

void atras() {
  ledcWrite(motorIzquierdoPWMCanal, abs(255));
  ledcWrite(motorDerechoPWMCanal, abs(255));
  digitalWrite(motorDerecho1, 0);
  digitalWrite(motorDerecho2, 1);
  digitalWrite(motorIzquierdo1, 0);
  digitalWrite(motorIzquierdo2, 1);
}

void detener() {
  ledcWrite(motorIzquierdoPWMCanal, abs(0));
  ledcWrite(motorDerechoPWMCanal, abs(0));
  digitalWrite(motorDerecho1, 0);
  digitalWrite(motorDerecho2, 0);
  digitalWrite(motorIzquierdo1, 0);
  digitalWrite(motorIzquierdo2, 0);
}

void avanzar() {
  ledcWrite(motorIzquierdoPWMCanal, abs(255));
  ledcWrite(motorDerechoPWMCanal, abs(255));
  digitalWrite(motorDerecho1, 1);
  digitalWrite(motorDerecho2, 0);
  digitalWrite(motorIzquierdo1, 1);
  digitalWrite(motorIzquierdo2, 0);
}

void avanzarDespacio() {
  ledcWrite(motorIzquierdoPWMCanal, abs(200));
  ledcWrite(motorDerechoPWMCanal, abs(200));
  digitalWrite(motorDerecho1, 1);
  digitalWrite(motorDerecho2, 0);
  digitalWrite(motorIzquierdo1, 1);
  digitalWrite(motorIzquierdo2, 0);
}

int detectarObjeto() {
  long tiempo;
  long distancia;

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  tiempo = pulseIn(Echo, HIGH);
  distancia = tiempo / 59;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(50);

  return distancia;
}

void brazoPosicionInicial() {
  miServoArriba.write(150);
  miServoBase.write(0);
  miServoPinza.write(180);
}

void brazoAgarrarObjeto() {
  miServoPinza.write(180);
  delay(2000);
  miServoArriba.write(105);
  delay(2000);
  miServoBase.write(135);
  delay(2000);
  miServoPinza.write(110);
  delay(2000);
}

void brazoDepositarObjeto() {
  miServoBase.write(0);
  delay(2000);
  miServoArriba.write(150);
  delay(2000);
  miServoPinza.write(180);
  delay(2000);
}

void girar() {
  ledcWrite(motorIzquierdoPWMCanal, abs(255));
  ledcWrite(motorDerechoPWMCanal, abs(255));
  digitalWrite(motorDerecho1, 0);
  digitalWrite(motorDerecho2, 0);
  digitalWrite(motorIzquierdo1, 1);
  digitalWrite(motorIzquierdo2, 0);
}
