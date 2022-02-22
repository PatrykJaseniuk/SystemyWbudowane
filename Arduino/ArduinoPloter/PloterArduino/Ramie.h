#include <Servo.h>
#include "Ramp.h"
#include <math.h>
#include <string.h>
#include "Interpolacja.h"

class Ramie
{
public:
    inline void UstawServa(int zlaczeServa1, int zlaczeServa2, int zlaczeServa3)
    {
        servo1.attach(zlaczeServa1);
        servo2.attach(zlaczeServa2);
        servo3.attach(zlaczeServa3);
    }

    inline void ustawPolozenieDocelowe(float x, float y, float z)
    {

        if (x < 30.0 && y < 30.0)
        {
            x = 70;
            y = 0;
        }
        doceloweX = x;
        doceloweY = y;
        doceloweZ = z;

        double aktualneX;
        double aktualneY;

        interpolacjaX.update(aktualneX);
        interpolacjaY.update(aktualneY);

        float odleglosc = getOdlegloscMiedzyPunktami(aktualneX, aktualneY, doceloweX, doceloweY);
        int delay = getDelay(odleglosc);

        // String wiadomosc = "ustawiam polozenie docelowe x: ";
        // wiadomosc += doceloweX;
        // wiadomosc += "\nustawiam polozenie docelowe y: ";
        // wiadomosc += doceloweY;
        // wiadomosc += "\nustawiam polozenie docelowe z: ";
        // wiadomosc += doceloweZ;
        // wiadomosc += "\npotrzebny czas: ";
        // wiadomosc += delay;
        // wiadomosc += "\nodleglosc: ";
        // wiadomosc += odleglosc;
        // Serial.println(wiadomosc);

        // interpolacjaX.pause();
        // interpolacjaY.pause();
        interpolacjaX.go(doceloweX, delay);
        // interpolacjaX.pause();
        interpolacjaY.go(doceloweY, delay);
        // interpolacjaY.pause();
        interpolacjaZ.go(doceloweZ, 1000);
    }

    inline bool porusz()
    {
        //
        //
        // if(!interpolacjaX.isPaused())
        // {
        //     interpolacjaX.resume();
        //     interpolacjaY.resume();
        // }
        
        bool czyKoniecZ = interpolacjaZ.update(aktualneZ);
        bool czyXKoniec = interpolacjaX.update(aktualneX);
        bool czyYKoniec = interpolacjaY.update(aktualneY);
        if (czyXKoniec && czyYKoniec && czyKoniecZ)
        {
            return true;
        }
        // aktualneAlfa = degToRad(interpolacjaX.update());
        // aktualneBeta = degToRad(interpolacjaY.update());

        kinematykaOdwrotna(dlugoscA, dlugoscB, aktualneX, aktualneY, aktualneAlfa, aktualneBeta);

        float przetworzoneAlfa = przetworzAlfa(aktualneAlfa, przesuniecieAlfa);
        float przetworzoneBeta = przetworzBeta(aktualneBeta, przesuniecieBeta);

        int alfaMikrosekundy = toMicroSeconds(przetworzoneAlfa);
        int betaMikrosekundy = toMicroSeconds(przetworzoneBeta);

        servo1.writeMicroseconds(alfaMikrosekundy);
        servo2.writeMicroseconds(betaMikrosekundy);
        servo3.write(getServo3Angle(doceloweZ));

        return false;
    }

private:
    Servo servo1, servo2, servo3;
    Interpolacja interpolacjaX, interpolacjaY, interpolacjaZ;
    float doceloweX, doceloweY, doceloweZ;
    float tepo = 60; //[czasTrwaniaFunkcjiUpdate/mm]
    float dlugoscA = 82, dlugoscB = 80;
    double aktualneX, aktualneY, aktualneZ;
    float aktualneAlfa = 0, aktualneBeta = 0;
    float const przesuniecieBeta = 2.967, przesuniecieAlfa = 0.907;
    const float msNaRad = 705.467;
    const float radNaDeg = 0.01744;

    inline int getServo3Angle(double z)
    {
        if (z < 0)
        {
            return 96;
        }
        else
        {
            return 25;
        }
    }
    constexpr inline int toMicroSeconds(float kat)
    {
        return msNaRad * kat + 700;
    }

    inline float degToRad(float kat)
    {
        return kat * radNaDeg;
    }

    inline float przetworzAlfa(float alfa, float przesuniecie)
    {
        return przesuniecie - alfa;
    }
    inline float przetworzBeta(float beta, float przesuniecie)
    {
        return przesuniecie - beta;
    }

    inline long getOdlegloscMiedzyPunktami(int x1, int y1, int x2, int y2)
    {
        long dx = x1 - x2;
        dx = dx * dx;
        long dy = y1 - y2;
        dy = dy * dy;
        return sqrt(dx + dy);
    }

    inline long getDelay(long odleglosc)
    {
        return (long)(odleglosc * tepo);
    }

    inline float wyznaczDlugoscPrzeciwprostokatnej(float x, float y)
    {
        return sqrt(x * x + y * y);
    }

    inline float wyznaczGamma(float x, float y)
    {
        if (x == 0)
        {
            return M_PI_2;
        }
        else
        {
            return atan(y / x);
        }
    }

    inline float wyznaczKat(float a, float b, float c)
    {
        return acos((a * a + b * b - c * c) / (2 * a * b));
    }

    inline void kinematykaOdwrotna(float a, float b, float x, float y, float &alfa, float &beta)
    {
        float gamma, delta, l;

        l = wyznaczDlugoscPrzeciwprostokatnej(x, y);
        // std::cout << "\ndlugosc l : " << l;
        gamma = wyznaczGamma(x, y);
        // std::cout << "\nkat gamma : " << gamma;
        delta = wyznaczKat(l, a, b);
        // std::cout << "\nkat delta : " << delta;
        alfa = gamma - delta;
        beta = wyznaczKat(a, b, l);
    }
    // inline void kinematykaOdwrotna(float aktualneX, float aktualneY, float &aktualneAlfa, float &aktualneBeta)
    // {
    //     float l = dlugosc(aktualneX, aktualneY);
    //     aktualneBeta = tCosBeta(dlugoscA, dlugoscB, l);
    //     float gamma = tCosGamma(dlugoscA, dlugoscB, l);
    //     float delta = atan(aktualneY / aktualneX);
    //     aktualneAlfa = delta - gamma;
    // }

    // inline float dlugosc(float x, float y)
    // {
    //     return sqrt(x * x + y * y);
    // }

    // float tCosGamma(float a, float b, float l)
    // {
    //     return acos((b * b - l * l - a * a) / (2 * l * a));
    // }

    // float tCosBeta(float a, float b, float l)
    // {
    //     return acos((l * l - a * a - b * b) / (2 * b * a));
    // }
};