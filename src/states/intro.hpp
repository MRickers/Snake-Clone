#pragma once
#include "states.hpp"
#include <GameKit/core/BaseState.hpp>
#include <GameKit/core/ui/TextBox.hpp>
#include <GameKit/helpers/Timer.hpp>

namespace snake
{
    class IntroState : public gk::IBaseState
    {
    public:
        IntroState(gk::SharedContextPtr);

        virtual void onCreate() override;
        virtual void onDestroy() override;

        virtual void activate() override;
        virtual void deactivate() override;

        virtual void update() override;
        virtual void draw(SDL_Renderer *) override;

    private:
        void changeState(const gk::EventDetails &);

        gk::SharedContextPtr m_ctx{nullptr};
        gk::Timer m_timer{};
    };

} // namespace snake
