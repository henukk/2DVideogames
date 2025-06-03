#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Config.h"


Scene::Scene()
{
	map = NULL;
	player = NULL;
	backgroundSprite = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if(backgroundSprite != NULL)
		delete backgroundSprite;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap(TILEMAP, texProgram);

	if (BACKGROUND != NULL) {
		if (!spritesheet.loadFromFile(BACKGROUND, TEXTURE_PIXEL_FORMAT_RGB)) {
			cout << "Error loading bacground image" << endl;
		}
		backgroundSprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &spritesheet, &texProgram);
		backgroundSprite->setPosition(glm::vec2(0.f, 0.f));
	}

	player = new Player();
	player->init(glm::ivec2(0, 0), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * TILE_SIZE, INIT_PLAYER_Y_TILES * TILE_SIZE));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (BACKGROUND != NULL) {
		backgroundSprite->update(deltaTime);
	}
	player->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	if (BACKGROUND != NULL) {
		backgroundSprite->render();
	}
	map->render();
	player->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



