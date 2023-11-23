#pragma once
#include <stddef.h>
#include <chrono>

namespace snake
{
    struct ScoreConfig
    {
        std::chrono::milliseconds upperLimit;
        std::chrono::milliseconds lowerLimit;
        size_t highscore;
        size_t middlescore;
        size_t lowscore;
    };

    class Score
    {
    public:
        Score(const ScoreConfig &);
        Score &operator++();

        void resetTimer();

        size_t getScore() const;
        void setScore(size_t);

    private:
        ScoreConfig m_config;
        size_t m_score{0};
        std::chrono::system_clock::time_point m_start;
    };

} // namespace snake
