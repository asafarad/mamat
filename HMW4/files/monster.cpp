#include "monster.h"
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"

/**
	* @brief Monster's constuctor
*/
Monster::Monster(unsigned short x, unsigned short y, int direction_hold) :
	Drawable({ x, y, (unsigned short)1, (unsigned short)1 }),
	level(1),
	vel(1),
	current_direction(left),
	direction_hold(direction_hold),
	direction_counter(0),
	next_bb({ x, y, 1, 1 }),
	gfx(MONSTER0) 
{
};

/**
 * @brief Move the Monster in the direction
 */
void Monster::move(direction_t direction) {
	struct rect screen_size = mini_gui_get_screen_size(mg);

	//Reset the direction_counter to direction_hold
	if (direction_counter <= 0) {
		current_direction = direction;
		direction_counter = direction_hold;
	}

	//Choose the progress direction
	switch (current_direction) {
		case left:
			if ((bounding_box.x - vel) <= (screen_size.x))
				break;
			next_bb.x = bounding_box.x - vel;
			break;
		case right:
			if ((bounding_box.x + bounding_box.width + vel) 
				>= (screen_size.x + screen_size.width))
				break;
			next_bb.x = bounding_box.x + vel;
			break;
		case up:
			if ((bounding_box.y - vel) <= (screen_size.y))
				break;
			next_bb.y = bounding_box.y - vel;
			break;
		case down:
			if ((bounding_box.y + bounding_box.height + vel) 
				>= (screen_size.y + screen_size.height))
				break;
			next_bb.y = bounding_box.y + vel;
			break;
		}
	direction_counter--;
}

/**
 * @brief Is called whenever any refresh is required
 */
void Monster::refresh() {

	//Every monster under level
	//5 has the most basic gfx and vel
	if (level < 5) {
		gfx = MONSTER0;
		vel = 1;
		next_bb.width = 1;
		next_bb.height = 1;
	}

	//Look for monsters' level-ups:
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

/**
 * @brief Return an ID that is unique to
 * monsters: 1
 */
int Monster::id() {
	return 1;
}

/**
 * @brief Draw the object
 */
void Monster::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	bounding_box = next_bb;
	mini_gui_print_rect(mg, next_bb, gfx);
}

/**
 * @brief Do a step in the 'game of life'
 * @param lst A list of all drawable objects in the world
 */
void Monster::step(DrawableList& lst) {
 //////COMMENT - CHECK ALL THE INPUTS LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Iterator iter = lst.begin(); 
	
	//Firstly, we shall find an iterator to this current monster:
	Iterator myselfIter = iter;
	while (myselfIter.get_object() != this)
		myselfIter = myselfIter.next();

	//Now we shall run over all the valid objects:
	while (iter.valid() == true) {
		Drawable* drawable = iter.get_object();
		if (drawable==this) {
			iter = iter.next();
			continue;
		}
		
		//We're looking for objects that overlap:

		if (collide(*drawable)) {
			//We collided with another object! Let's
			//check whether it's an apple (apples' 
			//ID is -1)

			if (drawable->id() == -1) {
				//Then eat the apple:
				inc_level(1);
				lst.erase(iter);
				refresh();
			}
			else if (drawable->id() == 1)
			{
				//In case we bumped into another
				//Monster (Monsters' ID is 1) -
				//let's fight that bastard!
				Monster* enemy = dynamic_cast<Monster*> 
					(iter.get_object());

				//If we win:
				if (enemy->level <= level) {
					inc_level(enemy->level);
					lst.erase(iter);
					refresh();
				}

				//If we lse:
				else {
					enemy->inc_level(level);
					lst.erase(myselfIter);
					enemy->refresh();
				}
			}
		}
		
		iter = iter.next(); ///=opeator IMPLEMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
	}
	
}

/**
 * @brief A getter function for the monster's 
	current level
 */

int Monster::get_level() {
	return level;
}

/**
 * @brief A setter function that increases
	the monster's level by the specified
	increment
 */

void Monster::inc_level(int increment) {
	level += increment;
}