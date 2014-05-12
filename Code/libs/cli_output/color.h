#ifndef COLOR_H
#define COLOR_H

#include <iostream>

namespace TCOM
{
	/**
	 * \brief Defines a color to be output to
	 *			a bash terminal window.
	 **/
	class Color
	{
		private:
			/** \brief The number determining the code. **/
			char myCode;

			/** 
			 * \brief Construct a color from its number code.
			 *
			 * \param c The number code for this color.
			 **/
			Color(char c);

		public:
			/** \brief The color black. **/
			static const Color BLACK;
			/** \brief The color red. **/
			static const Color RED;
			/** \brief The color green. **/
			static const Color GREEN;
			/** \brief The color yellow. **/
			static const Color YELLOW;
			/** \brief The color blue. **/
			static const Color BLUE;
			/** \brief The color magenta (purple, basically). **/
			static const Color MAGENTA;
			/** \brief The color cyan (a lighter blue). **/
			static const Color CYAN;
			/** \brief The color white. **/
			static const Color WHITE;

			char getColorCode() const;

			/**
			 * \brief Make the terminal output this color as the foreground.
			 *
			 * \param os The output stream to write to.
			 * \param c The color to change to.
			 *
			 * \returns The parameter `os`.
			 **/
			friend std::ostream& operator<< (std::ostream& os, const Color& c);
	};
}

#endif
