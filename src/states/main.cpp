#include "main.hpp"
#include <spdlog/spdlog.h>

void snake::MainState::onCreate()
{
    const auto [x, y] = m_buttonPos.Get();
    for (int i = 0; i < 3; ++i)
    {
        const auto buttonPos =
            gk::Vector2D{x, y + (i * (m_buttonSize.GetY() + m_buttonPadding))};

        m_shapes[i].m_pos = buttonPos + m_buttonSize / 2;
        m_shapes[i].m_size = m_buttonSize;
    }
    m_ctx->inputHandler->AddCallback(
        StateType::MAIN, "MouseLeft",
        [this](const gk::EventDetails &details)
        { mouseClick(details); });

    auto binding = gk::EventBinding{"MouseLeft"};
    binding.events.push_back({gk::EventType::MouseDown, SDL_SCANCODE_UNKNOWN,
                              gk::MouseButton::Left});
    m_ctx->inputHandler->AddBinding(StateType::MAIN, binding);
}

void snake::MainState::onDestroy()
{
    m_ctx->inputHandler->RemoveBinding(StateType::INTRO,
                                       "IntroContinue");
    m_ctx->inputHandler->RemoveCallback(StateType::INTRO,
                                        "IntroContinue");
}

void snake::MainState::mouseClick(const gk::EventDetails &details)
{
    const auto [mouseX, mouseY] = details.mouse_pos.Get();
    const auto [btnSizeX, btnSizeY] = m_buttonSize.Get();

    for (int i = 0; i < 3; ++i)
    {
        if (mouseX >= m_shapes[i].m_pos.GetX() &&
            mouseX <= m_shapes[i].m_pos.GetX() + btnSizeX &&
            mouseY >= m_shapes[i].m_pos.GetY() &&
            mouseY <= m_shapes[i].m_pos.GetY() + btnSizeY)
        {
            if (i == 0)
            {
                // m_ctx->stateMachine->switchTo(StateType::GAME);
                // m_ctx->inputHandler->setCurrentState(StateType::GAME);
            }
            else if (i == 1)
            {
                spdlog::info("Options");
            }
            else
            {
                m_ctx->app->stop();
            }
        }
    }
}

void snake::MainState::draw(SDL_Renderer *renderer)
{
    gk::Draw::setRendererColor(renderer, gk::Color::LIME);
    for (int i = 0; i < 3; ++i)
    {
        gk::Draw::filledRect(renderer, m_shapes[i].m_pos, m_shapes[i].m_size);
    }
}