#define ENA 6 //Motor direita
#define ENB 5 //Motor esquerda

#define IN1 13 //Motor direita frente
#define IN2 12 //Motor direita trás
#define IN3 4  //Motor esquerda frente
#define IN4 3  //Motor esquerda trás

#define trig1 10 //TRIG do sensor do meio
#define echo1 11 //ECHO do sensor do meio
#define trig2 1	 //TRIG do sensor do direita
#define echo2 2	 //ECHO do sensor do direita
#define trig3 9	 //TRIG do sensor do esquerda
#define echo3 8  //ECHO do sensor do esquerda

#define saida1 0 //saida 5v do 1o sensor
#define saida2 7 //saida 5v do 2o sensor

//Ultrassônico
float temp;

float distM = 0;

float distD = 0;

float distE = 0;

void setup()
{
  pinMode(trig1, OUTPUT); 
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  
  pinMode(saida1, OUTPUT);
  pinMode(saida2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  Serial.begin(9600);
}

void loop()
{

	digitalWrite(saida1, HIGH);
	digitalWrite(saida2, HIGH);

  distM = distancia(trig1, echo1);
  Serial.print("distancia (cm) do sensor 1: ");
  Serial.println(distM); 
  distD = distancia(trig2, echo2);
  Serial.print("distancia (cm) do sensor 2: ");
  Serial.println(distD);
  distE = distancia(trig3, echo3);
  Serial.print("distancia (cm) do sensor 3: ");
  Serial.println(distE);
  delay(3000);
  
  if (distD <= 15 && distD > 5) {  // Parede na direita
    Esquerda();
    delay(1000);
  }

  if (distD <= 5){                    // Parede na direita muito perto
    Esquerdafechada();
    delay(1000);
  }

  if (distE <= 15 && distE > 5) { // Parede na esquerda
    Direita();
    delay(1000);
  }

  if (distE <= 5){                    // Parede na esquerda muito perto
    Direitafechada();
    delay(1000);
  }

  if (distM >=15 && distD > 15 && distE > 15){  // Sem parede
    Frente();
  }

  
  if (distM <15 && distM >=5){          // Parede na frente
    Parar();
    delay(500);
      if (distD < distE){
        Esquerdafechada();
        delay(1000);
      }
      if (distE < distD){
        Direitafechada();
        delay(1000);
      }
  }

  if (distM <5){                     // Parede na frente muito perto
    Parar();
    delay(500);
    Re();
    delay(1000);
      if (distD < distE){
        Esquerdafechada();
        delay(1000);
      }
      if (distE < distD){
        Direitafechada();
        delay(1000);
      }
  
  }
}

float distancia(int TRIG, int ECHO) {
  digitalWrite(TRIG, HIGH);
  delay(0.01);
  digitalWrite(TRIG, LOW);
  float temp = pulseIn(ECHO, HIGH);
  float dist = 343*temp*0.000001/2*100;
  
  return dist;
}

//Funções de movimento
void Frente () {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Parar () {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Re () {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Direita () {
  analogWrite(ENA, 100);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Esquerda () {
  analogWrite(ENA, 150);
  analogWrite(ENB, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Direitafechada() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Esquerdafechada() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
