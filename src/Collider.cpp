#include "Collider.h"
#include "Player.h"

Collider::Collider()
{}

Collider::Collider(Vector center, Vector size)
: _center(center), _size(size)
{}

bool Collider::IsColliding(Player& player, Collider other) {
	return false;
}

bool Collider::IsColliding(Player& player, Rect rect) {
	// AABB collision detection
	if (player._pos.y + _center.y + _size.y / 2 <= rect.y)
		return false;
	if (player._pos.y + _center.y - _size.y / 2 >= rect.y + rect.h)
		return false;
	if (player._pos.x + _center.x + _size.x / 2 <= rect.x)
		return false;
	if (player._pos.x + _center.x - _size.x / 2 >= rect.x + rect.w)
		return false;

	return true;
}
