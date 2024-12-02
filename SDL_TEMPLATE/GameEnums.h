#pragma once
#include <iostream>
#include "SDL.h"

using Dimension = SDL_Point;

constexpr Dimension ENTITY_DIMENSION = { 45, 65 };
constexpr int BORDER_ALLOWANCE = 12;

enum class Face_Direction {
	LEFT,
	UP_LEFT,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT
};

enum class Prototype_Type {
	PLAYER,
	BULLET,
	SMALL_ENEMY,
};

std::string getProtoType_Type_Path(Prototype_Type type);