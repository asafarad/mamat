#include "monster.h"
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"

int Monster::count = 0;

Monster::Monster(unsigned short x, unsigned short y, int direction_hold) :

	level(1),
	vel(1),
	current_direction(left),
	direction_hold(direction_hold),
	direction_counter(0),
	gfx(MONSTER0),
	ID(count)
{
	bounding_box = { x, y, 1, 1 };
	next_bb = { x - 1,y,1,1 };
	count++;
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
	mini_gui_move(mg, next_bb.x, next_bb.y);
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

void Monster::eatApple(Iterator& appleIter, DrawableList& lst) {
	level++;
	lst.erase(appleIter);
	//refresh;
	
}
void Monster::fight(Iterator& enemyIter, DrawableList& lst) {
	Monster* enemy = dynamic_cast<Monster*> (enemyIter.get_object);
	if (enemy->get_level < level) {
		level += enemy->get_level;
		lst.erase(enemyIter);
	}
	else {
		enemy->set_level(level)
			lst.erase();

	}
}

int Monster::id() {
	return ID;
}

void Monster::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	mini_gui_print_rect(mg, next_bb, gfx);
}

void Monster::step(DrawableList& lst) {
 //////COMMENT - CHECK ALL THE INPUTS LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Iterator iter = lst.begin; 
	
	for (int i=0; i<lst.get_size; i++) {
		Drawable* drawable = iter.get_object;
		if (drawable->id == id) {
			iter = iter.next();
			continue;
		}
		if (collide(*drawable)) {
			if (drawable->id < 0) ////////CHECK WHETHER WE STILL WANT TO CHECK BY THE NEGATIVE ID
				eatApple(iter, lst);
			else
				level < iter.get_object
		}
		iter = iter.next(); ///=opeator IMPLEMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		refresh;
	}
	
}

int Monster::get_level() {
	return level;
}

void Monster::set_level(int increment) {
	level += increment;
}