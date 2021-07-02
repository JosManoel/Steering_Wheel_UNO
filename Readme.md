## Steering Wheel UNO

Este shield foi desenvolvido para o Arduino UNO, baseado em uma publicação do [Laboratório de Garagem](https://labdegaragem.com/profiles/blogs/tutorial-joystick-shield-arduino-uno-unojoy) e tendo como base a biblioteca [UnoJoy](https://github.com/AlanChatham/UnoJoy).

[Baixar arquivos Gerber](https://raw.githubusercontent.com/JosManoel/Steering_Wheel_UNO/main/Gerber/Gerber_Steering_Wheel_UNO.zip?token=APFMFGACUZWO6Z7HV5QSJH3ANIWTU)

***
<p align = "center">
  <img src= "https://github.com/JosManoel/Steering_Wheel_UNO/blob/main/assets_page/images/PCB.png" alt = "Shield Sterring Wheel" width = "400"/>
</p>

### 📌 Resumo

Este shield foi desenvolvido para utilização em joysticks de simulação, utilizando o **CI 74HC165** (registrador de deslocamento com saída serial) destinado a aumentar o número de portas do Arduino UNO. O shield conta com 4 saídas analógicas, destinadas ao volante, acelerador, freio e embreagem, além de saídas digitais para os botões direcionais, home, freio de mão, buzina, paddle shift (cambio borboleta) e câmbio manual. O dispositivo foi criado tendo como base a biblioteca [UnoJoy](https://github.com/AlanChatham/UnoJoy), estando limitado aos inputs suportados por esta biblioteca. 

***

### 🛠 Hardware

<p align = "center">
  <img src= "https://github.com/JosManoel/Steering_Wheel_UNO/blob/main/assets_page/images/PCB_Bottom-Top.png" alt = "Shield Sterring Wheel Top and bottom" width = "800"/>
</p>

O shield tem **53mm x 69mm** de dimensões, com 4 layers, cobrindo todo o Arduino UNO. Em virtude disto, o dispositivo dispõe de um LED de 5mm ligado ao pino 13, onde serve de extensão do LED interno do Arduino, facilitando a visualização de sinais de aviso emitidos. O LED é um componente opcional. 

#### Componentes utilizados

* **8x** resistor 10k;
* **5x** conector KK Macho 3 vias;
* **2x** conector KK Macho 2 vias;
* **1x** conector KK Macho 6 vias;
* **1x** conector KK Macho 9 vias;
* **1x** Led;
* **1x** CI 74HC165;
* **3x** Potenciômetros 1k;
* **1X** Barra de pinos*

**A barra de pinos é necessária para realizar a conexão entre o shield e o Arduino*

***

### 🔌 Conexões  

<p align = "center">
  <img src= "https://github.com/JosManoel/Steering_Wheel_UNO/blob/main/assets_page/images/PCB_Top.png" alt = "Shield Sterring Wheel Top" width = "400"/>
</p>

* **STRG** – Entrada analógica do volante;
* **CLUT** – Entrada analógica da embreagem;
* **BRAKE** – Entrada analógica do freio;
* **ACCEL** – Entrada analógica do acelerador;
* **HBRAKE** – Entrada digital do freio de mão;
* **HORN** – Entrada digital da buzina;
* **STRG_BUTTONS** – Entradas digitais direcionais;
* **GEAR_PINS** – Entradas digitais câmbio manual;
* **PADDLE_SHIFT** – Entradas digitais cambio borboleta.

***

### 📝 Sketch 

O projeto conta com um sketch demonstrativo onde é documentada a utilização biblioteca UnoJoy para transformar o Arduino em um dispositivo USB. O código ainda conta com uma função para realizar a leitura de dados seriais recebidos do CI 74HC165.

#### Leitura de dados do CI 74HC165

O CI 74HC165, responsável pela leitura de dados do câmbio manual, é um registrador de deslocamento com 8 entradas digitais e 1 saída serial, onde a leitura dos dados é realizada de forma paralela. As entradas do 74HC165 precisam ser setadas para nível logico baixo, através de 8 resistores de pull-down de 10K, passando para nível lógico alto quando um botão é pressionado (para mais informações consulte os [diagramas](https://github.com/JosManoel/Steering_Wheel_UNO/tree/main/Schematic).

O CI 74HC165 está conectado ao Arduino Uno por 4 pinos, sendo eles:

|               | Arduino | 74HC165 |
|---------------|---------|---------|
| **Clock_in**  |  Pin 12 |  Pin 2  |
| **Data**      |  Pin 11 |  Pin 7  |
| **Clock_Enb** |  Pin 10 |  Pin 15 |
| **Load_In**   |   Pin 9 |  Pin 1  |

#### Código

Após declarar os pinos de entrada do CI no Arduino, é iniciado um pulso no pino Load, que irá carregar os dados retirados da entrada paralela em um buffer. Em um próximo passo, o CI é configurado para realizar a leitura utilizando a função shiftIn, configurado com o bitOrder em MSBFIRST (Bit mais significativo). Para finalizar, o pino ClockIn é setado para nível alto, informando que a leitura foi finalizada, retornando a leitura dos dados.

#### Código de pulso de clock
```
void pulsePin(int pulse_clock){
  // Gera um pulso de clock no pino Load [CI 74HC165]
  digitalWrite(LoadIn, LOW);
  delayMicroseconds(pulse_clock);
  digitalWrite(LoadIn,HIGH);
  delayMicroseconds(pulse_clock);
}
```
#### Código de leitura de dados
```
byte getGear() {
  // Recuperando os dados do CI 74HC165 e realizando o shiftIn
  digitalWrite(ClockIn, HIGH);
  digitalWrite(ClockEnb, LOW);

  byte data = shiftIn(DataIn, ClockIn, MSBFIRST);

  digitalWrite(ClockIn, HIGH);
  // Retornando leitura dos 8 pinos do 74HC165 (1 byte)
  return(data);
}
```

***

### 📚 Leitura recomendada 
* [Shift Registers – 74HC595 & 74HC165 with Arduino](https://dronebotworkshop.com/shift-registers/)
* [ShiftIn()](https://www.arduino.cc/reference/pt/language/functions/advanced-io/shiftin/)
* [UnoJoy utilize seu Arduino Uno como um Joystick](https://labdegaragem.com/profiles/blogs/tutorial-joystick-shield-arduino-uno-unojoy)
* [Biblioteca UnoJoy](https://github.com/AlanChatham/UnoJoy)

***

### 📝 Licença

Este projeto está sobe a licença [Apache](https://github.com/JosManoel/Steering_Wheel_UNO/blob/main/LICENSE).

