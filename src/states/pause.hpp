#pragma once
#include <GameKit/core/BaseState.hpp>

namespace snake
{
    class PauseState : public gk::IBaseState
    {
    public:
        PauseState(gk::SharedContextPtr sharedContext)
            : m_sharedContext{sharedContext}
        {
        }

        void onCreate() override
        {
            setTransparent(true);

            m_shape.m_size = m_sharedContext->app->getWindowSize();
            m_shape.m_pos = {0, 0};

            {
                m_sharedContext->inputHandler->AddCallback(
                    StateType::PAUSED, "Unpause",
                    [this](const gk::EventDetails &details)
                    { unpause(details); });

                auto binding = gk::EventBinding{"Unpause"};
                binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_P});
                m_sharedContext->inputHandler->AddBinding(StateType::PAUSED, binding);
            }
        }
        void onDestroy() override
        {
            m_sharedContext->inputHandler->RemoveBinding(StateType::PAUSED, "Unpause");
            m_sharedContext->inputHandler->RemoveCallback(StateType::PAUSED, "Unpause");
        }

        void activate() override
        {
        }
        void deactivate() override
        {
        }

        void update() override
        {
        }
        void draw(SDL_Renderer *renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
            gk::Draw::filledRect(renderer, m_shape.m_pos, m_shape.m_size);
        }

    private:
        void unpause(const gk::EventDetails &)
        {
            m_sharedContext->stateMachine->switchTo(StateType::GAME);
            m_sharedContext->inputHandler->setCurrentState(StateType::GAME);
        }

        gk::SharedContextPtr m_sharedContext{nullptr};
        gk::Shape m_shape;
    };

} // namespace snake
