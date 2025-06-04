#ifndef _UNBREAKABLE_BLOCK_INCLUDE
#define _UNBREAKABLE_BLOCK_INCLUDE

#include "StaticObject.h"

class UnbreakableBlock : public StaticObject {
public:
	enum class Color { Blue, Red, Yellow };
	enum class Length { X1, X2, X3, X4 };
	enum class Type { Horizontal, Vertical };

	UnbreakableBlock(TileMap* tilemap, Color color, Length length, Type type);

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void onCollision(GameObject* other) override;

	static int getSpriteRow(Color color, Length length, Type type);

private:
	Color color;
	Length length;
	Type type;

	static Texture spritesheet;
};

#endif // _UNBREAKABLE_BLOCK_INCLUDE
