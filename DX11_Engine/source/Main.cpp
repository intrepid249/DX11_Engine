#include <Windows.h>

#include "engine/Engine.h"
#include <memory>

using namespace TrepiCoder;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	std::shared_ptr<Engine> app = std::shared_ptr<Engine>(new Engine());
	app->initialize(hInstance, "Hello", "MyWindowClass", 800, 600);

	while (app->pollEventMessages()) {
		app->update();
		app->render();
	}

	return EXIT_SUCCESS;
}