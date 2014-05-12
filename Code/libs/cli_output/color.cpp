#include "color.h"

using namespace std;
using namespace TCOM;

Color::Color(char c)
	:	myCode(c)
	{ }

const Color Color::BLACK('0');
const Color Color::RED('1');
const Color Color::GREEN('2');
const Color Color::YELLOW('3');
const Color Color::BLUE('4');
const Color Color::MAGENTA('5');
const Color Color::CYAN('6');
const Color Color::WHITE('7');

char Color::getColorCode() const
{
	return myCode;
}

ostream& TCOM::operator<< (ostream& os, const Color& c)
{
	return os << (char) 27 << "[3" << c.getColorCode() << 'm';
}
