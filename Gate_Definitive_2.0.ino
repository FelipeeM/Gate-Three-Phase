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
//Variavel que guarda o tempo para acionamento do controle dentro do void "open" "close"
unsigned long myTime;
unsigned long atualTime;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  for (int key = 0; key < 4; key++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
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
  close();
}

void loop() {

  while (digitalRead(pnInfra) == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  if (digitalRead(pnReleControl) == 0) {
    controle();
    //botao de abrir
    if (digitalRead(pnButtonOpen) == 0) {
      open();
      //botao de fechar
    } else if (digitalRead(pnButtonClose) == 0) {
      close();
    }
  }


  void open() {
    digitalWrite(LED_BUILTIN, HIGH);
    atualTime = millis();
    while (lastEndLineOpen == 0 & digitalRead(pnInfra) == 1) {
      myTime = millis();
      //Ativando rele
      digitalWrite(pnReleGateOpen, LOW);

      if (digitalRead(pnReleControl) == 0 & (myTime - atualTime) > 2000) {

        //Atualizando sensor para o loop
        lastEndLineOpen = 1;
        //Atualizando posicao do outro sensor
        lastEndLineClose = digitalRead(pnEndLineClose);
        break;
      }

      //Atualizando sensor para o loop
      lastEndLineOpen = digitalRead(pnEndLineOpen);
      //Atualizando posicao do outro sensor
      lastEndLineClose = digitalRead(pnEndLineClose);
    }

    if (digitalRead(pnInfra) == 0) {
      //Atualizando sensor para o loop
      lastEndLineOpen = 1;
      //Atualizando posicao do outro sensor
      lastEndLineClose = digitalRead(pnEndLineClose);
    }
    //Desativando rele
    digitalWrite(pnReleGateOpen, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
  }

  void close() {
    digitalWrite(LED_BUILTIN, HIGH);
    atualTime = millis();
    while (lastEndLineClose == 0 & digitalRead(pnInfra) == 1) {
      myTime = millis();
      //Ativando rele
      digitalWrite(pnReleGateClose, LOW);

      if (digitalRead(pnReleControl) == 0 & (myTime - atualTime) > 2000) {

        //Atualizando sensor para o loop
        lastEndLineClose = 1;
        //Atualizando posicao do outro sensor
        lastEndLineOpen = digitalRead(pnEndLineOpen);

        break;
      }

      //Atualizando sensor para o loop
      lastEndLineClose = digitalRead(pnEndLineClose);
      //Atualizando posicao do outro sensor
      lastEndLineOpen = digitalRead(pnEndLineOpen);
    }

    if (digitalRead(pnInfra) == 0) {
      lastEndLineClose = 1;
      lastEndLineOpen = digitalRead(pnEndLineOpen);
    }
    //Desativando rele
    digitalWrite(pnReleGateClose, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
  }

  void controle() {

    if (lastEndLineOpen == 0) {
      open();
    } else if (lastEndLineClose == 0) {
      close();
    }
  }
