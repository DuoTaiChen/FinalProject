#include "MainScene.h"
#include "Menu.h"
#include "EndScene.h"

enum class Scene
{
	MENU,
	GAME,
	END,
	EXIT
};

Scene state;

void enterMenu() {
	Menu* menu = new Menu();
	while (true) {
		menu->Update();
		if (menu->GetState() == MenuState::GAME) {
			state = Scene::GAME;
			break;
		}
		if (menu->GetState() == MenuState::EXIT) {
			state = Scene::EXIT;
			break;
		}
	}
	delete menu;
}

double enterGame() {
	MainScene* aob = new MainScene();
	while (!aob->IsEnd()) {
		aob->Update();
	}
	double record = aob->GetRecord();
	delete aob;
	state = Scene::END;
	return record;
}

void enterEndScene(double record) {
	EndScene* end = new EndScene(record);
	while (true) {
		end->Update();
		if (end->GetState() == EndState::RESTART) {
			state = Scene::GAME;
			break;
		}
		if (end->GetState() == EndState::MENU) {
			state = Scene::MENU;
			break;
		}
		if (end->GetState() == EndState::EXIT) {
			state = Scene::EXIT;
			break;
		}
	}
	delete end;
}

int main(int argc, char* argv[])
{
	state = Scene::MENU;
	double record=0;
	while (state != Scene::EXIT)
	{
		switch (state)
		{
		case Scene::MENU:
			enterMenu();
			break;
		case Scene::GAME:
			record=enterGame();
			break;
		case Scene::END:
			enterEndScene(record);
			break;
		case Scene::EXIT:
			break;
		default:
			break;
		}
	}
	return 0;
}