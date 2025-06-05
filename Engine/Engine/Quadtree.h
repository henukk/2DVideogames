#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace stdExtension {

    template <typename T, typename TCoord>
    class Quadtree {
    private:
        static constexpr int MAX_OBJECTS = 4;
        static constexpr int MAX_LEVELS = 5;

        enum QuadtreeDivisions {
            TOP_LEFT = 0,
            TOP_RIGHT = 1,
            BOT_LEFT = 2,
            BOT_RIGHT = 3
        };

        using Vec2 = glm::vec<2, TCoord>;

        struct Node {
            int level;
            Vec2 topLeft;
            Vec2 size;
            std::vector<T> objects;
            std::unique_ptr<Node> children[4];

            Node(int level, Vec2 topLeft, Vec2 size)
                : level(level), topLeft(topLeft), size(size) {
            }

            bool hasChildren() const {
                return children[0] != nullptr;
            }

            Vec2 bottomRight() const {
                return topLeft + size;
            }
        };

    public:
        Quadtree(Vec2 topLeft, Vec2 size)
            : root(std::make_unique<Node>(0, topLeft, size)) {
        }

        void insert(const T& object) {
            insert(root.get(), object);
        }

        std::vector<T> query(const Vec2& pos, const Vec2& size) const {
            std::vector<T> result;
            query(root.get(), pos, size, result);
            return result;
        }

    private:
        std::unique_ptr<Node> root;

        void insert(Node* node, const T& object) {
            Vec2 objPos = object.getPosition();
            Vec2 objSize = object.getSize();

            if (!fitsInside(objPos, objSize, node->topLeft, node->size))
                return;

            if (node->hasChildren()) {
                int index = getChildIndex(node, objPos, objSize);
                if (index != -1) {
                    insert(node->children[index].get(), object);
                    return;
                }
            }

            node->objects.push_back(object);

            if (node->objects.size() > MAX_OBJECTS && node->level < MAX_LEVELS) {
                subdivide(node);
                auto objs = std::move(node->objects);
                node->objects.clear();

                for (const auto& obj : objs) {
                    insert(node, obj);
                }
            }
        }

        bool fitsInside(const Vec2& pos, const Vec2& size,
            const Vec2& topLeft, const Vec2& areaSize) const {
            return pos.x >= topLeft.x &&
                pos.y >= topLeft.y &&
                pos.x + size.x <= topLeft.x + areaSize.x &&
                pos.y + size.y <= topLeft.y + areaSize.y;
        }

        void subdivide(Node* node) {
            Vec2 halfSize = node->size * static_cast<TCoord>(0.5);
            node->children[TOP_LEFT] = std::make_unique<Node>(node->level + 1, node->topLeft, halfSize);
            node->children[TOP_RIGHT] = std::make_unique<Node>(node->level + 1,
                node->topLeft + Vec2(halfSize.x, 0), halfSize);
            node->children[BOT_LEFT] = std::make_unique<Node>(node->level + 1,
                node->topLeft + Vec2(0, halfSize.y), halfSize);
            node->children[BOT_RIGHT] = std::make_unique<Node>(node->level + 1,
                node->topLeft + halfSize, halfSize);
        }

        int getChildIndex(Node* node, const Vec2& pos, const Vec2& size) const {
            TCoord halfWidth = node->size.x / 2;
            TCoord halfHeight = node->size.y / 2;

            bool top = pos.y + size.y <= node->topLeft.y + halfHeight;
            bool bottom = pos.y >= node->topLeft.y + halfHeight;
            bool left = pos.x + size.x <= node->topLeft.x + halfWidth;
            bool right = pos.x >= node->topLeft.x + halfWidth;

            if (top) {
                if (left)  return TOP_LEFT;
                if (right) return TOP_RIGHT;
            }
            else if (bottom) {
                if (left)  return BOT_LEFT;
                if (right) return BOT_RIGHT;
            }

            return -1;
        }

        void query(const Node* node, const Vec2& pos, const Vec2& size, std::vector<T>& result) const {
            if (!intersects(pos, size, node->topLeft, node->size))
                return;

            for (const auto& obj : node->objects) {
                Vec2 objPos = obj.getPosition();
                Vec2 objSize = obj.getSize();

                if (intersects(pos, size, objPos, objSize))
                    result.push_back(obj);
            }

            if (node->hasChildren()) {
                for (int i = 0; i < 4; ++i)
                    query(node->children[i].get(), pos, size, result);
            }
        }

        bool intersects(const Vec2& aPos, const Vec2& aSize,
            const Vec2& bPos, const Vec2& bSize) const {
            return !(aPos.x + aSize.x <= bPos.x || aPos.x >= bPos.x + bSize.x ||
                aPos.y + aSize.y <= bPos.y || aPos.y >= bPos.y + bSize.y);
        }
    };

} // namespace stdExtension

#endif // _QUADTREE_H_
