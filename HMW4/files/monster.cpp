#include "monster.h"
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"

Monster::Monster(unsigned short x, unsigned short y, int direction_hold) :
	Drawable({ x, y, (unsigned short)1, (unsigned short)1 }),
	level(1),
	vel(1),
	current_direction(left),
	direction_hold(direction_hold),
	direction_counter(0),
	gfx(MONSTER0) //1 stands for a monster, -1 stands for an apple
{
	unsigned short next_step = x - 1;
	next_bb = { next_step,y,(unsigned short)1,(unsigned short)1 };
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
	//mini_gui_move(mg, next_bb.x, next_bb.y);
}

/**
 * @brief Is called whenever any refresh is required
 */
void Monster::refresh() {
	if (level < 5) {
		gfx = MONSTER0;
		vel = 1;
		next_bb.width = 1;
		next_bb.height = 1;
	}
	else if (level < 15) {
		gfx = MONSTER1;
		vel = 1;
		next_bb.width = 3;
		next_bb.height = 1;
	}
	else if (level < 25) {
		gfx = MONSTER2;
		vel = 1;
		next_bb.width = 3;
		next_bb.height = 2;
	}
	else {
		gfx = MONSTER3;
		vel = 2;
		next_bb.width = 8;
		next_bb.height = 3;
	}
	// Get world size
	struct rect world_size = mini_gui_get_screen_size(mg);
	// Fix position in case of screen overflow
	if (next_bb.x + next_bb.width >= world_size.width) {
		next_bb.x = world_size.width - next_bb.width;
	}
	if (next_bb.y + next_bb.height >= world_size.height) {
		next_bb.y = world_size.height - next_bb.height;
	}
}
/*
void Monster::eatApple(Iterator& appleIter, DrawableList& lst) {
	set_level(1);
	lst.erase(appleIter);
	
}
*/

/*
void Monster::fight(Iterator& myselfIter, Iterator& enemyIter, DrawableList& lst) {
	Monster* enemy = dynamic_cast<Monster*> (enemyIter.get_object);
	if (enemy->get_level() < get_level()) {
		level += enemy->get_level();
		lst.erase(enemyIter);
	}
	else {
		enemy->set_level(level);
		lst.erase(myselfIter);
	}
}
*/

int Monster::id() {
	return 1;
}

void Monster::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	mini_gui_print_rect(mg, next_bb, gfx);
}

void Monster::step(DrawableList& lst) {
 //////COMMENT - CHECK ALL THE INPUTS LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Iterator iter = lst.begin(); 
	
	//Firstly, we shall find an iterator to this current monster
	Iterator iterTmp = iter; //Initialize a temporary iterator
	while (iterTmp.get_object() != this)
		iterTmp = iterTmp.next();

	Iterator myselfIter = iterTmp; //myselfIter is an iterator to this current monster

	for (int i=0; i<lst.get_size(); i++) {
		mini_gui_log(mg, "# list size: %d\n", lst.get_size());
		Drawable* drawable = iter.get_object();
		if (drawable==this) {
			iter = iter.next();
			continue;
		}
		if (collide(*drawable)) {
			if (drawable->id() == -1) {//check whether it's an apple (apples' ID is -1)
				//Then eat the apple:
				set_level(1);
				lst.erase(iter);
			}
			else
			{
				//Let's fucking fight!!!
				Monster* enemy = dynamic_cast<Monster*> (iter.get_object());
				if (enemy->get_level() < get_level()) {
					level += enemy->get_level();
					lst.erase(iter);
				}
				else {
					enemy->set_level(level);
					lst.erase(myselfIter);
				}
			}
		}
		iter = iter.next(); ///=opeator IMPLEMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		mini_gui_log(mg, "# next object is %d\n", drawable->id());
		refresh();
	}
	
}

int Monster::get_level() {
	return level;
}

void Monster::set_level(int increment) {
	level += increment;
}