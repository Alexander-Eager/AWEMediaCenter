#ifndef COMMAND_H
#define COMMAND_H

#include "color.h"
#include <string>
#include <iostream>

namespace TCOM
{
	/**
	 * \brief Defines a general interface for an
	 *			ANSI escape sequence.
	 **/
	class Command
	{
		protected:
			/** \brief The string output to the terminal. **/
			std::string myCommand;

			/**
			 * \brief Construct the command from the given string.
			 *
			 * \param comm The string to output to the terminal.
			 **/
			Command(const std::string& comm);

		public:
			/**
			 * \brief Get the string to output to the terminal.
			 *
			 * \returns The string to output to the terminal.
			 **/
			const std::string& getCommandString() const;

			/**
			 * \brief Apply the command to the given terminal output.
			 *
			 * \param os The stream to apply the command to.
			 * \param comm The command to apply.
			 *
			 * \returns The parameter `os`.
			 **/
			friend std::ostream& operator<< (std::ostream& os, const Command& comm);

			/**
			 * \brief Applies the effects of both commands.
			 *
			 * If these commands conflict at all, the second is the one that matters.
			 *
			 * \param other The command to add to this one.
			 *
			 * \returns The resulting sum.
			 **/
			Command operator+ (const Command& other) const;

			// literally does nothing
			static Command Nothing();

			// these all deal with cursor movement
			static Command MoveCursorTo(uint row, uint col);
			static Command MoveCursorLeft(uint num = 1);
			static Command MoveCursorRight(uint num = 1);
			static Command MoveCursorUp(uint num = 1);
			static Command MoveCursorDown(uint num = 1);

			// clears contents of screen but doesn't scroll
			static Command EraseDisplay();
			// exactly the same as the clear command
			static Command ClearDisplay();

			// all of these are considered graphics
			static Command ResetGraphics();
			static Command MakeTextBold();
			static Command UnderlineText();
			static Command MakeTextBlink();
			static Command TurnOnReverseVideo();
			static Command TurnOnConcealed();
			static Command ChangeColor(const Color& foreground,
										const Color& background);
			static Command ChangeForegroundColor(const Color& c);
			static Command ChangeBackgroundColor(const Color& c);

			// TODO the mode setting and keyboard string stuff
	};
}

#endif