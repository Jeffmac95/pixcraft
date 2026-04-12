#include "grid.hpp"
#include <string>


Grid::Grid(int canvasWidth, int canvasHeight) {
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;

	Layer baseLayer;
	baseLayer.image = GenImageColor(canvasWidth, canvasHeight, BLANK);
	baseLayer.texture = LoadTextureFromImage(baseLayer.image);
	baseLayer.opacity = 1.0f;
	baseLayer.name = "Layer 0";
	baseLayer.isVisible = true;
	layers.push_back(baseLayer);
}

Grid::~Grid() {
	for (Layer& l : layers) {
		UnloadImage(l.image);
		UnloadTexture(l.texture);
	}
	for (Image& i : canvasStates) UnloadImage(i);
}

void Grid::Draw(Vector2 canvasPos) {
	DrawRectangle(canvasPos.x, canvasPos.y, canvasWidth * zoom, canvasHeight * zoom, GRAY);

	for (int i = 0; i < layers.size(); i++) {
		if (layers[i].isVisible) {
			float opacity = (i == activeLayer) ? 1.0f : 0.4f;
			Color tint = Fade(WHITE, opacity);
			DrawTextureEx(layers[i].texture, canvasPos, 0, zoom, tint);
		}
	}

	for (int y = 0; y < canvasHeight; y++) {
		for (int x = 0; x < canvasWidth; x++) {
			DrawRectangleLines(canvasPos.x + x * zoom, canvasPos.y + y * zoom, zoom, zoom, LIGHTGRAY);
		}
	}
}

bool Grid::HandleInput(Vector2& canvasPos, Tool selectedTool, Color selectedColor) {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (canvasStates.size() >= 10) {
			UnloadImage(canvasStates.front());
			canvasStates.erase(canvasStates.begin());
		}
		canvasStates.push_back(ImageCopy(layers[activeLayer].image));
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Color c = selectedTool == TOOL_ERASER ? BLANK : selectedColor;
		return DrawPixel(canvasPos, c);
	}

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
		return DrawPixel(canvasPos, BLANK);
	}
	
	if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
		Vector2 delta = GetMouseDelta();
		canvasPos.x += delta.x;
		canvasPos.y += delta.y;
	}

	float wheel = GetMouseWheelMove();
	if (wheel != 0) {
		int oldZoom = zoom;

		if (wheel > 0) zoom++;
		else if (wheel < 0) zoom--;

		if (zoom < 1) zoom = 1;
		if (zoom > 32) zoom = 32;

		// zoom on mouse pos
		if (zoom != oldZoom) {
			Vector2 mousePos = GetMousePosition();
			canvasPos = {
				mousePos.x - (mousePos.x - canvasPos.x) * ((float)zoom / oldZoom),
				mousePos.y - (mousePos.y - canvasPos.y) * ((float)zoom / oldZoom)
			};
		}
	}

	return false;
}

bool Grid::DrawPixel(Vector2 canvasPos, Color c) {
	int canvasX = (GetMouseX() - canvasPos.x) / zoom;
	int canvasY = (GetMouseY() - canvasPos.y) / zoom;

	if (canvasX >= 0 && canvasX < canvasWidth && canvasY >= 0 && canvasY < canvasHeight) {
		ImageDrawPixel(&layers[activeLayer].image, canvasX, canvasY, c);
		UpdateTexture(layers[activeLayer].texture, layers[activeLayer].image.data);
		return true;
	}

	return false;
}

void Grid::Export(const char* filename) {
	ExportImage(layers[activeLayer].image, TextFormat("%s.png", filename));
}

void Grid::Import(const char* filename) {
	Image imported = LoadImage(filename);
	if (!IsImageValid(imported)) return;

	canvasStates.push_back(ImageCopy(layers[activeLayer].image));

	UnloadImage(layers[activeLayer].image);
	layers[activeLayer].image = imported;
	canvasWidth = layers[activeLayer].image.width;
	canvasHeight = layers[activeLayer].image.height;

	UnloadTexture(layers[activeLayer].texture);
	layers[activeLayer].texture = LoadTextureFromImage(layers[activeLayer].image);
}

void Grid::Resize(int size) {
	if (size == canvasWidth && size == canvasHeight) return;


	UnloadImage(layers[activeLayer].image);
	UnloadTexture(layers[activeLayer].texture);

	canvasWidth = size;
	canvasHeight = size;

	layers[activeLayer].image = GenImageColor(canvasWidth, canvasHeight, BLANK);
	layers[activeLayer].texture = LoadTextureFromImage(layers[activeLayer].image);
}

void Grid::Rotate() {
	ImageRotateCW(&layers[activeLayer].image);
	UpdateTexture(layers[activeLayer].texture, layers[activeLayer].image.data);
}

void Grid::Flip() {
	ImageFlipHorizontal(&layers[activeLayer].image);
	UpdateTexture(layers[activeLayer].texture, layers[activeLayer].image.data);
}

void Grid::Undo() {
	if (canvasStates.empty()) return;
	UnloadImage(layers[activeLayer].image);
	layers[activeLayer].image = ImageCopy(canvasStates.back());
	UnloadImage(canvasStates.back());
	canvasStates.pop_back();
	UpdateTexture(layers[activeLayer].texture, layers[activeLayer].image.data);
}

void Grid::AddLayer() {
	if (layers.size() >= 5) return;
	
	Layer newLayer;
	newLayer.image = GenImageColor(canvasWidth, canvasHeight, BLANK);
	newLayer.texture = LoadTextureFromImage(newLayer.image);
	newLayer.opacity = 1.0f;
	newLayer.name = "Layer + " + std::to_string(layers.size());
	newLayer.isVisible = true;
	layers.push_back(newLayer);

	activeLayer = layers.size() - 1;
}

int Grid::GetPixelWidth() { return canvasWidth * zoom; }
int Grid::GetPixelHeight() { return canvasHeight * zoom; }
Image& Grid::getCanvas() { return layers[activeLayer].image; }
std::vector<Layer>& Grid::getLayers() { return layers; }
int& Grid::getActiveLayer() { return activeLayer; }