#include "apple.h"
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"

#define pass (void)0

Apple::Apple(unsigned short x, unsigned short y) :
	Drawable({ x, y, 1, 1 }),
	gfx(APPLE),//-1 stands for an apple, 1 stands for a monster
	isdrawn(false)
{

};


/**
	* @brief Move the object in the direction
	*/
void Apple::move(direction_t direction) {
	pass; //Nothing happens as the apple never moves
}

/**
* @brief Draw the object
*/
void Apple::draw() {
	if (isdrawn == true) // apple already drawn
		return;
	else {
		isdrawn = true;
		mini_gui_print_rect(mg, bounding_box, gfx);
	}
}

/**
* @brief Return an ID that is unique to
* the dynamid type of the drawable object.
*/

int Apple::id() {
	return -1;
}

/**
* @brief Is called whenever any refresh is required
*/
void Apple::refresh() {
	pass;
}


/**
* @brief Do a step in the 'game of life'
* @param lst A list of all drawable objects in the world
*/
void Apple::step(DrawableList& lst) {
	pass;
}

