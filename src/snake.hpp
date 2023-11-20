#pragma once
#include <cstddef>
#include <functional>
#include <vector>
#include <GameKit/vector/Vector2d.hpp>

class SDL_Renderer;
namespace snake
{
    using SnakeContainer = std::vector<gk::Vector2D>;
    class Snake
    {
    public:
        enum class Direction
        {
            up,
            down,
            left,
            right
        };

        using ScoreCallback = std::function<void(const size_t score)>;

        Snake(const size_t blocksize = 16);

        void update();
        void draw(SDL_Renderer *);

        void reset(const gk::Vector2D &startPos);

        void setHeadPos(const gk::Vector2D &pos);
        void setDirection(const Snake::Direction);
        void setLives(const size_t lives);

        gk::Vector2D getHeadPos() const;
        Direction getDirection() const;
        size_t getLives() const;
        size_t getSpeed() const;
        SnakeContainer getSnake() const;

        void extend();

    private:
        size_t m_size;
        gk::Vector2D m_bodyRect;
        SnakeContainer m_snakeSegments;
        Direction m_direction{Direction::right};
        size_t m_speed;
        size_t m_lives;

        void move();
        size_t checkCollision() const;
        void cut(const size_t segment);
    };
} // namespace snake
