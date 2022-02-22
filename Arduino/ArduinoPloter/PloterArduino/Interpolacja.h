class Interpolacja
{
private:
    double pozycjaDocelowa = 0, pozycjaAktualna = 0;
    double szybkosc = 0;
    double const szybkoscBezwzgledna = 0.01;
    // double czasRozpoczecia = 0;
    // bool czyAktualizowano = true;
    bool czyKoniec = false;
    // double poprzedniCzas = 0;

    // inline double obliczSzybkosc(double aktualnaPozycja, double docelowaPozycja, double czasTrwania)
    // {
    //     double odleglosc = docelowaPozycja - aktualnaPozycja;

    //     return (double)odleglosc / czasTrwania;
    // }

    // inline double obliczPolozenie(double pozycjaPoczatkowa, double szybkosc, double czasTrwania)
    // {
    //     return pozycjaPoczatkowa + (szybkosc * czasTrwania);
    // }

    inline bool sprawdzCzyKoniec(double aktualnePolozenie, double polozenieKoncowe, double szybkosc)
    {
        double d = aktualnePolozenie - polozenieKoncowe;
        if (d < 0.001 && d > -0.001)
        {
            return true;
        }
        else if (szybkosc < 0)
        {
            return aktualnePolozenie <= polozenieKoncowe;
        }
        else
        {
            return aktualnePolozenie >= polozenieKoncowe;
        }
    }

    inline double wyznaczSzybkosc(double pozycjaAktualna, double pozycjaDocelowa, double czasTrwania)
    {

        double odleglosc = pozycjaDocelowa - pozycjaAktualna;

       
        return odleglosc / czasTrwania;
        // if(pozycjaAktualna>pozycjaDocelowa)
        // {
        //     return -;
        // }
        // else
        // {
        //     return szybkoscBezwzgledna;
        // }
    }

public:
    void go(double pozycjaDocelowa, double czasTrwania)
    {
        // pozycjaStartowa = pozycjaDocelowa;
        this->pozycjaDocelowa = pozycjaDocelowa;

        double d = pozycjaDocelowa - pozycjaAktualna;
        if(d<0.001 && d>-0.001)
        {
            czyKoniec = true;
        }else
        {
             szybkosc = wyznaczSzybkosc(pozycjaAktualna, pozycjaDocelowa, czasTrwania);
        // szybkosc = obliczSzybkosc(pozycjaStartowa, pozycjaDocelowa, czasTrwania);
        // czyAktualizowano = true;
        czyKoniec = false;
        }

       
    }

    inline bool update(double &pozycjaAktualna)
    {

        if (!czyKoniec)
        {
            this->pozycjaAktualna += szybkosc;
            if (sprawdzCzyKoniec(this->pozycjaAktualna, pozycjaDocelowa, szybkosc))
            {
                czyKoniec = true;
                this->pozycjaAktualna = pozycjaDocelowa;
            }
            // return pozycjaDocelowa;
            // }
            // else
            // {
            //     return pozycjaAktualna;
            // }
        }
        pozycjaAktualna = this->pozycjaAktualna;
        return czyKoniec;

        // else
        // {
        //     return pozycjaDocelowa;
        // }
        // return docelowaPozycjaAktualna;
        // if (czyAktualizowano)
        // {
        //     poprzedniCzas = 0;
        //     czasRozpoczecia = millis();
        //     czyAktualizowano = false;
        //     czyKoniec = false;
        // }
        // if (!czyKoniec)
        // {
        //     double czasTrwania;
        //     //  = millis() - czasRozpoczecia;
        //     // if(czasTrwania-poprzedniCzas>10.0)
        //     {
        //         czasTrwania = 1.5+poprzedniCzas;
        //     }
        //     poprzedniCzas=czasTrwania;
        //     double aktualnePolozenie = obliczPolozenie(pozycjaStartowa, szybkosc, czasTrwania);

        //     if (czyDoszloDoKonca(aktualnePolozenie, pozycjaDocelowa, szybkosc))
        //     {
        //         czyKoniec = true;
        //         return pozycjaDocelowa;
        //     }
        //     else
        //     {
        //         return aktualnePolozenie;
        //     }
        // }
        // else
        // {
        //     return pozycjaDocelowa;
        // }
    }
};