#ifndef COLUMN_H
#define COLUMN_H

#include <iostream>
#include <cstddef>
#include <vector>
#include "command.h"

namespace TCOM
{
	/**
	 * \brief Describes a column of colored text that
	 *			may be placed next to other such columns.
	 **/
	class Column
	{
		private:
			/** \brief Literally an empty string. **/
			static std::string myEmptyString;

			/** \brief List of entries in the column. **/
			std::vector<std::string> myEntries;
			std::vector<Command> myEntryFormats;
			/** \brief The format for the middle of the column. **/
			Command myFormat;
			/** \brief The minimum width allowed for the column. **/
			uint myMinWidth;
			/** \brief The actual width of the column. **/
			uint myWidth;

		public:
			Column(const Command& defaultFormat = Command::Nothing(),
					uint minWidth = 0);

			void addEntry(const std::string& entry);
			void addEntry(const std::string& entry, Command form);

			bool insertEntry(uint index, const std::string& entry);
			bool insertEntry(uint index, const std::string& entry,
								Command form);

			bool removeEntry(uint index);
			const std::string& getEntry(uint index) const;

			void setEntry(uint index, const std::string& value);
			void setEntryFormat(uint index, Command form);

			void printEntry(std::ostream& os, uint index) const;

			uint numEntries() const;
	};
}

#endif