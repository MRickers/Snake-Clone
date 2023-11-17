#include "states/game.hpp"
#include "game.hpp"

namespace snake
{
    GameState::GameState(gk::SharedContextPtr sharedContext) : m_ctx{sharedContext},
                                                               m_snake{}
    {
    }

    void GameState::onCreate()
    {
        m_snake.reset(m_ctx->app->getWindowSize() / 2);

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
        m_snake.update();
    }

    void GameState::draw(SDL_Renderer *renderer)
    {
        m_snake.draw(renderer);
    }

    void GameState::changeDirection(const gk::EventDetails &details)
    {
        const auto mousePos = details.mouse_pos;
    }
} // snake
