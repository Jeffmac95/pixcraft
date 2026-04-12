#pragma once

#include "raylib.h"
#include "raygui.h"
#include "layer.hpp"
#include <vector>


enum Tool {
	TOOL_PENCIL,
	TOOL_ERASER
};

class UI {
public:
	UI();
	void Draw();
	void DrawPrevColors();
	Tool getSelectedTool();
	Color getSelectedColor();
	bool getisPrevColorBtnSelected();
	bool getisSavePressed();
	bool getisImportPressed();
	bool getisResizeBtnPressed();
	bool getisRotateBtnPressed();
	bool getisFlipBtnPressed();
	bool getisAddLayerBtnPressed();
	void setisSavePressed(bool isSet);
	void setisImportPressed(bool isSet);
	void setisResizeBtnPressed(bool isSet);
	void setisRotateBtnPressed(bool isSet);
	void setisFlipBtnPressed(bool isSet);
	void setisAddLayerBtnPressed(bool isSet);
	void addPrevColor(Color c);
	void parseHex();
	int parseCurrentCanvasSize();
	const char* getExportFilename() { return exportInput; };
	const char* getImportFilename() { return importInput; };
	void DrawMiniLayers(std::vector<Layer>& layers, int& activeLayer);

private:
	Tool selectedTool = TOOL_PENCIL;
	Color selectedColor = BLACK;
	Color lastColor = selectedColor;
	Rectangle resizeDropdown = { 10.0f, 10.0f, 80.0f, 30.0f };
	Rectangle resizeBtn = { 100.0f, 10.0f, 50.0f, 30.0f };
	bool isResizeBtnPressed = false;
	Rectangle toolsLabel = { 10.0f, 120.0f, 100.0f, 30.0f };
	Rectangle pencilBtn = { 10.0f, 140.0f, 50.0f, 30.0f };
	Rectangle eraserBtn = { 70.0f, 140.0f, 50.0f, 30.0f };
	Rectangle transformLabel = { 10.0f, 240.0f, 100.0f, 30.0f };
	Rectangle flipBtn = { 10.0f, 260.0f, 50.0f, 30.0f };
	Rectangle rotateBtn = { 70.0f, 260.0f, 50.0f, 30.0f };
	Rectangle exportInputArea = { 10.0f, 300.0f, 80.0f, 30.0f };
	Rectangle importInputArea = { 10.0f, 340.0f, 80.0f, 30.0f };
	Rectangle exportBtn = { 95.0f, 300.0f, 30.0f, 30.0f };
	Rectangle importBtn = { 95.0f, 340.0f, 30.0f, 30.0f };
	bool isSavePressed = false;
	bool isImportPressed = false;
	char exportInput[32] = "sprite";
	bool exportInputEditMode = false;
	char importInput[32] = "path";
	bool importInputEditMode = false;
	char hexInput[16] = "#000000";
	bool hexEditMode = false;
	int fontSize = 16;
	Rectangle inputHexTextArea = { 10.0f, 380.0f, 80.0f, 30.0f };
	Rectangle colorLabel = { 10.0f, 420.0f, 100.0f, 30.0f };
	int currentColorX = 110;
	int currentColorY = 420;
	int colorRectSize = 20;
	Rectangle colorPicker = { 10.0f, 450.0f, 100.0f, 100.0f };
	Rectangle prevColorBtn = { 10.0f, 560.0f, 130.0f, 30.0f };
	int prevColorsX = 145;
	int prevColorsY = 560;
	int prevColorsWidth = 310;
	int prevColorsHeight = 30;
	std::vector<Color> prevColors;
	bool isPrevColorBtnSelected = false;
	int selectedCanvasSize = 1;
	bool isCanvasSizeDropdownOpen = false;
	bool isRotateBtnPressed = false;
	bool isFlipBtnPressed = false;
	Rectangle addLayerBtn = { 765.0f, 10.0f, 35.0f, 35.0f };
	bool isAddLayerBtnPressed = false;
};