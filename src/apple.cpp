#include "apple.hpp"
#include <random>
#include <cmath>

#include "snake.hpp"
#include <GameKit/helpers/Draw.hpp>

snake::Apple::Apple(size_t blockSize, int minPos, int maxXPos, int maxYPos) : m_blockSize{blockSize},
                                                                              m_min{minPos},
                                                                              m_maxX{maxXPos},
                                                                              m_maxY{maxYPos},
                                                                              m_pos{0, 0}
{
}

gk::Vector2D snake::Apple::getPosition() const
{
    return m_pos;
}

void snake::Apple::resetPosition(const snake::Snake *snake)
{
    bool collide = true;
    while (collide)
    {
        const auto newPos = spawnNew();
        collide = false;

        for (const auto &segment : snake->getSnake())
        {
            if (static_cast<int>(newPos.GetX()) == static_cast<int>(segment.GetX()) &&
                static_cast<int>(newPos.GetY()) == static_cast<int>(segment.GetY()))
            {
                collide = true;
                break;
            }
        }
        m_pos = newPos;
    }
}

void snake::Apple::draw(SDL_Renderer *renderer)
{
    gk::Draw::setRendererColor(renderer, gk::Color::RED);
    const auto &[x, y] = m_pos.Get();

    gk::Draw::filledCircle(renderer,
                           static_cast<int>(x) * m_blockSize + m_blockSize / 2,
                           static_cast<int>(y) * m_blockSize + m_blockSize / 2,
                           m_blockSize / 2);
}

gk::Vector2D snake::Apple::spawnNew()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distributionX(m_min, m_maxX);
    std::uniform_int_distribution<int> distributionY(m_min, m_maxY);

    return {static_cast<float>(distributionX(gen)), static_cast<float>(distributionY(gen))};
}

void snake::Apple::setMinMax(int min, int maxX, int maxY)
{
    m_min = min;
    m_maxX = maxX;
    m_maxY = maxY;
}