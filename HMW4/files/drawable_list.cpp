
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
		n.iterator_counter++; // if the node is not nullptr increse its counter cause this point to the node
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

	//make sure that the pointer is not null- nothing to decrease
	if (ptr == nullptr)
		return;

	//decrease this iterator's counter
	ptr->iterator_counter--;

	//conditions to delete the memory of node
	if (ptr->iterator_counter == 0 && ptr->valid==false) {
		//conditions for the cases of head and tail of list
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

	//make sure that the pointer is not null- if it's nullptr the iterator is already invalid
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
	if (ptr == other.ptr) //the iterators point to the same node
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

	//Firstly, we shall check that we have received correct input
	if (ptr != nullptr) {

		//If the next node is null - we are at the tail of list and 
		//we shall return invalid iterator(points to nullptr)
		if (ptr->next == nullptr) {
			//keep the next pointer in case the decrease_counter deletes the pointer memory
			struct Node* nextPtr = ptr->next; 
			decrease_counter();
			ptr = nextPtr;
			return *this;
		}

		//keep the next pointer in case the decrease_counter deletes the pointer memory
		struct Node* nextPtr = ptr->next; 
		decrease_counter();

		//In case the next node is NOT valid, we shall progress 
		//until a valid node
		while ((nextPtr != nullptr) && (nextPtr->valid == false)) {
			nextPtr = nextPtr->next;
			//If we reached the end of the list, we shall return
			//invalid iterator
			if (nextPtr == nullptr) {
				ptr = nextPtr;
				return *this;
			}
		}
		//Progress and increase the counter if we reached a valid node
		ptr = nextPtr;
		increase_counter();
		return *this;
	}
	//if we get here the iterator points to nullptr
	//i.e. end of list and nothing to progress
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



		//If the prev node is null - we are at the head and 
		//we shall return invalid iterator
		if (ptr->prev == nullptr) {
			//keep the prev pointer in case the decrease_counter deletes the pointer memory
			struct Node* prevPtr = ptr->prev;
			decrease_counter();
			ptr = prevPtr;
			return *this;
		}
		//keep the prev pointer in case the decrease_counter deletes the pointer memory
		struct Node* prevPtr = ptr->prev;
		decrease_counter();
		//In case the next node is NOT valid, we shall 
		//regress until a valid node
		while ((prevPtr != nullptr) && (prevPtr->valid == false)) {
			prevPtr = prevPtr->prev;
			//If we reached the head of the list, we shall 
			//return invalid iterator
			if (prevPtr == nullptr) {
				ptr = prevPtr;
				return *this;
			}
		}
		//Regress and increase the counter
		ptr = prevPtr;
		increase_counter();
		return *this;
	}
	//if we get here the iterator points to nullptr
	//i.e. head of list and nothing to progress
	return *this;
}

/**
 * @breif Returns true iff this is valid
 */
bool Iterator::valid() const {
	if (ptr == nullptr) //if pointer is nullptr the iterator is invalid
		return false;
	return ptr->valid;
}

/*
 * @brief Creates an empty list
 */

DrawableList::DrawableList() :
	//initialize empty list- head and tail are nullptr
	head(nullptr),
	tail(nullptr),
	size(0)
{
};

/*
 * @brief Free all the objects of this.
 * @note Must free the memory for the drawable objects as well
 */
DrawableList::~DrawableList() {

	Iterator it(*head);
	while (size > 0) {
		erase(it);
		it = it.next();
	}

	/*//Start an iterator at the list's beginning
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
	delete tail;*/
}

/*
 * @brief Push to list front (before head).
 */
void DrawableList::push_front(Drawable& item) {
	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	newNode->next = head;

	// in case the list is empty- head and tail points to the same new node
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

	// in case the list is empty- head and tail points to the same new node
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
	if (it.ptr == nullptr) //legal input
		return;
	it.invalidate(); //first, invalidate the iterator i.e. the node
	if (it.ptr == head) {
		if (size == 1) { //list has one object- head is equal to tail
			head = nullptr;
			tail = nullptr;
			size--;
			return;
		}
		head = it.ptr->next;
		head->prev = nullptr;
	}
	else if (it.ptr == tail) {
		tail = it.ptr->prev;
		tail->next = nullptr;
	}
	else { //node is inside the list- has prev and next
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
	if (it.valid() == false) //in case the head is invalid- find the "real" valid head of list
		it.next();
	return it;
}

/**
 * @brief Returns an iterator to the end of the list
 */
Iterator DrawableList::end() {
	Iterator it(*tail);
	if (it.valid() == false) //in case the tail is invalid- find the "real" valid tail of list
		it.prev();
	return it;
}