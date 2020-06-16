#include "apple.h"
#include "drawable.h"
#include "ascii_objects.h"
#include "drawable_list.h"
#include "drawable.cpp"

//ASAF - I added a "pass" argument which means "doing nothing" :) It's useful for object like the apple which doesn't do much
#define pass (void)0

Apple::Apple(unsigned short x, unsigned short y, int direction_hold) :
	gfx(APPLE),
	ID(-1), //-1 stands for an apple, 1 stands for a monster
{
	bounding_box = { x, y, 1, 1 };

};


/**
	* @brief Move the object in the direction
	*/
void Apple::move() {
	pass; //Nothing happens as the apple never moves
}

/**
* @brief Draw the object
*/
void Apple::draw() {
	mini_gui_print_rect(mg, bounding_box, gfx);
}

/**
* @brief Return an ID that is unique to
* the dynamid type of the drawable object.
*/

int Apple::id() {
	return ID;
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

