const int buttonPin = 11; // the number of the pushbutton pin

class Wyswietlacz
{
    public:
     static void inicjalizuj()
    {
        pinMode(digit0, OUTPUT);
        pinMode(digit1,OUTPUT);
        pinMode(digit2, OUTPUT);
        pinMode(digit3, OUTPUT);
        pinMode(digit4, OUTPUT);
        pinMode(digit5, OUTPUT);
        pinMode(digit6, OUTPUT);
        pinMode(digit7, OUTPUT);
    }

    static void wyswietlLiczbe(char liczba)
    {
        // liczba = 0;
        digitalWrite(digit0, liczba & 0b00000001);
        digitalWrite(digit1, liczba & 0b00000010);
        digitalWrite(digit2, liczba & 0b00000100);
        digitalWrite(digit3, liczba & 0b00001000);
        digitalWrite(digit4, liczba & 0b00010000);
        digitalWrite(digit5, liczba & 0b00100000);
        digitalWrite(digit6, liczba & 0b01000000);
        digitalWrite(digit7, liczba & 0b10000000);
    }

    private:
       const static int digit0 = 2;
       const static int digit1 = 3;
       const static int digit2 = 4;
       const static int digit3 = 5;
       const static int digit4 = 6;
       const static int digit5 = 7;
       const static int digit6 = 8;
       const static int digit7 = 9;
};
// variables will change:
int buttonState = 0; // variable for reading the pushbutton status

void setup()
{
    Serial.begin(9600);
    Wyswietlacz::inicjalizuj();
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
}

void loop()
{
    if (buttonClicked())
    {
        auto wylosowanaLiczba = millis() % 255;

        Wyswietlacz::wyswietlLiczbe(wylosowanaLiczba);
        Serial.println("nacisnieto Przycisk");
        Serial.println(String(wylosowanaLiczba));
        delay(1000);
    }
}

bool buttonClicked()
{
    if (digitalRead(buttonPin) == HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}