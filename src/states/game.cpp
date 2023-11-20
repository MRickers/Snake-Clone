#include "states/game.hpp"
#include "game.hpp"
#include "apple.hpp"
#include <GameKit/helpers/Draw.hpp>

namespace snake
{
    static constexpr auto blockSize = 16;

    GameState::GameState(gk::SharedContextPtr sharedContext) : m_ctx{sharedContext},
                                                               m_snake{blockSize},
                                                               m_timer{},
                                                               m_bounds{m_ctx->app->getWindowSize() / blockSize},
                                                               m_apple{blockSize}
    {
        const auto &[x, y] = m_ctx->app->getWindowSize().Get();
        m_bounds = {x * .62f / blockSize, y / blockSize};
        m_apple.setMinMax(1, static_cast<int>(m_bounds.GetX()) - 2, static_cast<int>(m_bounds.GetY()) - 2);
    }

    void GameState::onCreate()
    {
        m_snake.reset(m_ctx->app->getWindowSize() / 2 / 16);
        m_apple.resetPosition(&m_snake);

        {
            auto binding = gk::EventBinding{.id = "turnLeft"};
            binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_A});
            m_ctx->inputHandler->AddBinding(StateType::GAME, binding);
            m_ctx->inputHandler->AddCallback(StateType::GAME, "turnLeft", [&](const gk::EventDetails &)
                                             {
                const auto currentDirection = m_snake.getDirection();
                if(currentDirection != Snake::Direction::right){
                    m_snake.setDirection(Snake::Direction::left);
                } });
        }

        {
            auto binding = gk::EventBinding{.id = "turnRight"};
            binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_D});
            m_ctx->inputHandler->AddBinding(StateType::GAME, binding);
            m_ctx->inputHandler->AddCallback(StateType::GAME, "turnRight", [&](const gk::EventDetails &)
                                             {
                const auto currentDirection = m_snake.getDirection();
                if(currentDirection != Snake::Direction::left){
                    m_snake.setDirection(Snake::Direction::right);
                } });
        }
        {
            auto binding = gk::EventBinding{.id = "turnUp"};
            binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_W});
            m_ctx->inputHandler->AddBinding(StateType::GAME, binding);
            m_ctx->inputHandler->AddCallback(StateType::GAME, "turnUp", [&](const gk::EventDetails &)
                                             {
                const auto currentDirection = m_snake.getDirection();
                if(currentDirection != Snake::Direction::down){
                    m_snake.setDirection(Snake::Direction::up);
                } });
        }
        {
            auto binding = gk::EventBinding{.id = "turnDown"};
            binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_S});
            m_ctx->inputHandler->AddBinding(StateType::GAME, binding);
            m_ctx->inputHandler->AddCallback(StateType::GAME, "turnDown", [&](const gk::EventDetails &)
                                             {
                const auto currentDirection = m_snake.getDirection();
                if(currentDirection != Snake::Direction::up){
                    m_snake.setDirection(Snake::Direction::down);
                } });
        }
        {
            auto binding = gk::EventBinding{.id = "pause"};
            binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_P});
            m_ctx->inputHandler->AddBinding(StateType::GAME, binding);
            m_ctx->inputHandler->AddCallback(StateType::GAME, "pause", [&](const gk::EventDetails &)
                                             {
                m_ctx->stateMachine->switchTo(StateType::PAUSED);
                m_ctx->inputHandler->setCurrentState(StateType::PAUSED); });
        }

        m_timer.Start();
    }

    void GameState::onDestroy()
    {
    }

    void GameState::activate()
    {
    }

    void GameState::deactivate()
    {
    }

    void GameState::update()
    {
        if (m_timer.HasPassed(200))
        {
            m_snake.update();

            checkWorldBounds();

            const auto &[snake_x, snake_y] = m_snake.getHeadPos().Get();
            const auto &[apple_x, apple_y] = m_apple.getPosition().Get();

            if (static_cast<int>(snake_x) == static_cast<int>(apple_x) &&
                static_cast<int>(snake_y) == static_cast<int>(apple_y))
            {
                m_snake.extend();
                m_apple.resetPosition(&m_snake);
            }

            m_timer.Reset();
        }
    }

    void GameState::draw(SDL_Renderer *renderer)
    {
        m_snake.draw(renderer);
        m_apple.draw(renderer);
        renderBounds(renderer);
    }

    void GameState::checkWorldBounds()
    {
        const auto &[x_pos, y_pos] = m_snake.getHeadPos().Get();

        if (x_pos <= 0 ||
            x_pos >= static_cast<int>(m_bounds.GetX()) - 1 ||
            y_pos <= 0 ||
            y_pos >= static_cast<int>(m_bounds.GetY()) - 1)
        {
            m_snake.reset({15, 15});
            m_snake.setDirection(Snake::Direction::up);
        }
    }

    void GameState::renderBounds(SDL_Renderer *renderer)
    {
        const auto &[size_x, size_y] = m_bounds.Get();

        gk::Draw::setRendererColor(renderer, gk::Color::MAROON);

        bool draw = false;
        for (int i = 0; i < static_cast<int>(size_x); i++)
        {
            for (int j = 0; j < static_cast<int>(size_y); j++)
            {
                if (i == 0 ||
                    j == 0 ||
                    i == static_cast<int>(size_x) - 1 ||
                    j == static_cast<int>(size_y) - 1)
                {
                    gk::Draw::filledRect(renderer,
                                         {static_cast<float>(i) * blockSize, static_cast<float>(j) * blockSize},
                                         {blockSize - 1, blockSize - 1});
                }
            }
        }
    }
} // snake
