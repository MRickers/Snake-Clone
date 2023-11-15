add_executable(${PROJECT_NAME}
main.cpp
states/intro.cpp
states/main.cpp
)
target_link_libraries(${PROJECT_NAME} libGkCore spdlog::spdlog_header_only)