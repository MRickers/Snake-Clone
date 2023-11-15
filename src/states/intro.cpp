#include "intro.hpp"

snake::IntroState::IntroState(gk::SharedContextPtr sharedContext) : m_ctx{sharedContext}
{
}

void snake::IntroState::onCreate()
{
    m_ctx->inputHandler->AddCallback(
        StateType::INTRO, "IntroContinue",
        [this](const gk::EventDetails &details)
        { changeState(details); });

    auto binding = gk::EventBinding{"IntroContinue"};
    binding.events.push_back({gk::EventType::KeyDown, SDL_SCANCODE_SPACE});
    m_ctx->inputHandler->AddBinding(StateType::INTRO, binding);
}

void snake::IntroState::changeState([[maybe_unused]] const gk::EventDetails &)
{
    if (m_timer.HasPassed(1000))
    {
        if (m_ctx)
        {
            m_ctx->stateMachine->switchTo(StateType::MAIN);
            m_ctx->stateMachine->remove(StateType::INTRO);
            m_ctx->inputHandler->setCurrentState(StateType::MAIN);
        }
    }
}

void snake::IntroState::onDestroy()
{
}

void snake::IntroState::activate()
{
    m_timer.Start();
}

void snake::IntroState::deactivate()
{
}

void snake::IntroState::update()
{
}

void snake::IntroState::draw([[maybe_unused]] SDL_Renderer *renderer)
{
}
