#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <GLFW/glfw3.h>
#include <memory>
#include "Scene.h"
#include "AudioManager.h"


class Game
{
private:
	Game();

public:
	static Game& instance();

	void init();
	bool update(int deltaTime);
	void render();
	void shutdown();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;

private:
	bool bPlay;
	bool keys[GLFW_KEY_LAST + 1];

	std::unique_ptr<Scene> scene;
};

#endif // _GAME_INCLUDE
