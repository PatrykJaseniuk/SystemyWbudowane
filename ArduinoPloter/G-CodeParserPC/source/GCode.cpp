#include "GCode.h"

gpr::gcode_program GCode::program;
std::vector<gpr::block>::iterator GCode::iterator;
std::string GCode::x = "000.00", GCode::y = "000.00", GCode::z = "001.00";