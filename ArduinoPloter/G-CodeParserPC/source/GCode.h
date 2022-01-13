// #include <String.h>
#include "gcode_program.h"
#include "parser.h"
#include <fstream>
#include <streambuf>
#include <string>
#include <ostream>
// #include <string>

using namespace std;
class GCode
{
public:
    static inline void open(char *path)
    {
        std::string file = path;

        std::ifstream t(file);
        std::string file_contents((std::istreambuf_iterator<char>(t)),
                                  std::istreambuf_iterator<char>());

        program = gpr::parse_gcode(file_contents);
        iterator = program.begin();
    }

    static inline bool next(std::string &m)
    {
        while (iterator != program.end())
        {
            gpr::block block = *iterator;

            auto chankIterator = block.begin();
            bool czyWordAdress = false;
            while (chankIterator != block.end())
            {
                // if(chankIterator->tp() == gpr::chunk_type::CHUNK_TYPE_WORD)
                // {
                //     cout << *chankIterator;
                // }
                if (chankIterator->tp() == gpr::chunk_type::CHUNK_TYPE_WORD_ADDRESS)
                {
                    
                    // cout << "***" << *chankIterator << "---";
                    if (chankIterator->get_word() == 'X')
                    {
                        czyWordAdress = true;
                        gpr::addr adres = chankIterator->get_address();
                        double wartosc = adres.double_value();
                        x = to_string(wartosc);
                        x = x.substr(0, 6);
                    }
                    else if (chankIterator->get_word() == 'Y')
                    {
                        czyWordAdress = true;
                        gpr::addr adres = chankIterator->get_address();
                        double wartosc = adres.double_value();
                        y = to_string(wartosc);
                        y = y.substr(0, 6);
                    }
                    else if (chankIterator->get_word() == 'Z')
                    {
                        czyWordAdress = true;
                        gpr::addr adres = chankIterator->get_address();
                        double wartosc = adres.double_value();
                        z = to_string(wartosc);
                        z = z.substr(0, 6);
                    }
                }
                // if (chankIterator->tp() == gpr::chunk_type::CHUNK_TYPE_PERCENT)
                // {
                //     cout << *chankIterator;
                // }
                // if (chankIterator->tp() == gpr::chunk_type::CHUNK_TYPE_COMMENT)
                // {
                //     cout << *chankIterator;
                // }
                chankIterator++;
            }
            iterator++;

            if(czyWordAdress)
            {
                m = "OK" + x + y + z;
                return true;
            }           
        }
        return false;
    }

private:
    static std::string x, y , z;
    static std::vector<gpr::block>::iterator iterator;
    static gpr::gcode_program program;
};