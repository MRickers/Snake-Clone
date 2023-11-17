#include <spdlog/spdlog.h>
#include <GameKit/App.hpp>
#include "states/intro.hpp"
#include "states/main.hpp"
int main()
{
    const gk::Vector2D windowSize{640, 480};

    auto app = std::make_shared<gk::App>(gk::AppConfiguration{
        "Snake v.0.1", static_cast<size_t>(windowSize.GetX()),
        static_cast<size_t>(windowSize.GetY())});

    auto inputHandler = std::make_shared<gk::StateInputHandler>();
    auto stateMachine = std::make_shared<gk::StateMachine>();
    gk::SharedContextPtr sharedContext =
        std::make_shared<gk::SharedContext>(inputHandler, stateMachine, app);

    stateMachine->registerState(
        StateType::INTRO,
        [sharedContext, &windowSize]() -> gk::BaseStatePtr
        { return std::make_unique<snake::IntroState>(sharedContext); });

    stateMachine->registerState(
        StateType::MAIN,
        [sharedContext]() -> gk::BaseStatePtr
        { return std::make_unique<snake::MainState>(sharedContext); });

    app->setInputHandler(inputHandler);
    app->setStateMachine(stateMachine);
    stateMachine->switchTo(StateType::INTRO);

    try
    {
        app->run();
    }
    catch (const std::exception &e)
    {
        spdlog::error(e.what());
    }

    return 0;
}