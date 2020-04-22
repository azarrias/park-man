#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Player.h"

class Controller {
public:
	bool HandleInput(Player& player) const;
};

#endif