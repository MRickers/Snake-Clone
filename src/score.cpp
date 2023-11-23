#include "score.hpp"

snake::Score::Score(const ScoreConfig &config) : m_config{config},
                                                 m_score{0},
                                                 m_start{}
{
}

snake::Score &snake::Score::operator++()
{
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_start);

    if (duration <= m_config.upperLimit)
    {
        m_score += m_config.highscore;
    }
    else if (duration > m_config.upperLimit && duration <= m_config.lowerLimit)
    {
        m_score += m_config.middlescore;
    }
    else
    {
        m_score += m_config.lowscore;
    }
    return *this;
}

void snake::Score::resetTimer()
{
    m_start = std::chrono::system_clock::now();
}

size_t snake::Score::getScore() const
{
    return m_score;
}

void snake::Score::setScore(size_t newScore)
{
    m_score = newScore;
}
