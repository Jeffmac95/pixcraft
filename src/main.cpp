#include "raylib.h"
#include "grid.hpp"
#include "ui.hpp"


int main() {
	InitWindow(800, 600, "Pixcraft");

	Grid grid(64, 64);
	Vector2 canvasPos = { 
		(GetScreenWidth() - grid.GetPixelWidth()) / 2.0f,
		(GetScreenHeight() - grid.GetPixelHeight()) / 2.0f
	};
	UI ui;

	while (!WindowShouldClose()) {
		if (grid.HandleInput(canvasPos, ui.getSelectedTool(), ui.getSelectedColor())) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				ui.addPrevColor(ui.getSelectedColor());
			}
		}

		if (ui.getisSavePressed()) {
			grid.Export(ui.getExportFilename());
			ui.setisSavePressed(false);
		}

		if (ui.getisImportPressed()) {
			grid.Import(ui.getImportFilename());
			ui.setisImportPressed(false);

			canvasPos = {
				(GetScreenWidth() - grid.GetPixelWidth()) / 2.0f,
				(GetScreenHeight() - grid.GetPixelHeight()) / 2.0f
			};
		}

		if (ui.getisResizeBtnPressed()) {
			grid.Resize(ui.parseCurrentCanvasSize());
			ui.setisResizeBtnPressed(false);

			canvasPos = {
				(GetScreenWidth() - grid.GetPixelWidth()) / 2.0f,
				(GetScreenHeight() - grid.GetPixelHeight()) / 2.0f
			};
		}

		if (ui.getisRotateBtnPressed()) {
			grid.Rotate();
			ui.setisRotateBtnPressed(false);
		}

		if (ui.getisFlipBtnPressed()) {
			grid.Flip();
			ui.setisFlipBtnPressed(false);
		}
		
		if (ui.getisAddLayerBtnPressed()) {
			
			grid.AddLayer();
			ui.setisAddLayerBtnPressed(false);
		}

		if (IsKeyPressed(KEY_Z) && IsKeyDown(KEY_LEFT_CONTROL)) {
			grid.Undo();
		}

		BeginDrawing();
			ClearBackground({30, 30, 30, 255});
			grid.Draw(canvasPos);
			ui.Draw();
			if (ui.getisPrevColorBtnSelected()) {
				ui.DrawPrevColors();
			}
			ui.DrawMiniLayers(grid.getLayers(), grid.getActiveLayer());

		EndDrawing();
	}

	CloseWindow();
	return 0;
}