
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drawable_list.h"
using namespace std;

Iterator::Iterator(Node& n) :
	ptr(&n)
{};

Iterator::Iterator(const Iterator& other) :
	ptr(other.ptr)
	// Should we initialize also DrawableList??????????????????
{};

Iterator::~Iterator() {
	delete ptr;
}

void Iterator::decrease_counter() {
	ptr->iterator_counter--;
	if (ptr->iterator_counter == 0 && ptr->valid==false) {
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		delete ptr->item;
		delete ptr;
	}	
}

void Iterator::increase_counter() {
	ptr->iterator_counter++;
}

Drawable* Iterator::get_object() {
	return ptr->item;
}

void Iterator::invalidate() {
	if (ptr == nullptr)
		return;
	ptr->valid = false;
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
}

Iterator& Iterator::set(const Iterator& other) {
	if (other.ptr == nullptr) //input check
		return *this;
	if (ptr == other.ptr)
		return *this;
	decrease_counter();
	ptr = other.ptr;
	increase_counter();
	return *this;
}

Iterator& Iterator::next() {
	if (ptr->next == nullptr)
		return *this; //Ask this in the forum
	decrease_counter();
	while (ptr->next->valid == false) {
		ptr = ptr->next; //continue until we reach a valid node
	}
	ptr = ptr->next; //update to the wanted node
	increase_counter();
	return *this;
}

Iterator& Iterator::prev() {
	if (ptr->prev == nullptr)
		return *this;
	decrease_counter();
	while (ptr->prev->valid == false) {
		ptr = ptr->prev;
	}
	ptr = ptr->prev;
	increase_counter();
	return *this;
}

bool Iterator::valid() const {
	return ptr->valid;
}

DrawableList::DrawableList() :
	size(0)
{
	head = new Node;
	tail = new Node;
};

DrawableList::~DrawableList() {
	Node* currNode = tail;
	Node* tmpNode;
	while (currNode != head) {
		delete currNode->item;
		tmpNode = currNode->prev;
		delete currNode;
		currNode = tmpNode;
	}
	delete head->item;
	delete head;
}


void DrawableList::push_front(Drawable& item) {
	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

void DrawableList::push_back(Drawable& item) {
	Node* newNode = new Node;
	newNode->item = &item;
	newNode->valid = true;
	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;
}

void DrawableList::erase(Iterator& it) {
	it.invalidate();
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