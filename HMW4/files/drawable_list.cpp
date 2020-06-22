
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drawable_list.h"
using namespace std;

Iterator::Iterator(Node& n) :
	ptr(&n) {
	n.iterator_counter++;
};

Iterator::Iterator(const Iterator& other) :
	ptr(other.ptr)
	// Should we initialize also DrawableList??????????????????
{
	increase_counter();
};

Iterator::~Iterator() {
	if (ptr == nullptr)
		return;
	decrease_counter();
}

void Iterator::decrease_counter() {
	if (ptr == nullptr)
		return;
	ptr->iterator_counter--;
	if (ptr->iterator_counter == 0 && ptr->valid==false) {
		if (ptr->prev != nullptr)
			ptr->prev->next = ptr->next;
		if (ptr->next != nullptr)
			ptr->next->prev = ptr->prev;
		delete ptr->item;
		delete ptr;
	}	
}

void Iterator::increase_counter() {
	if (valid())
		ptr->iterator_counter++;
}

Drawable* Iterator::get_object() {
	if (ptr == nullptr)
		return nullptr;
	return ptr->item;
}

void Iterator::invalidate() {
	if (ptr == nullptr)
		return;
	ptr->valid = false;
	//ptr->prev->next = ptr->next;
	//ptr->next->prev = ptr->prev;
}

Iterator& Iterator::set(const Iterator& other) {
	if (ptr == other.ptr)
		return *this;
	decrease_counter();
	ptr = other.ptr;
	increase_counter();
	return *this;
}

Iterator& Iterator::next() {

	//Decreasing the current iterator's counter for all cases
	//Firstly, we shall check that we have received correct input
	if (ptr != nullptr) {

		

		//If the next node is null - we are at the tail and we shall return invalid iterator
		if (ptr->next == nullptr) {
			struct Node* tmp = ptr->next;
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

			struct Node* tmp = ptr->next;
			decrease_counter();
			//In case the next node is NOT valid, we shall progress until a valid node
			while ((tmp != nullptr) && (tmp->valid == false)) {
				tmp = tmp->next;
				//If we reached the end of the list, we shall return invalid iterator
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

Iterator& Iterator::prev() {


	//Firstly, we shall check that we have received correct input
	if (ptr != nullptr) {



		//If the next node is null - we are at the tail and we shall return invalid iterator
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
		//In case the next node is NOT valid, we shall progress until a valid node
		while ((tmp != nullptr) && (tmp->valid == false)) {
			tmp = tmp->prev;
			//If we reached the end of the list, we shall return invalid iterator
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

bool Iterator::valid() const {
	if (ptr == nullptr)
		return false;
	return ptr->valid;
}

DrawableList::DrawableList() :
	size(0)
{
	head = nullptr;
	tail = head;
};

DrawableList::~DrawableList() {
	Node* currNode = head;
	Node* tmpNode;
	while (currNode != tail) {
		delete currNode->item;
		tmpNode = currNode->next;
		delete currNode;
		currNode = tmpNode;
	}
	delete tail->item;
	delete tail;
}


void DrawableList::push_front(Drawable& item) {
	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	newNode->next = head;
	if (size == 0) { // list is empty
		head = newNode;
		tail = head;
		size++;
		return;
	}
	head->prev = newNode;
	head = newNode;
	size++;
}

void DrawableList::push_back(Drawable& item) {
	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	newNode->prev = tail;
	if (size == 0) { // list is empty
		tail = newNode;
		head = tail;
		size++;
		return;
	}
	tail->next = newNode;
	tail = newNode;
	size++;
}

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

int DrawableList::get_size() const {
	return size;
}

Iterator DrawableList::begin() {
	Iterator it(*head);
	return it;
}

Iterator DrawableList::end() {
	Iterator it(*tail);
	return it;
}