#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& m) : map(m)
{
	currentNode = m.dummy.next;
}
//Theta(1)

void MapIterator::first() {
	currentNode = map.dummy.next;
}
//Theta(1)

void MapIterator::next() {
	if (currentNode == &map.dummy)
		throw exception();
	currentNode = currentNode->next;
}
//Theta(1)

TElem MapIterator::getCurrent(){
	if (currentNode == &map.dummy)
		throw exception();
	return currentNode->elem;
}
//Theta(1)

bool MapIterator::valid() const {
	return currentNode != &map.dummy;
}
//Theta(1)


