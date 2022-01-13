#include <HardwareSerial.h>
#include <Arduino.h>

class SerialPC
{
public:
  static void wyslijKoniec()
  {
    // Serial.println(mesage);
    Serial.print('O');
  }
  static bool odczytajXYZ(float &x, float &y, float &z)
  {
    if (odczytano == false)
    {
      odczytano = true;
      x = zadaneX;
      y = zadaneY;
      z = zadaneZ;
      return true;
    }
    else
    {
      return false;
    }
  }
  static float odczytajX()
  {
    return zadaneX;
  }
  static float odczytajY()
  {
    return zadaneY;
  }
  static float odczytajZ()
  {
    return zadaneZ;
  }

  static void begin()
  {
    Serial.begin(9600);
  }

  /**
       * @brief foramt wiadomosci: (OKXXX.XXYYY.YYZZZ.ZZ)
       *
       * @return true
       * @return false
       */
  static bool parseMesage()
  {
    // delay(10000);
    int liczbaDostepnychbitow = Serial.available();
    if (liczbaDostepnychbitow >= 21)
    {
      String mesage;
      // char buforWiadomosci[21];
      // int index = 0;
      // char odczytanyZnak = Serial.read();
      // while(odczytanyZnak!='\n' && index<20)
      // {
      //   buforWiadomosci[index] = odczytanyZnak;
      //   index++;
      //   odczytanyZnak = Serial.read();
      // }
      // buforWiadomosci[20] = '\n';
      // mesage = buforWiadomosci;
      char buffer[21];
      // Serial.readBytes(buffer,21);
      // mesage = buffer;
      Serial.readBytes(buffer,21);
      mesage = buffer;
      // Serial.println(liczbaDostepnychbitow);
      // Serial.print(mesage);

      String info = mesage.substring(0, 2);
      if (info.equals("OK"))
      {
        String sValServo1 = mesage.substring(2, 8);
        String sValServo2 = mesage.substring(8, 14);
        String sValServo3 = mesage.substring(14, 20);
        zadaneX = sValServo1.toFloat();
        zadaneY = sValServo2.toFloat();
        zadaneZ = sValServo3.toFloat();
        odczytano = false;
        //test
        // String odpowiedz = "\nvalServo1 = " + sValServo1;
        // odpowiedz += "\nValServo2 = " + sValServo2;
        // odpowiedz += "\nValServo3 = " + sValServo3;

        // Serial.print(mesage);
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

private:
  // static String mesage;
  static bool odczytano;
  static float zadaneX;
  static float zadaneY;
  static float zadaneZ;
};