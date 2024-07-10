const int sem = 4;
const int pinEcho = 2;
const int pinTrigger = 3;
const int btnVerde = 9;
const int btnRojo = 10;

int contadorObjetivo;
int contador = 0;
int variabilidadNumeroAleatorio = 7;

bool semaforoRojo = false;
bool btnVerdePulsado = false;
bool vehiculoDetectado = false;

void setup(){
  pinMode(sem, OUTPUT);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(btnVerde, INPUT_PULLUP);
  pinMode(btnRojo, INPUT_PULLUP);
  semVerde();
  contadorObjetivo = obtenerAleatorio();
}

void loop(){
  mando();
  vehiculoDetectado = ping();
  if(vehiculoDetectado && !semaforoRojo){
    contador++;
    if(contador >= contadorObjetivo){
      contador = 0;
      contadorObjetivo = obtenerAleatorio();
      semRojo();
    }
    while(ping()){
      delay(200);
      mando();
    }
  }
  delay(200);
}

void mando(){
  if (digitalRead(btnVerde) == LOW){
    btnVerdePulsado = true;
    semVerde();
  }
  
  if (digitalRead(btnRojo) == LOW){
    semRojo();
    semaforoRojo = true;
    delay(10);
  }
}

void semVerde(){
  digitalWrite(sem, LOW);
  semaforoRojo = false;
}

void semRojo(){
  digitalWrite(sem, HIGH);
  semaforoRojo = true;
}

bool ping(){
  long duration, distanceCm;

  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(4);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  duration = pulseIn(pinEcho, HIGH);

  distanceCm = duration * 10 / 292 / 2;
  if(distanceCm < 10){
    return true;
  } else{
    return false;
  }
}

int obtenerAleatorio(){
  if(random(1, variabilidadNumeroAleatorio) <= 2){
    return random(1, variabilidadNumeroAleatorio);
  } else{
    return random(variabilidadNumeroAleatorio - 5, variabilidadNumeroAleatorio + 5);
  }
}