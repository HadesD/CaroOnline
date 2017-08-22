// http://linux-sxs.org/programming/kbhit.html
#ifndef KBHIT_h
#define KBHIT_h
#include <termios.h>

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

#endif
