#include "column_group.h"

using namespace std;
using namespace TCOM;

ColumnGroup::ColumnGroup(const string& sep,
							const Command& sepFormat)
	:	myColumns(),
		mySepFormat(sepFormat),
		mySep(sep)
	{ }

void ColumnGroup::addColumn(const Column& col)
{
	myColumns.push_back(col);
}

bool ColumnGroup::removeColumn(uint index)
{
	if (index >= numColumns())
	{
		return false;
	}
	myColumns.erase(myColumns.begin() + index);
	return true;
}

bool ColumnGroup::insertColumn(uint index, const Column& col)
{
	if (index > numColumns())
	{
		return false;
	}
	myColumns.insert(myColumns.begin() + index, col);
	return true;
}

Column& ColumnGroup::operator[] (uint index)
{
	return myColumns.at(index);
}

const Column& ColumnGroup::operator[] (uint index) const
{
	return myColumns.at(index);
}

uint ColumnGroup::numColumns() const
{
	return myColumns.size();
}

ostream& TCOM::operator<< (ostream& os, const ColumnGroup& cols)
{
	uint lines = 0;
	for (uint i = 0; i < cols.myColumns.size(); ++ i)
	{
		if (cols.myColumns[i].numEntries() > lines)
		{
			lines = cols.myColumns[i].numEntries();
		}
	}

	for (uint i = 0; i < lines; ++ i)
	{
		for (uint j = 0; j < cols.myColumns.size(); ++ j)
		{
			cols[j].printEntry(os, i);
			os << Command::ResetGraphics();
			if (j != cols.myColumns.size() - 1)
			{
				os << cols.mySepFormat << cols.mySep;
			}
		}
		os << endl;
	}
	return os;
}