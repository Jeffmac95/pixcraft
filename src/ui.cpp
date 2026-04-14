#define RAYGUI_IMPLEMENTATION
#include "ui.hpp"


UI::UI() {}

void UI::Draw() {
	if (GuiDropdownBox(resizeDropdown, "32x32;64x64;128x128", &selectedCanvasSize, isCanvasSizeDropdownOpen)) isCanvasSizeDropdownOpen = !isCanvasSizeDropdownOpen;
	if (GuiButton(resizeBtn, "Resize")) isResizeBtnPressed = true;
	GuiLabel(toolsLabel, "TOOLS");
	if (GuiButton(pencilBtn, "#23#")) selectedTool = TOOL_PENCIL;
	if (GuiButton(eraserBtn, "#28#")) selectedTool = TOOL_ERASER;
	if (GuiButton(colorPickBtn, "#27#")) selectedTool = TOOL_COLORPICKER;
	if (GuiButton(nukeBtn, "#143#")) selectedTool = TOOL_NUKE;
	if (GuiButton(straightLineBtn, "#63#")) selectedTool = TOOL_STRAIGHTLINE;
	GuiButton(fillBtn, "#29#");
	GuiButton(drawRectBtn, "#133#");
	GuiButton(drawCircleBtn, "#135#");
	GuiLabel(transformLabel, "TRANSFORM");
	if (GuiButton(flipBtn, "#39#")) isFlipBtnPressed = true;
	if (GuiButton(rotateBtn, "#72#")) isRotateBtnPressed = true;
	if (GuiTextBox(inputHexTextArea, hexInput, fontSize, hexEditMode)) {
		hexEditMode = !hexEditMode;
		if (!hexEditMode) {
			parseHex();
		}
	}
	GuiLabel(colorLabel, TextFormat("R:%d G:%d B:%d", selectedColor.r, selectedColor.g, selectedColor.b));
	DrawRectangle(currentColorX, currentColorY, colorRectSize, colorRectSize, selectedColor);
	GuiColorPicker(colorPicker, "Select color", &selectedColor);
	if (GuiButton(prevColorBtn, "Select prev colors")) isPrevColorBtnSelected = !isPrevColorBtnSelected;
	if (GuiTextBox(exportInputArea, exportInput, fontSize, exportInputEditMode)) exportInputEditMode = !exportInputEditMode;
	if (GuiTextBox(importInputArea, importInput, fontSize, importInputEditMode)) importInputEditMode = !importInputEditMode;
	if (GuiButton(exportBtn, "#2#")) isSavePressed = true;
	if (GuiButton(importBtn, "#3#")) isImportPressed = true;
	if (GuiButton(addLayerBtn, "#8#")) isAddLayerBtnPressed = true;
}

void UI::DrawPrevColors() {
	DrawRectangleLines(prevColorsX, prevColorsY, prevColorsWidth, prevColorsHeight, BLACK);
	int x = 155;
	int y = 565;
	int offset = 10;
	for (int i = 0; i < prevColors.size(); i++) {
		Rectangle colorRect = { (float)x, (float)y, (float)colorRectSize, (float)colorRectSize };
		DrawRectangleRec(colorRect, prevColors[i]);
		
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
			CheckCollisionPointRec(GetMousePosition(), colorRect)) {
			selectedColor = prevColors[i];
		}

		x += colorRectSize + offset;
	}
}

void UI::addPrevColor(Color c) {
	for (int i = 0; i < prevColors.size(); i++) {
		if (ColorIsEqual(prevColors[i], c)) return;
	}

	if (prevColors.size() >= 10) {
		prevColors.erase(prevColors.begin());
	}
	prevColors.push_back(c);
}

void UI::parseHex() {
	if (hexInput[0] != '#' || strlen(hexInput) != 7) return;

	long value = strtol(hexInput + 1, nullptr, 16);
	value = (value << 8) | 0xFF;
	selectedColor = GetColor(value);
}

int UI::parseCurrentCanvasSize() {
	if (selectedCanvasSize == 0) return 32;
	else if (selectedCanvasSize == 2) return 128;
	else return 64;
}

void UI::DrawMiniLayers(std::vector<Layer>& layers, int& activeLayer) {
	int x = 710;
	int y = 80;
	int miniLayerSize = 80;
	int offset = 10;
	for (int i = 0; i < layers.size(); i++) {

		Rectangle miniLayer = { (float)x, (float)y + i * (miniLayerSize + offset), (float)miniLayerSize, (float)miniLayerSize };

		DrawRectangleRec(miniLayer, i == activeLayer ? Fade(YELLOW, 0.5f) : Fade(LIGHTGRAY, 0.5f));

		DrawTexturePro(
			layers[i].texture,
			{ 0, 0, (float)layers[i].image.width, (float)layers[i].image.height },
			miniLayer,
			{ 0, 0 },
			0,
			WHITE
		);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
			CheckCollisionPointRec(GetMousePosition(), miniLayer)) {
			activeLayer = i;
		}
	}
}

Tool UI::getSelectedTool() { return selectedTool; }
Color& UI::getSelectedColor() { return selectedColor; }
bool UI::getisPrevColorBtnSelected() { return isPrevColorBtnSelected; }
bool UI::getisSavePressed() { return isSavePressed; }
bool UI::getisImportPressed() { return isImportPressed; }
bool UI::getisResizeBtnPressed() { return isResizeBtnPressed; }
bool UI::getisRotateBtnPressed() { return isRotateBtnPressed; }
bool UI::getisFlipBtnPressed() { return isFlipBtnPressed; }
bool UI::getisAddLayerBtnPressed() { return isAddLayerBtnPressed; }
void UI::setisResizeBtnPressed(bool isSet) { isResizeBtnPressed = isSet; }
void UI::setisSavePressed(bool isSet) { isSavePressed = isSet; }
void UI::setisImportPressed(bool isSet) { isImportPressed = isSet; }
void UI::setisRotateBtnPressed(bool isSet) { isRotateBtnPressed = isSet; }
void UI::setisFlipBtnPressed(bool isSet) { isFlipBtnPressed = isSet; }
void UI::setisAddLayerBtnPressed(bool isSet) { isAddLayerBtnPressed = isSet; }