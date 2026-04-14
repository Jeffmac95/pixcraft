#pragma once

#include "raylib.h"
#include <string>

struct Layer {
	Image image;
	Texture2D texture;
	float opacity;
	std::string name;
	bool isVisible;
};