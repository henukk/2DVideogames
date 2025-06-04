#ifndef _BREAKABLE_BLOCK_INCLUDE
#define _BREAKABLE_BLOCK_INCLUDE

#include "StaticObject.h"

class BreakableBlock : public StaticObject {
public:
	enum class Color { Blue, Red, Yellow };
	enum class Length { X1, X2, X3, X4 };
	enum class Type { Horizontal, Vertical };

	BreakableBlock(TileMap* tilemap, Color color, Length length, Type type);

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void onCollision(GameObject* other) override;

	static int getSpriteRow(Color color, Length length, Type type);
	void setAnimations(float texY);

	void breakBlock();
	bool isBreaked();

private:
	Color color;
	Length length;
	Type type;

	static Texture spritesheet;
};

#endif // _BREAKABLE_BLOCK_INCLUDE
