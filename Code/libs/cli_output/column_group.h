#include "column.h"

namespace TCOM
{
	/**
	 * \brief Describes a group of columns to be printed.
	 **/
	class ColumnGroup
	{
		private:
			std::vector<Column> myColumns;
			Command mySepFormat;
			std::string mySep;

		public:
			ColumnGroup(const std::string& sep = " ",
						const Command& sepFormat = Command::Nothing());

			void addColumn(const Column& col);
			bool removeColumn(uint index);
			bool insertColumn(uint index, const Column& col);
			
			Column& operator[] (uint index);
			const Column& operator[] (uint index) const;

			uint numColumns() const;

			friend std::ostream& operator<< (std::ostream& os,
												const ColumnGroup& cols);
	};
}