#ifndef APPLE_H
#define APPLE_H
#include "drawable.h"
#include "monster.h"

class Apple : public Drawable {

	// The gfx of the apple
	const char* gfx;
	bool isdrawn; //We shall use this boolean
	//member variable to make sure that the apple
	//hasn't been already drawn, so we don't
	//reprint over and over again the same apples

public:

	/**
	 * @brief Initiate an apple in x,y
	 */
	Apple(unsigned short x, unsigned short y);

	/**
	 * @brief Move the object in the direction
	 */
	virtual void move(direction_t direction);

	/**
	 * @brief Draw the object
	 */
	virtual void draw();

	/**
	 * @brief Return an ID that is unique to 
	 * the dynamid type of the drawable object.
	 */
	virtual int id();

	/**
	 * @brief Is called whenever any refresh is required
	 */
	virtual void refresh();

	/**
	 * @brief Do a step in the 'game of life'
	 * @param lst A list of all drawable objects in the world
	 */
	virtual void step(DrawableList& lst);
};

#endif 
