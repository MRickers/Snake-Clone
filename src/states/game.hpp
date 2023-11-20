#pragma once
#include <GameKit/core/BaseState.hpp>
#include <GameKit/helpers/Timer.hpp>
#include "states/states.hpp"
#include "snake.hpp"
#include "apple.hpp"

namespace snake
{
    class GameState : public gk::IBaseState
    {
    public:
        GameState(gk::SharedContextPtr sharedContext);

        virtual void onCreate() override;
        virtual void onDestroy() override;

        virtual void activate() override;
        virtual void deactivate() override;

        virtual void update() override;
        virtual void draw(SDL_Renderer *) override;

    private:
        void changeDirection(const gk::EventDetails &);
        void checkWorldBounds();
        void renderBounds(SDL_Renderer *);

        gk::SharedContextPtr m_ctx;
        snake::Snake m_snake;
        gk::Timer m_timer;
        gk::Vector2D m_bounds;
        snake::Apple m_apple;
    };
} // namespace snake
