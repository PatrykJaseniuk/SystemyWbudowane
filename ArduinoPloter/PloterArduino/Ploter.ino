/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.floateraction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/
// #include "Przycisk.h"
#include <Servo.h>
#include "SerialPC.h"
#include "Ramie.h"
#include "Program.h"

float valZadaneServo1; // variable to read the value from the analog pin
float valZadaneServo2;
float valZadaneServo3;

Ramie ramie;
bool czyWyslanoKoniec = true;
double y, x;

void setup()
{
  ramie.UstawServa(9, 10, 11);
  SerialPC::begin();
  ramie.ustawPolozenieDocelowe(0, 0, 0);

  // Program::push(75.0, 0.0, 1.0);
  // Program::push(150.0, 0.0, -1.0);
  // Program::push(150.0, 50.0, 1.0);
  // Program::push(80.0, 130.0, -1.0);
  // Program::push(20.0, 130.0, 0.0);
  // Program::push(20.0, 65.0, 0.0);
  // Program::push(75.0, 0.0, 0.0);
  // y = 0;
  // x = 75;
}
void loop()
{
  // float valZadaneX, valZadaneY, valZadaneZ;
  // if (SerialPC::odczytajXYZ(valZadaneX, valZadaneY, valZadaneZ))
  // {
  //   ramie.ustawPolozenieDocelowe(valZadaneX, valZadaneY, valZadaneZ);
  // }
  if (SerialPC::parseMesage())
  {
    float valZadaneX, valZadaneY, valZadaneZ;
    SerialPC::odczytajXYZ(valZadaneX, valZadaneY, valZadaneZ);

    // Program::push(valZadaneX, valZadaneY, valZadaneZ);
    ramie.ustawPolozenieDocelowe(-valZadaneX, valZadaneY, valZadaneZ);
    // czyWyslanoKoniec = false;
    // SerialPC::wyslijKoniec();
    czyWyslanoKoniec = false;
  }
  else
  {
    if (ramie.porusz())
    {
      if (czyWyslanoKoniec == false)
      {
        SerialPC::wyslijKoniec();
        czyWyslanoKoniec = true;
      }

      // double x, y, z;
      // Program::getNext(x, y, z);
      // y += 10;
      // x -= 4;
      // ramie.ustawPolozenieDocelowe(x, y, z);
    }
  }
}

void serialEvent()
{

  // if ()
  // {
  //   float valZadaneX, valZadaneY, valZadaneZ;
  //   valZadaneX = SerialPC::odczytajX();
  //   valZadaneY = SerialPC::odczytajY();
  //   valZadaneZ = SerialPC::odczytajZ();

  //   //  String wiadomosc = "aktualne X :";
  //   // wiadomosc += ramie.aktualneX;
  //   // wiadomosc += "\naktualne Y :";
  //   // wiadomosc += ramie.aktualneY;
  //   // wiadomosc += "\naktualne Alfa :";
  //   // wiadomosc += ramie.aktualneAlfa;
  //   // wiadomosc += "\naktualne Beata :";
  //   // wiadomosc += ramie.aktualneBeta;
  //   // Serial.println(wiadomosc);

  //   ramie.ustawPolozenieDocelowe(valZadaneX, valZadaneY, valZadaneZ);
  // }
}

// inline void zaladujGcode()
// {
    
// }
