#include "column.h"

using namespace std;
using namespace TCOM;

string Column::myEmptyString;

Column::Column(const Command& format, uint minWidth)
	:	myEntries(),
		myFormat(format),
		myMinWidth(minWidth),
		myWidth(minWidth)
	{ }

void Column::addEntry(const string& entry, Command form)
{
	myEntries.push_back(entry);
	myEntryFormats.push_back(form);
	if (myWidth < entry.size())
	{
		myWidth = entry.size();
	}
}

void Column::addEntry(const string& entry)
{
	myEntries.push_back(entry);
	myEntryFormats.push_back(myFormat);
	if (myWidth < entry.size())
	{
		myWidth = entry.size();
	}
}

bool Column::insertEntry(uint index, const string& entry, Command form)
{
	if (index > numEntries())
	{
		return false;
	}
	myEntries.insert(myEntries.begin() + index, entry);
	myEntryFormats.insert(myEntryFormats.begin() + index, form);
	return true;
}

bool Column::insertEntry(uint index, const string& entry)
{
	if (index > numEntries())
	{
		return false;
	}
	myEntries.insert(myEntries.begin() + index, entry);
	myEntryFormats.insert(myEntryFormats.begin() + index, myFormat);
	return true;
}

bool Column::removeEntry(uint index)
{
	if (index >= numEntries())
	{
		return false;
	}
	if (myEntries.at(index).size() == myWidth)
	{
		myEntries.erase(myEntries.begin() + index);
		uint max = myMinWidth;
		for (auto x : myEntries)
		{
			if (x.size() > max)
			{
				max = x.size();
			}
		}
		myWidth = max;
	}
	else
	{
		myEntries.erase(myEntries.begin() + index);
	}
	myEntryFormats.erase(myEntryFormats.begin() + index);
	return true;
}

const string& Column::getEntry(uint index) const
{
	if (index >= numEntries())
	{
		return myEmptyString;
	}
	return myEntries.at(index);
}

void Column::setEntry(uint index, const string& value)
{
	if (index < numEntries())
	{
		myEntries[index] = value;
		return;
	}
	while (numEntries() < index)
	{
		addEntry("");
	}
	myEntries.push_back(value);
}

void Column::setEntryFormat(uint index, Command form)
{
	if (index < numEntries())
	{
		myEntryFormats[index] = form;
	}
	while (numEntries() <= index)
	{
		myEntries.push_back(myEmptyString);
		myEntryFormats.push_back(form);
	}
}

uint Column::numEntries() const
{
	return myEntries.size();
}

void Column::printEntry(ostream& os, uint index) const
{
	// change format
	os << Command::ResetGraphics();
	if (index >= numEntries())
	{
		os << myFormat;
	}
	else
	{
		os << myEntryFormats[index];
	}

	// print out the entry
	uint numLeft = myWidth - getEntry(index).size();
	os << getEntry(index);
	for (uint i = 0; i < numLeft; ++ i)
	{
		os << ' ';
	}
}