#pragma once

#include "raylib.h"
#include "raymath.h"
#include "layer.hpp"
#include "ui.hpp"
#include <vector>


class Grid {
public:
	Grid(int canvasWidth, int canvasHeight);
	~Grid();
	void Draw(Vector2 canvasPos);
	bool HandleInput(Vector2& canvasPos, Tool selectedTool, Color& selectedColor);
	bool DrawPixel(Vector2 canvasPos, Color c);
	int GetPixelWidth();
	int GetPixelHeight();
	Image& getCanvas();
	void Export(const char* filename);
	void Import(const char* filename);
	void Resize(int size);
	void Rotate();
	void Flip();
	void Undo();
	void AddLayer();
	std::vector<Layer>& getLayers();
	int& getActiveLayer();

private:
	std::vector<Layer> layers;
	int canvasWidth;
	int canvasHeight;
	int zoom = 8;
	std::vector<Image> canvasStates;
	int activeLayer = 0;
	Vector2 lineStart = {0, 0};
	bool isDrawingStraightLine = false;
	bool isDrawingRect = false;
	bool isDrawingCircle = false;
};