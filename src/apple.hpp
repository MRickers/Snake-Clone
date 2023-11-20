#pragma once
#include <GameKit/vector/Vector2d.hpp>
#include <stddef.h>

class SDL_Renderer;

namespace snake
{
    class Snake;

}

namespace snake
{
    class Apple
    {
    public:
        Apple(size_t blockSize, int minPos = 0, int maxXPos = 5, int maxYPos = 5);

        gk::Vector2D getPosition() const;
        void resetPosition(const snake::Snake *);
        void draw(SDL_Renderer *);
        void setMinMax(int min, int maxX, int maxY);

    private:
        gk::Vector2D spawnNew();

        size_t m_blockSize;
        int m_min, m_maxX, m_maxY;
        gk::Vector2D m_pos;
    };

} // namespace snake
