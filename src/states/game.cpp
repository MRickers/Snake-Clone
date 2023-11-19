#include "states/game.hpp"
#include "game.hpp"

namespace snake
{
    static constexpr auto blockSize = 16;

    GameState::GameState(gk::SharedContextPtr sharedContext) : m_ctx{sharedContext},
                                                               m_snake{blockSize},
                                                               m_render{true},
                                                               m_timer{}
    {
    }

    void GameState::onCreate()
    {
        m_snake.reset(m_ctx->app->getWindowSize() / 2 / 16);

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

            m_timer.Reset();
        }
    }

    void GameState::draw(SDL_Renderer *renderer)
    {
        m_snake.draw(renderer);
    }

    void GameState::changeDirection(const gk::EventDetails &details)
    {
        const auto mousePos = details.mouse_pos;
    }
    void GameState::checkWorldBounds()
    {
        const auto &[x_pos, y_pos] = m_snake.getHeadPos().Get();

        if (x_pos < 0 ||
            x_pos >= static_cast<int>(m_ctx->app->getWindowSize().GetX() / blockSize) ||
            y_pos < 0 ||
            y_pos >= static_cast<int>(m_ctx->app->getWindowSize().GetY() / blockSize))
        {
            m_snake.reset({15, 15});
            m_snake.setDirection(Snake::Direction::up);
        }
    }
} // snake
