/******************************************************\
 * Arduino Shield Sterring Wheel - CODE ARDUINO UNO   *
 *                                                    *
 * By: JosManoel                                      *
 * E-mail: josmanoelfreitas2012@gmail.com             *
 * GitHub: https://github.com/JosManoel               *
\******************************************************/

////////////////////////////////////////////////////////
////                     CONEXOES                   ////
////////////////////////////////////////////////////////

#define pulse_val 5   // definindo tempo de deslocamento do clock e load

////////////////////////////////////////////////////////
////                     CONEXOES                   ////
////////////////////////////////////////////////////////

// Definindo Pinos de conexões do 74HC165
int ClockEnb = 10; // CE pin 15
int DataIn = 11;   // Q7 pin 7 (verificar se pode ser o pin 9 )
int ClockIn = 12;  // CP pin 2
int LoadIn = 13;   // PL pin 1

// Definindo Pinos de botoes 
int PShiftP = 9;   // PShift plus  (cambio borboleta)
int PShiftM = 8;   // PShift minus (cambio borboleta)
int Horn = 7;      // Horn Button  (buzina)

// Definindo Entradas analogicas
int Accel = 0;     // Acelerador
int Break = 1;     // Freio
int Clut = 2;      // Embreagem
int HBreak = 3;    // Freio de mão
int Strg = 4;      // Volante

// Botoes opcionais
/*
int OpAnalog = 5;  // Saída analogica opcional
int OpButt1 = 2;   // Button opcional 1
int OpButt2 = 3;   // Button opcional 2
int OpButt3 = 4;   // Button opcional 3
int OpButt4 = 5;   // Button opcional 4
int OpButt5 = 6;   // Button opcional 5
*/

//Pulso de clock no pino Load 
void pulse_pin(int pulse_clock){

  digitalWrite(LoadIn, LOW);
  delayMicroseconds(pulse_clock);
  digitalWrite(LoadIn,HIGH);
  delayMicroseconds(pulse_clock);
}

//Pegando valores e realizando o shiftIn
byte get_data() {
  digitalWrite(ClockIn, HIGH);
  digitalWrite(ClockEnb, LOW);

  byte data = shiftIn(DataIn, ClockIn, LSBFIRST);

  digitalWrite(ClockIn, HIGH);

  return(data);
}

//Printando informações no terminal
void print_data(byte data_info){

  Serial.print("Estado dos pinos do 74hc165 \n");
  Serial.println(data_info, BIN);

}

void setup() {
  
  // iniciando a comunicação por terminal
  Serial.begin(9600); 

  //Setando os pinos do arduino

    //Setup 74HC165 connections
  pinMode(ClockEnb, OUTPUT);
  pinMode(DataIn, INPUT);
  pinMode(ClockIn, OUTPUT);
  pinMode(LoadIn, OUTPUT);

    //Setando pinos de botoes do volante
  pinMode(PShiftP, INPUT_PULLUP);
  pinMode(PShiftM, INPUT_PULLUP);
  pinMode(Horn, INPUT_PULLUP);

}


void loop() {
  //aplicando um pulso de clock no load pin
  pulse_pin(pulse_val);
  print_data(get_data());
}
