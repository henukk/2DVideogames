#ifndef _LEVEL_DATA_INCLUDE
#define _LEVEL_DATA_INCLUDE

#include <vector>
#include <glm/glm.hpp>

struct TileEntry {
    enum class TileType { Breakable, Unbreakable };
    enum class BlockColor { Blue, Red, Yellow };
    enum class BlockLength { X1, X2, X3, X4 };
    enum class BlockType { Horizontal, Vertical };

    TileType type;
    BlockColor color;
    BlockLength length;
    BlockType orientation;
    glm::ivec2 position;
};

class LevelData {
public:
    void addTile(const TileEntry& entry);
    const std::vector<TileEntry>& getTiles() const;

private:
    std::vector<TileEntry> tiles;
};

inline void LevelData::addTile(const TileEntry& entry) {
    tiles.push_back(entry);
}

inline const std::vector<TileEntry>& LevelData::getTiles() const {
    return tiles;
}

#endif // _LEVEL_DATA_INCLUDE
