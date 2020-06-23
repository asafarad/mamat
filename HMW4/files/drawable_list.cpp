
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drawable_list.h"
using namespace std;

/**
 * @brief Iterator's constructor
 */
Iterator::Iterator(Node& n) :
	ptr(&n) {
	if (&n != nullptr)
		n.iterator_counter++;
};

/**
 * @brief Iterator's copy constructor
 */
Iterator::Iterator(const Iterator& other) :
	ptr(other.ptr)
	// Should we initialize also DrawableList??????????????????
{
	increase_counter();
};

/**
 * @brief Iterator's destructor
 */
Iterator::~Iterator() {
	if (ptr == nullptr)
		return;
	decrease_counter();
}

/**
 * @brief Decreases iterator counter in the node pointed by this
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 */

void Iterator::decrease_counter() {

	//make sure that the pointer is not null
	if (ptr == nullptr)
		return;

	//decrease this iterator's counter
	ptr->iterator_counter--;

	//conditions for the cases of head and tail
	if (ptr->iterator_counter == 0 && ptr->valid==false) {
		if (ptr->prev != nullptr)
			ptr->prev->next = ptr->next;
		if (ptr->next != nullptr)
			ptr->next->prev = ptr->prev;
		delete ptr->item;
		delete ptr;
	}	
}

/**
 * @brief Increases the iterator counter
 * of the node pointed by ptr
 */

void Iterator::increase_counter() {
	if (valid())
		ptr->iterator_counter++;
}


/*
 * @brief Returns the item pointerd by this
 */

Drawable* Iterator::get_object() {

	//make sure that the pointer is not null
	if (ptr == nullptr)
		return nullptr;

	return ptr->item;
}

/*
 * @brief Make the node pointed by this to be invalid.
 * @note In case this is the last iterator that
 * points to a node, free the memory of the node
 */
void Iterator::invalidate() {

	//make sure that the pointer is not null
	if (ptr == nullptr)
		return;
	ptr->valid = false;
}

/**
 * @brief Changes the state of this to point at the next valid node
 * @returns this
 * @note In case there is no next valid node, sets this as invalid
 */
Iterator& Iterator::set(const Iterator& other) {
	if (ptr == other.ptr)
		return *this;
	decrease_counter();
	ptr = other.ptr;
	increase_counter();
	return *this;
}

/**
 * @brief Changes the state of this to point at the next valid node
 * @returns this
 * @note In case there is no next valid node, sets this as invalid
 */
Iterator& Iterator::next() {

	//Decreasing the current iterator's counter for all cases
	//Firstly, we shall check that we have received correct input
	if (ptr != nullptr) {

		//If the next node is null - we are at the tail and 
		//we shall return invalid iterator
		if (ptr->next == nullptr) {
			struct Node* tmp = ptr->next;
			decrease_counter();
			ptr = tmp;
			return *this;
		}

			struct Node* tmp = ptr->next;
			decrease_counter();

			//In case the next node is NOT valid, we shall progress 
			//until a valid node
			while ((tmp != nullptr) && (tmp->valid == false)) {
				tmp = tmp->next;
				//If we reached the end of the list, we shall return
				//invalid iterator
				if (tmp == nullptr) {
					ptr = tmp;
					return *this;
				}
			}
		//Progress and increase the counter
		ptr = tmp;
		increase_counter();
		return *this;
	}

	return *this;
}

/**
 * @brief Changes the state of this to point at the previous valid node
 * @returns this
 * @note In case there is no previous valid node, sets this as invalid
 */
Iterator& Iterator::prev() {


	//Firstly, we shall check that we have received correct input
	if (ptr != nullptr) {



		//If the next node is null - we are at the tail and 
		//we shall return invalid iterator
		if (ptr->prev == nullptr) {
			struct Node* tmp = ptr->prev;
			decrease_counter();
			ptr = tmp;
			return *this;
		}

		/*//If the next node is indeed valid - we just move to it
		if (ptr->next->valid) {
			ptr = ptr->next;
			increase_counter();
			return *this;
		}*/

		struct Node* tmp = ptr->prev;
		decrease_counter();
		//In case the next node is NOT valid, we shall 
		//progress until a valid node
		while ((tmp != nullptr) && (tmp->valid == false)) {
			tmp = tmp->prev;
			//If we reached the end of the list, we shall 
			//return invalid iterator
			if (tmp == nullptr) {
				ptr = tmp;
				return *this;
			}
		}
		//Progress and increase the counter
		ptr = tmp;
		increase_counter();
		return *this;
	}

	return *this;
}

/**
 * @breif Returns true iff this is valid
 */
bool Iterator::valid() const {
	if (ptr == nullptr)
		return false;
	return ptr->valid;
}

/*
 * @brief Creates an empty list
 */

DrawableList::DrawableList() :
	size(0)
{
	head = nullptr;
	tail = head;
};

/*
 * @brief Free all the objects of this.
 * @note Must free the memory for the drawable objects as well
 */
DrawableList::~DrawableList() {

	//Start an iterator at the list's beginning
	Node* currNode = head;
	Node* tmpNode;

	//Then iterator until the list's end
	while (currNode != tail) {
		delete currNode->item;
		tmpNode = currNode->next;
		delete currNode;
		currNode = tmpNode;
	}

	if (tail != nullptr)
		delete tail->item;
	delete tail;
}

/*
 * @brief Push to list front (before head).
 */
void DrawableList::push_front(Drawable& item) {

	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	newNode->next = head;

	// in case the list is empty
	if (size == 0) { 
		head = newNode;
		tail = head;
		size++;
		return;
	}

	// otherwise:
	head->prev = newNode;
	head = newNode;
	size++;
}

/*
 * @brief Push to list back (after tail).
 */
void DrawableList::push_back(Drawable& item) {
	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	newNode->prev = tail;

	// in case the list is empty
	if (size == 0) {
		tail = newNode;
		head = tail;
		size++;
		return;
	}
	// otherwise:
	tail->next = newNode;
	tail = newNode;
	size++;
}

/**
 * @brief Removes an object pointed by the iterator
 */
void DrawableList::erase(Iterator& it) {
	it.invalidate();
	if (it.ptr == head) {
		//it.ptr->valid = false;
		head = it.ptr->next;
		head->prev = nullptr;
	}
	else if (it.ptr == tail) {
		//it.ptr->valid = false;
		tail = it.ptr->prev;
		tail->next = nullptr;
	}
	else {
		//it.invalidate();
		it.ptr->prev->next = it.ptr->next;
		it.ptr->next->prev = it.ptr->prev;
	}
	size--;
}

/**
 * @brief Returns the size of this
 */
int DrawableList::get_size() const {
	return size;
}

/**
 * @brief Returns an iterator to the beginning of the list
 */
Iterator DrawableList::begin() {
	Iterator it(*head);
	return it;
}

/**
 * @brief Returns an iterator to the end of the list
 */
Iterator DrawableList::end() {
	Iterator it(*tail);
	return it;
}