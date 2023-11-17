#pragma once
#include <GameKit/core/BaseState.hpp>
#include "states.hpp"

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
        gk::SharedContextPtr m_ctx;
    };
} // namespace snake
