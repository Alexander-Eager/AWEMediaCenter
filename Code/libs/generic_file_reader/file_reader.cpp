#include "file_reader.h"

#include <sstream>

bool copyFile(const std::string& file, std::ostream& out)
{
	// try to open locally first
	std::ifstream reader(file);

	// if it doesn't open, assume its a webpage and read that
	if (reader.fail())
	{
		// now try web page
		readURLIntoStream(file, out);
		return true;
	}

	// the file exists locally, so return all of its contents
	char buffer[1001];
	while (reader.getline(buffer, 1001))
	{
		out << buffer << '\n';
	}
	return true;
}