#include <iostream>
#include "SerialPort.h"
#include "Arduino.h"
#include "GCode.h"

using namespace std;

int main(int argC, char **argV)
{
    string noweUstawienie;
    Arduino::connect();
    _sleep(5000);
    if (argC >= 2)
    {
        GCode::open(argV[1]);
        
        while (GCode::next(noweUstawienie))
        {
            string stoper;

            // string noweUstawienie = GCode::next();
            
            cout << "\nOKXXXXXXYYYYYYZZZZZZ :\n";
            cout<<noweUstawienie<<"###\n";
            // cin >> noweUstawienie;

        //    cin >> stoper;
             Arduino::wyslij(noweUstawienie);
            std::string wiadomoscOdebrana="";
            // _sleep(200);

            // cin >> stoper;
            while (Arduino::odbierz(wiadomoscOdebrana)){}
            
            // cout << "\nodebrano: " << wiadomoscOdebrana;
            
        }
        
    }
    else
    {
        while(noweUstawienie !="koniec")
        {
            cout << "\nOKXXXXXXYYYYYYZZZZZZ :\n";
            cin>>noweUstawienie;
             Arduino::wyslij(noweUstawienie);
        }
    }
}
