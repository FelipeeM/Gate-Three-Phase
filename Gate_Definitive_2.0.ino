#define LED_BUILTIN 13
//Reles para ativar os motores
int pnReleGateOpen = 3;
int pnReleGateClose = 4;
//Sensor de presenca
int pnInfra = 5;
//Fim de curso
int pnEndLineOpen = 7;
int pnEndLineClose = 6;
//Botoes
int pnButtonOpen = 8;
int pnButtonClose = 9;
//Rele do controle
int pnReleControl = 2;

int lastEndLineClose = 0;
int lastEndLineOpen = 0;

unsigned long atualTime;
void infra() {
  while (digitalRead(pnInfra) == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    Serial.println("---INFRA---");
  }
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  for (int key = 0; key < 5; key++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  };

  pinMode(pnReleControl, OUTPUT);
  digitalWrite(pnReleControl, HIGH);

  pinMode(pnInfra, OUTPUT);

  pinMode(pnEndLineOpen, OUTPUT);
  pinMode(pnEndLineClose, OUTPUT);


  pinMode(pnButtonOpen, OUTPUT);
  digitalWrite(pnButtonOpen, HIGH);

  pinMode(pnButtonClose, OUTPUT);
  digitalWrite(pnButtonClose, HIGH);

  pinMode(pnReleGateOpen, OUTPUT);
  digitalWrite(pnReleGateOpen, HIGH);
  pinMode(pnReleGateClose, OUTPUT);
  digitalWrite(pnReleGateClose, HIGH);

  Serial.begin(9600);

  lastEndLineOpen = digitalRead(pnEndLineOpen);
  lastEndLineClose = digitalRead(pnEndLineClose);
  infra();
  close();
}

void loop() {

  infra();
  if (digitalRead(pnReleControl) == 0) {
    controle();
  }
}


void open() {
  digitalWrite(LED_BUILTIN, HIGH);
  atualTime = millis();
  
  lastEndLineOpen = digitalRead(pnEndLineOpen);
  while (lastEndLineOpen == 0 & digitalRead(pnInfra) == 1) {
    lastEndLineOpen = digitalRead(pnEndLineOpen);
    digitalWrite(pnReleGateOpen, LOW);
    if (digitalRead(pnReleControl) == 0 & (millis() - atualTime) > 2500) break;
  }
  lastEndLineOpen = 1;
  lastEndLineClose = 0;
  
  Serial.println("Aberto");
  digitalWrite(pnReleGateOpen, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}

void close() {
  digitalWrite(LED_BUILTIN, HIGH);
  atualTime = millis();
  
  lastEndLineClose = digitalRead(pnEndLineClose);
  while (lastEndLineClose == 0 & digitalRead(pnInfra) == 1) {
    lastEndLineClose = digitalRead(pnEndLineClose);
    digitalWrite(pnReleGateClose, LOW);
    if (digitalRead(pnReleControl) == 0 & (millis() - atualTime) > 2500) break;
  }
  
  lastEndLineClose = 1;
  lastEndLineOpen = 0;

  digitalWrite(pnReleGateClose, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}

void controle() {
  if (lastEndLineOpen == 0 && lastEndLineClose == 1) {
    open();
  } else if (lastEndLineClose == 0 && lastEndLineOpen == 1) {
    close();
  } else if (lastEndLineClose == 1 && lastEndLineOpen == 1) {
    lastEndLineClose = digitalRead(pnEndLineClose);
    lastEndLineOpen = digitalRead(pnEndLineOpen);
  }
}
