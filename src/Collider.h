#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Util.h"

class Player;

class Collider {
public:
	Collider();
	Collider(Vector center, Vector size);
	bool IsColliding(Player& player, Collider other);
	bool IsColliding(Player& player, Rect rect);

private:
	Vector _center;
	Vector _size;
};

#endif