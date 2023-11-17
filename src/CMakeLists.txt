add_executable(${PROJECT_NAME}
states/main.cpp
states/game.cpp
snake.hpp
snake.cpp
main.cpp
)
target_link_libraries(${PROJECT_NAME} libGkCore spdlog::spdlog_header_only)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_SOURCE_DIR}/src/assets/Roboto-Black.ttf $<TARGET_FILE_DIR:${PROJECT_NAME}>
)       