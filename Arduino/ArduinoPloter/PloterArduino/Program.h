struct Pozycja
{
    double x, y, z;
};

class Program
{
private:
    static const int size = 100;
    static Pozycja tabPozycji[size];
    static int pushIterator;
    static int getIterator;

public:
   static void push(double x, double y, double z)
    {
        if (pushIterator < size)
        {
            tabPozycji[pushIterator].x = x;
            tabPozycji[pushIterator].y = y;
            tabPozycji[pushIterator].z = z;
            pushIterator++;
        }
    }
    static bool getNext(double &x, double &y, double &z)
    {
        if (getIterator < pushIterator)
        {
            x = tabPozycji[getIterator].x;
            y = tabPozycji[getIterator].y;
            z = tabPozycji[getIterator].z;
            getIterator++;
            return true;
        }
        else
        {
            return false;
        }
    }


};