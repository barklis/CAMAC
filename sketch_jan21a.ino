/*
 * Aby uruchomić ten program musisz pobrać biblioteke do sterownika silnika. Masz ją pod adresem:
 * https://github.com/xxxooo/StepperDriver
 * Wypadkowujesz pliki do folderu Arduino\libraries i uruchamiasz ponownie IDE.
 */

#include <StepperDriver.h> 

char command[5];
char value_char[7];
int value;
char inChar;
int pos_x;
int pos_y;

// Test pin
const int led_nieb=7;
const int led_czerw=6;
const int led_zolty=5;

// Konifuracja
int motor_steps = 200;
int step_divisition = 32;
int en_pin = 8;
int cw_pinX = 6;
int clk_pinX = 3;
int cw_pinY = 5;
int clk_pinY = 2;

// Inicjalizacja silników
StepperDriver stepperX(motor_steps, step_divisition, en_pin, cw_pinX, clk_pinX);  
StepperDriver stepperY(motor_steps, step_divisition, en_pin, cw_pinY, clk_pinY); 

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pos_x=0;
  pos_y=0;

  //testy:
  /*
  pinMode(led_nieb, OUTPUT);
  pinMode(led_czerw, OUTPUT);
  pinMode(led_zolty, OUTPUT);
  */
  //Czekanie na odzew programu:
}

void loop() {

  Oczekiwanie();
  Praca();
}

void Oczekiwanie()
{
  /*
  digitalWrite(led_nieb, LOW);
  digitalWrite(led_czerw, LOW);
  digitalWrite(led_zolty, HIGH);
  */
  while(Serial.read() >= 0){} //Czyszczenie bufora (nie dziala?)
  while(Serial.read() != 'o')
  {
    Serial.println("star");
    delay(1000); 
  } 
}

void Praca()
{
  //digitalWrite(led_zolty, LOW);

  while(true)
  {
    if (Serial.available() > 0)
    {
      for (int i = 0; i<4; i++)
      {
        inChar = Serial.read();
        command[i] = inChar;
      }
      command[4]='\0';
    }
      
    // Komenda awaryjnego przerwania pracy STOP
    if(!strcmp(command,"stop"))
    {
      stepperX.powerEnable(false);
      break;
    }

    // Komenda inicjalizacji pracy ONNN
    if(!strcmp(command,"onnn"))
    {
      stepperX.powerEnable(true);
      // Ustawienie prędkości
      stepperX.setSpeed(30);
      stepperY.setSpeed(30);
    }

    // Komenda zakończenia pracy OFFF
    if(!strcmp(command,"offf"))
    {
      //Miejsce na powrot
      //Serwo_x(abs(pos_x));
      //Serwo_y(abs(pos_y));
      stepperX.step(mov(-pos_x));
      stepperY.step(mov(-pos_y));
      pos_x=0;
      pos_y=0;
      break;
    }

    // Komenda ruchu w osi x MOVX[value]
    if(!strcmp(command,"movx"))
    {
      for(int i=0;Serial.available() > 0 && i<6;i++)
      {
        inChar = Serial.read();
        value_char[i]=inChar;
      }
      value_char[6]='\0';
      
      value = atoi(value_char);
      pos_x+=value;
      stepperX.step(mov(value));

      //Miejsce na sterowanie
      //Serwo_x(abs(value));
      Serial.println(pos_x);
    }

    // Komenda ruchu w osi y MOVY[value]
    if(!strcmp(command,"movy"))
    {
      for(int i=0;Serial.available() > 0 && i<6;i++)
      {
        inChar = Serial.read();
        value_char[i]=inChar;
      }
      value_char[6]='\0';
    
      value = atoi(value_char);
      pos_y+=value;
      stepperY.step(mov(value));

      //Miejsce na sterowanie 
      //Serwo_y(abs(value));
      Serial.println(pos_y);
    }
  
    //Zerowanie wejscia
    delay(100);
    value=0;
    for(int i=0;i<4;i++)
    {
      value_char[i]='\0';
      command[i]='\0'; 
    }
  }
}

// Funkcaja zamiejająca um na kroki
int mov(int value)
{
  return (int)(value * motor_steps / 200); // rzutowanie na wszelki wypadek
  /* 0.5 to jest przekładnia na silniku, 1000 - to jest skok na śrubie,
   *  ale ostatecznie możesz sprawdzić czy to sie z grubsza zgadza
   */
}


//Testowe funkcje:
void Serwo_x(int x)
{
  for(int i=0;i<x;i++)
  {
    digitalWrite(led_nieb, HIGH);
    delay(150);
    digitalWrite(led_nieb, LOW);
    delay(150);
  }
}

void Serwo_y(int y)
{
  for(int i=0;i<y;i++)
  {
    digitalWrite(led_czerw, HIGH);
    delay(150);
    digitalWrite(led_czerw, LOW);
    delay(150);
  }
}
