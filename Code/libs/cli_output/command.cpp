#include "command.h"

using namespace std;
using namespace TCOM;

#include <sstream>

Command::Command(const string& comm)
	:	myCommand(comm)
	{ }

ostream& TCOM::operator<< (ostream& os, const Command& comm)
{
	return os << comm.getCommandString();
}

Command Command::operator+ (const Command& other) const
{
	return Command(myCommand + other.myCommand);
}

const string& Command::getCommandString() const
{
	return myCommand;
}

Command Command::Nothing()
{
	return Command("");
}

Command Command::MoveCursorTo(uint row, uint col)
{
	stringstream ss;
	ss << (char) 27
		<< '['
		<< row
		<< ';'
		<< col
		<< 'H';
	return Command(ss.str());
}

Command Command::MoveCursorLeft(uint num)
{
	stringstream ss;
	ss << (char) 27
		<< '['
		<< num
		<< 'D';
	return Command(ss.str());
}
Command Command::MoveCursorRight(uint num)
{
	stringstream ss;
	ss << (char) 27
		<< '['
		<< num
		<< 'C';
	return Command(ss.str());
}
Command Command::MoveCursorUp(uint num)
{
	stringstream ss;
	ss << (char) 27
		<< '['
		<< num
		<< 'A';
	return Command(ss.str());
}
Command Command::MoveCursorDown(uint num)
{
	stringstream ss;
	ss << (char) 27
		<< '['
		<< num
		<< 'B';
	return Command(ss.str());
}

// deletes content of screen
Command Command::EraseDisplay()
{
	stringstream ss;
	ss << (char) 27
		<< "[2J";
	return Command(ss.str());
}

// clear command
Command Command::ClearDisplay()
{
	return Command::EraseDisplay() + Command::MoveCursorTo(0, 0);
}

// all of these are considered graphics
Command Command::ResetGraphics()
{
	stringstream ss;
	ss << (char) 27
		<< "[0m";
	return Command(ss.str());
}
Command Command::MakeTextBold()
{
	stringstream ss;
	ss << (char) 27
		<< "[1m";
	return Command(ss.str());
}
Command Command::UnderlineText()
{
	stringstream ss;
	ss << (char) 27
		<< "[4m";
	return Command(ss.str());
}
Command Command::MakeTextBlink()
{
	stringstream ss;
	ss << (char) 27
		<< "[5m";
	return Command(ss.str());
}
Command Command::TurnOnReverseVideo()
{
	stringstream ss;
	ss << (char) 27
		<< "[7m";
	return Command(ss.str());
}
Command Command::TurnOnConcealed()
{
	stringstream ss;
	ss << (char) 27
		<< "[8m";
	return Command(ss.str());
}
Command Command::ChangeColor(const Color& foreground,
								const Color& background)
{
	stringstream ss;
	ss << (char) 27
		<< "[3"
		<< foreground.getColorCode()
		<< ";4"
		<< background.getColorCode()
		<< 'm';
	return Command(ss.str());
}
Command Command::ChangeForegroundColor(const Color& c)
{
	stringstream ss;
	ss << (char) 27
		<< "[3"
		<< c.getColorCode()
		<< 'm';
	return Command(ss.str());
}
Command Command::ChangeBackgroundColor(const Color& c)
{
	stringstream ss;
	ss << (char) 27
		<< "[4"
		<< c.getColorCode()
		<< 'm';
	return Command(ss.str());
}