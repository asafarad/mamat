#include "monster.h"
#include "drawable.h"
#include "ascii_objects.h"

Monster::Monster(unsigned short x, unsigned short y, int direction_hold) :

	level(1),
	vel(1),
	current_direction(left),
	direction_hold(direction_hold),
	direction_counter(0),
	gfx(MONSTER0)
{
	bounding_box = { x, y, 1, 1 };
	next_bb = { x - 1,y,1,1 };

};

void Monster::move(direction_t direction) {
	rect screen_size = mini_gui_get_screen_size(mg);
	if (direction_counter == 0) {
		switch (direction) {
		case left:
			if ((next_bb.x - vel) <= screen_size.x)
				return;
			next_bb.x = next_bb.x - vel;
			break;
		case right:
			if ((next_bb.x + next_bb.width + vel) >= screen_size.x + screen_size.width)
				return;
			next_bb.x = next_bb.x + vel;
			break;
		case up:
			if ((next_bb.y - vel) <= screen_size.y)
				return;
			next_bb.y = next_bb.y - vel;
			break;
		case down:
			if ((next_bb.y + next_bb.height + vel) >= screen_size.y + screen_size.height)
				return;
			next_bb.y = next_bb.y + vel;
			break;
		}
	}
}

void Monster::refresh() {
	if (level >= 5 && level < 15) {
		gfx = MONSTER1;
		next_bb.height = 1;
		next_bb.width = 3;
	}
	else if (level >= 15 && level < 25) {
		gfx = MONSTER2;
		next_bb.height = 2;
		next_bb.width = 3;
	}
	else if (level >= 15 && level < 25) {
		gfx = MONSTER3;
		next_bb.height = 3;
		next_bb.width = 8;
		vel = 2;
	}

}