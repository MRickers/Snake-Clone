#include "snake.hpp"
#include <GameKit/helpers/Draw.hpp>
#include <GameKit/helpers/GameException.hpp>
#include <spdlog/spdlog.h>

snake::Snake::Snake(const size_t blocksize)
    : m_size{blocksize},
      m_bodyRect{static_cast<float>(m_size - 1), static_cast<float>(m_size - 1)},
      m_snakeSegments{},
      m_direction{snake::Snake::Direction::up},
      m_speed{15},
      m_lives{3}

{
    reset({5, 7});
}

void snake::Snake::update()
{
    if (m_snakeSegments.empty())
    {
        return;
    }
    move();
    if (const auto segmentIndex = checkCollision(); segmentIndex != 0)
    {
        cut(segmentIndex);
        --m_lives;
    }
}

void snake::Snake::draw(SDL_Renderer *renderer)
{
    if (renderer)
    {
        if (!m_snakeSegments.empty())
        {
            gk::Draw::setRendererColor(renderer, gk::Color::GREEN);
            for (const auto &segment : m_snakeSegments)
            {
                const auto segmentPos = segment * m_size;
                gk::Draw::filledRect(renderer, segmentPos, m_bodyRect);
            }

            gk::Draw::setRendererColor(renderer, gk::Color::YELLOW);
            const auto segmentPos = m_snakeSegments.at(0) * m_size;
            gk::Draw::filledRect(renderer, segmentPos, m_bodyRect);
        }
    }
    else
    {
        throw gk::GameException("Invalid renderer", -9000);
    }
}

void snake::Snake::reset(const gk::Vector2D &startPos)
{
    m_snakeSegments.clear();

    m_snakeSegments.push_back(startPos);
    m_snakeSegments.push_back(startPos - gk::Vector2D{0, -1});
    m_snakeSegments.push_back(startPos - gk::Vector2D{0, -2});

    m_direction = Snake::Direction::up;
    m_speed = 15;
    m_lives = 3;
}

void snake::Snake::setHeadPos(const gk::Vector2D &pos)
{
    m_snakeSegments.front() = pos;
}

void snake::Snake::setDirection(const Snake::Direction dir)
{
    m_direction = dir;
}

snake::Snake::Direction snake::Snake::getDirection() const
{
    const auto &head = m_snakeSegments.at(0);
    const auto &neck = m_snakeSegments.at(1);

    if (static_cast<int>(head.GetX()) == static_cast<int>(neck.GetX()))
    {
        return (static_cast<int>(head.GetY() > static_cast<int>(neck.GetY()))) ? Snake::Direction::down : Snake::Direction::up;
    }
    else if (static_cast<int>(head.GetY()) == static_cast<int>(neck.GetY()))
    {
        return (static_cast<int>(head.GetX() > static_cast<int>(neck.GetX()))) ? Snake::Direction::right : Snake::Direction::left;
    }
    throw gk::GameException{"snake invalid direction", -100};
}

size_t snake::Snake::getSpeed() const
{
    return m_speed;
}

snake::SnakeContainer snake::Snake::getSnake() const
{
    return m_snakeSegments;
}

gk::Vector2D snake::Snake::getHeadPos() const
{
    return m_snakeSegments.front();
}

size_t snake::Snake::getLives() const
{
    return m_lives;
}

void snake::Snake::setLives(const size_t lives)
{
    m_lives = lives;
}

void snake::Snake::extend()
{
    if (m_snakeSegments.empty())
    {
        return;
    }

    const auto &[tailHeadX, tailHeadY] = m_snakeSegments.back().Get();

    if (m_snakeSegments.size() > 1)
    {
        auto &tailBone = m_snakeSegments.at(m_snakeSegments.size() - 2);

        const auto &[tailBoneX, tailBoneY] = tailBone.Get();

        if (static_cast<int>(tailHeadX) == static_cast<int>(tailBoneX))
        {
            if (static_cast<int>(tailHeadY) > static_cast<int>(tailBoneY))
            {
                m_snakeSegments.push_back({tailHeadX, tailHeadY + 1});
            }
            else
            {
                m_snakeSegments.push_back({tailHeadX, tailHeadY - 1});
            }
        }
        else if (static_cast<int>(tailHeadY) == static_cast<int>(tailBoneY))
        {
            if (static_cast<int>(tailHeadX) > static_cast<int>(tailBoneX))
            {
                m_snakeSegments.push_back({tailHeadX + 1, tailHeadY});
            }
            else
            {
                m_snakeSegments.push_back({tailHeadX - 1, tailHeadY});
            }
        }
    }
    else
    {
        if (m_direction == Direction::up)
        {
            m_snakeSegments.push_back({tailHeadX, tailHeadY + 1});
        }
        else if (m_direction == Direction::down)
        {
            m_snakeSegments.push_back({tailHeadX, tailHeadY - 1});
        }
        else if (m_direction == Direction::left)
        {
            m_snakeSegments.push_back({tailHeadX + 1, tailHeadY});
        }
        else if (m_direction == Direction::right)
        {
            m_snakeSegments.push_back({tailHeadX - 1, tailHeadY});
        }
    }
}

void snake::Snake::move()
{
    for (int i = m_snakeSegments.size() - 1; i > 0; --i)
    {
        m_snakeSegments[i] = m_snakeSegments[i - 1];
    }

    if (m_direction == Direction::left)
    {
        m_snakeSegments[0] -= {1, 0};
    }
    else if (m_direction == Direction::right)
    {
        m_snakeSegments[0] += {1, 0};
    }
    else if (m_direction == Direction::up)
    {
        m_snakeSegments[0] -= {0, 1};
    }
    else if (m_direction == Direction::down)
    {
        m_snakeSegments[0] += {0, 1};
    }
}

size_t snake::Snake::checkCollision() const
{
    if (m_snakeSegments.size() > 4)
    {
        const auto &[headX, headY] = m_snakeSegments.front().Get();
        for (auto it = m_snakeSegments.begin() + 1; it != m_snakeSegments.end();
             ++it)
        {
            const auto &[x, y] = it->Get();
            if (static_cast<size_t>(x) == static_cast<size_t>(headX) &&
                static_cast<size_t>(y) == static_cast<size_t>(headY))
            {
                return m_snakeSegments.end() - it;
            }
        }
    }
    return 0;
}

void snake::Snake::cut(const size_t segment)
{
    for (int i = 0; i < segment; i++)
    {
        m_snakeSegments.pop_back();
    }
}
