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

// Definindo Pinos de conexões do 74HC165
int ClockEnb = 10; // CE pin 15
int DataIn = 11;   // Q7 pin 7 (verificar se pode ser o pin 9 )
int ClockIn = 12;  // CP pin 2
int LondIn = 13;   // PL pin 1

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
int OpAnalog = 5;
int OpButt1 = 2;
int OpButt2 = 3;
int OpButt3 = 4;
int OpButt4 = 5;
int OpButt5 = 6;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
