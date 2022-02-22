#include "SerialPort.h"
#include <iostream>
using namespace std;

class Arduino
{
public:
    static void inline connect(char *port = "\\\\.\\COM4 ")
    {
        arduino = new SerialPort(port);
        if (arduino->isConnected())
        {
            cout << "Udalo sie poloczyc\n";
        }
        else
        {
            cout << "nie udalo sie poloczyc\n";
        }
    };

    /**
 * @brief wysyla komende do arduino
 * 
 * @param command OKXXXYYYZZZDDDD 
 * XXX - kat pierwszego serva
 * YYY - kat drugiego serva
 * ZZZ - kat drugiego serva 
 * DDDD - czas trwania ruchu  
 */
    static void inline wyslij(string command)
    {
        // char *port = "\\\\.\\COM4";
        // char incoming[MAX_DATA_LENGTH];
        if (arduino->isConnected())
        {
            cout << "\nrozmiar instrukcji: " << (command.size()+1);
            // cout << "podaj instrukcje [Y / N] ";
            // cin >> command;
            char *charArray = new char[command.size() + 1];
            copy(command.begin(), command.end(), charArray);
            charArray[command.size()] = '\n';

            arduino->writeSerialPort(charArray, MAX_DATA_LENGTH);
            // cout << "\nwyslano do arduino: " << command << "\n";

            // Sleep(100);
        }
    }

    static bool odbierz(std::string &wiadomosc)
    {
        char output[MAX_DATA_LENGTH+100];
        memset(output, 0, sizeof(output));
        int liczbaOdczytanychBitow = arduino->readSerialPort(output, MAX_DATA_LENGTH+100);
       
        if (liczbaOdczytanychBitow > 0)
        { cout << "\n liczba odczytanych bitow: "<<liczbaOdczytanychBitow<<"\nodebrno z Arduino:\n" << output << endl;
            return false;
        }
        else
        {
            return true;
        }
    }

public:
    static SerialPort *arduino;
};