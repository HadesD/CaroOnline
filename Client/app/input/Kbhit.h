/**
 * Copyright http://linux-sxs.org/programming/kbhit.html
 */

#ifndef KBHIT_h
#define KBHIT_h
#if defined(__linux__)
#  include <termios.h>
#endif

namespace app { namespace input {

class Kbhit
{
	public:
		Kbhit();
		~Kbhit();
		int kbhit();
		int getch();

	private:
		struct termios initial_settings, new_settings;
		int peek_character;
};

} }

#endif
