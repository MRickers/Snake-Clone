#include "main.hpp"
#include <spdlog/spdlog.h>
#include <filesystem>

namespace fs = std::filesystem;

snake::MainState::MainState(gk::SharedContextPtr sharedContext)
    : m_ctx{sharedContext}
{
    // Get the current working directory
    fs::path currentPath = fs::current_path();
    spdlog::info("current path: " + currentPath.string());

    spdlog::info("loading fonts...");
    for (int i = 0; i < buttonCount; i++)
    {
        if (!m_textBoxes[i].loadFont("Roboto-Black.ttf", 25))
        {
            spdlog::warn("could not load textbox font");
        }
    }
}

void snake::MainState::onCreate()
{
    const auto [x, y] = m_buttonPos.Get();
    for (int i = 0; i < buttonCount; ++i)
    {
        const auto buttonPos =
            gk::Vector2D{x, y + (i * (m_buttonSize.GetY() + m_buttonPadding))};

        m_shapes[i].m_pos = buttonPos + m_buttonSize / 2;
        m_shapes[i].m_size = m_buttonSize;
        m_textBoxes[i].setPos({m_shapes[i].m_pos.GetX() + 10, m_shapes[i].m_pos.GetY() + 10});

        if (i == 0)
        {
            m_textBoxes[i].add("START");
        }
        else if (i == 1)
        {
            m_textBoxes[i].add("OPTIONS");
            m_shapes[i].m_size = {130, 50};
        }
        else
        {
            m_textBoxes[i].add("QUIT");
        }
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
    m_ctx->inputHandler->RemoveBinding(StateType::MAIN,
                                       "MouseLeft");
    m_ctx->inputHandler->RemoveCallback(StateType::MAIN,
                                        "MouseLeft");
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
                m_ctx->stateMachine->switchTo(StateType::GAME);
                m_ctx->inputHandler->setCurrentState(StateType::GAME);
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
    gk::Draw::setRendererColor(renderer, gk::Color::CRIMSON);
    for (int i = 0; i < 3; ++i)
    {
        gk::Draw::filledRect(renderer, m_shapes[i].m_pos, m_shapes[i].m_size);
        m_textBoxes[i].draw(renderer);
    }
}