/********************************************************************\
 *        Arduino Shield Sterring Wheel - CODE ARDUINO UNO          *
 *                                                                  *
 * By: JosManoel                                                    *
 * E-mail: josmanoelfreitas2012@gmail.com                           *
 * GitHub: https://github.com/JosManoel                             *
\********************************************************************/

/*
==============================   NOTA:   =============================
  
         Este código foi testado apenas em ambiente simulado, 
            utilizando o software Proteus na versão 8.1.

  Este código foi desenvolvindo para ser utilizando em conjunto com 
    o CI 74HC165, um registrador de deslocamento com uma entrada 
               paralela de 8 bits e uma saída serial. 
  Este CI foi utilizado para aumentar o numero de portas do Arduino 
     Uno, possibilitando a construção de um cambio com 8 marchas.

  Acesse o repositório da biblioteca para obter mais informações:
  GitHub: https://github.com/AlanChatham/UnoJoy

======================================================================
*/

// Incluindo biblioteca UnoJoy
#include "UnoJoy.h"

/********************************************************************\
 *                        VARIAVEIS DE CONTROLE                     *
\********************************************************************/

#define pulse_val 5   // definindo tempo de deslocamento de load
byte OldValues;       // variavel de constrole de terminal

/********************************************************************\
 *                 DEFININDO CONEXÕES COM O ARDUINO                 *
\********************************************************************/

// LED de info
const int led = 13;      // LED de info 

// Definindo Pinos de conexões do 74HC165
const int ClockIn = 12;  // CP pin 2
const int DataIn = 11;   // Q7 pin 7
const int ClockEnb = 10; // CE pin 15
const int LoadIn = 9;    // PL pin 1

// Definindo Pinos de botoes 
const int PShiftP = 8;   // PShift +
const int PShiftM = 7;   // PShift -
const int Home = 6;      // Home PS3
const int Horn = A5;     // Buzina 
const int HBrake = A4;   // Freio de mão

// Dpad - Direcionais do joystick
const int DpadUp = 5;      
const int DpadDown = 4; 
const int DpadLeft = 3;
const int DpadRight = 2;

// Definindo Entradas analogicas
const int Accel = A0;    // Acelerador
const int Brake = A1;    // Freio
const int Clut = A2;     // Embreagem
const int Strg = A3;     // Volante

/********************************************************************\
 *                             FUNÇÕES                              *
\********************************************************************/

void setupPins(){
  // Setando pinos de conexões do CI 74HC165 
  pinMode(ClockEnb, OUTPUT);
  pinMode(DataIn, INPUT);
  pinMode(ClockIn, OUTPUT);
  pinMode(LoadIn, OUTPUT);

  // Setando pinos de conexões do botões
  pinMode(PShiftP, INPUT_PULLUP);
  pinMode(PShiftM, INPUT_PULLUP);
  pinMode(HBrake, INPUT_PULLUP);
  pinMode(Horn, INPUT_PULLUP);
  pinMode(Home, INPUT_PULLUP);

  // Setando pinos do Dpad
  pinMode(DpadUp, INPUT_PULLUP);
  pinMode(DpadDown, INPUT_PULLUP);
  pinMode(DpadLeft, INPUT_PULLUP);
  pinMode(DpadRight, INPUT_PULLUP);
}

void pulsePin(int pulse_clock){
  // Gera um pulso de clock no pino Load [CI 74HC165]
  digitalWrite(LoadIn, LOW);
  delayMicroseconds(pulse_clock);
  digitalWrite(LoadIn,HIGH);
  delayMicroseconds(pulse_clock);
}

byte getGear() {
  // Recuperando os dados do ci 74HC165 e realizando o shiftIn
  digitalWrite(ClockIn, HIGH);
  digitalWrite(ClockEnb, LOW);

  byte data = shiftIn(DataIn, ClockIn, MSBFIRST);

  digitalWrite(ClockIn, HIGH);
  // Retornando leitura dos 8 pinos do 74HC165 (1 byte)
  return(data);
}

void ledInfo(int rpt){
  // Aciona o LED de informações
  for (int l = 0; l < rpt ; l++){ 
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(250);                       
    digitalWrite(LED_BUILTIN, LOW);   
    delay(250);                       
  }
}

dataForController_t getControllerData(byte data_gear){

  /*
    Limpando dados do buffer com a função getBlankDataForController()
    presente na biblioteca UnoJoy.
  */
  dataForController_t controllerData = getBlankDataForController(); 

  // Setando entradas do cambio
  /*
     A leitura das entradas do cambio é realizada na função getGear(),
     que retorna um byte, onde cada bit simboliza uma marcha a partir 
     do primeiro bit. O bitRead realiza a leitura de determinado bit 
     no byte.
  */
  controllerData.triangleOn = bitRead(data_gear, 0); // 1° Marcha
  controllerData.circleOn = bitRead(data_gear, 1);   // 2° Marcha
  controllerData.squareOn = bitRead(data_gear, 2);   // 3° Marcha
  controllerData.crossOn = bitRead(data_gear, 3);    // 4° Marcha
  controllerData.l1On = bitRead(data_gear, 4);       // 5° Marcha
  controllerData.l2On = bitRead(data_gear, 5);       // 6° Marcha
  controllerData.l3On = bitRead(data_gear, 6);       // 7° Marcha
  controllerData.r1On = bitRead(data_gear, 7);       // Marcha Ré

  // Setando paddle shift e outros butões
  controllerData.r2On = !digitalRead(PShiftP);       // Paddle Shift +
  controllerData.r3On = !digitalRead(PShiftM);       // Paddle Shift -
  controllerData.selectOn = !digitalRead(Horn);      // Buzina
  controllerData.startOn = !digitalRead(HBrake);     // Freio de mão
  controllerData.homeOn = !digitalRead(Home);        // Home
  
  // Setando Dpad
  controllerData.dpadUpOn = !digitalRead(DpadUp);
  controllerData.dpadDownOn = !digitalRead(DpadDown);
  controllerData.dpadLeftOn = !digitalRead(DpadLeft);
  controllerData.dpadRightOn = !digitalRead(DpadRight);

  // Setando entradas analógicas 
  /* 
    Usar o analogRead para realizar a leitura de portas analogias
    retorna um dado de 10bits de resolução, sendo necessário 
    realizar o deslocamento de 2 bits para que ela possa ser 
    utilizada pela biblioteca UnoJoy.
  */
  controllerData.leftStickX = analogRead(Strg) >> 2;   // Volante
  controllerData.leftStickY = analogRead(Accel) >> 2;  // Acelerador
  controllerData.rightStickX = analogRead(Clut) >> 2;  // Embreagem
  controllerData.rightStickY = analogRead(Brake) >> 2; // Freio

}

void setup() {
  // Setando pinos
  setupPins();
  // Inicializando joystick
  setupUnoJoy();

  pinMode(LED_BUILTIN, OUTPUT);
  ledInfo(2);
}

void loop() {
  //aplicando um pulso de clock no load pin
  pulsePin(pulse_val);

  // Realizando a atualização da letura dos dados
  dataForController_t controllerData = getControllerData(getGear());
  setControllerData(controllerData);
}
