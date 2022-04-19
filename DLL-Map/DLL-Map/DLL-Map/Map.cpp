#include "Map.h"
#include "MapIterator.h"
#include <exception>

using namespace std;

Map::DLLNode::DLLNode(TKey k, TValue v, DLLNode * n, DLLNode* p)
{
	elem.first = k;
	elem.second = v;
	next = n;
	prev = p;
}

Map::DLLNode::DLLNode()
{
	elem.first = NULL_TVALUE;
	elem.second = NULL_TVALUE;
	next = nullptr;
	prev = nullptr;
}

Map::Map(int sizeMap) {
	this->dummy.next = &dummy;
	this->dummy.prev = &dummy;
	this->sizeMap = sizeMap;
}
//Theta(1)

Map::~Map() {
	DLLNode* currentNode = this->dummy.next;
	while ((*currentNode).next != &this->dummy)
	{
		currentNode = (*currentNode).next;
		delete currentNode->prev;
	}
}
//Theta(n) n-number of Nodes

TValue Map::add(TKey c, TValue v){
	if (this->isFull())
		throw exception();
	DLLNode *currentNode = &this->dummy;
	if ((*currentNode).next == &this->dummy)
	{
		DLLNode* pNext = new DLLNode(c, v, &this->dummy, &this->dummy);
		this->dummy.next = pNext;
		this->dummy.prev = pNext;
		return NULL_TVALUE;
	}
	while ((*currentNode).next != &this->dummy && (*currentNode).elem.first != c)
	{
		currentNode = (*currentNode).next;
	}
	if ((*currentNode).elem.first == c)
	{
		TValue oldValue = (*currentNode).elem.second;
		(*currentNode).elem.second = v;
		return oldValue;
	}
	DLLNode* pNext = new DLLNode(c, v, (*currentNode).next, currentNode);
	(*(*currentNode).next).prev = pNext;
	(*currentNode).next= pNext;
	return NULL_TVALUE;
}
//Best case:Theta(1) Worst case: Theta(n) Total: O(n)

TValue Map::search(TKey c) const{
	DLLNode* currentNode = this->dummy.next;
	while ((*currentNode).next != &this->dummy && (*currentNode).elem.first != c)
	{
		currentNode = (*currentNode).next;
	}
	if ((*currentNode).elem.first == c)
	{
		return (*currentNode).elem.second;
	}
	return NULL_TVALUE;
}
//Best case:Theta(1) Worst case: Theta(n) Total: O(n)

TValue Map::remove(TKey c){
	if (this->search(c) == NULL_TVALUE)
		return NULL_TVALUE;
	DLLNode* currentNode = this->dummy.next;
	while ((*currentNode).next != &this->dummy && (*currentNode).elem.first != c)
	{
		currentNode = (*currentNode).next;
	}
	TValue oldValue = (*currentNode).elem.second;
	(*(*currentNode).next).prev = (*currentNode).prev;
	(*(*currentNode).prev).next = (*currentNode).next;
	return oldValue;
}
//Best case:Theta(1) Worst case: Theta(n) Total: O(n)

int Map::size() const {
	int size = 0;
	DLLNode* currentNode = this->dummy.next;
	while ((*currentNode).next != &this->dummy)
	{
		currentNode = (*currentNode).next;
		size++;
	}
	if (currentNode != &this->dummy)
		size++;
	return size;
}
// Theta(n)

bool Map::isEmpty() const{
	return (dummy.next == &dummy && dummy.prev == &dummy);
}
//Theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}

bool Map::isFull() const
{
	if (this->size() == this->sizeMap)
		return true;
	return false;
}
