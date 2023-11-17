#pragma once
#include "states.hpp"
#include <GameKit/core/BaseState.hpp>
#include <GameKit/helpers/Types.hpp>
#include <GameKit/helpers/Draw.hpp>
#include <GameKit/core/ui/TextBox.hpp>
#include <spdlog/spdlog.h>

namespace snake
{
    class MainState : public gk::IBaseState
    {
        static constexpr auto buttonCount = 3;

    public:
        MainState(gk::SharedContextPtr sharedContext)
            : m_ctx{sharedContext}
        {
            spdlog::info("loading fonts...");
            for (int i = 0; i < buttonCount; i++)
            {
                if (!m_textBoxes[i].loadFont("Roboto-Black.ttf", 25))
                {
                    spdlog::warn("could not load textbox font");
                }
            }
        }

        void onCreate() override;
        void onDestroy() override;

        void activate() override
        {
        }
        void deactivate() override
        {
        }

        void update() override
        {
        }
        void draw(SDL_Renderer *renderer) override;

    private:
        void mouseClick(const gk::EventDetails &details);

        gk::SharedContextPtr m_ctx{nullptr};

        gk::Vector2D m_buttonSize{100, 50};
        gk::Vector2D m_buttonPos{220, 90};
        uint32_t m_buttonPadding{10};
        gk::Shape m_shapes[buttonCount];
        gk::TextBox m_textBoxes[buttonCount];
    };

} // namespace snake
