#include <iostream>
#include <string>
#include <vector>

std::string format_duration(int seconds)
{

    if (seconds == 0)
    {
        return "now";
    }

    constexpr int minutesInSeconds = 60;
    constexpr int hoursInSeconds = minutesInSeconds * 60;
    constexpr int dayInSeconds = hoursInSeconds * 24;
    constexpr int yearInSeconds = dayInSeconds * 365;

    int m_years = seconds / yearInSeconds;
    seconds -= m_years * yearInSeconds;

    int m_days = seconds / dayInSeconds;
    seconds -= m_days * dayInSeconds;

    int m_hours = seconds / hoursInSeconds;
    seconds -= m_hours * hoursInSeconds;

    int m_minutes = seconds / minutesInSeconds;
    seconds -= m_minutes * minutesInSeconds;

    std::vector<std::string> result;

    if (m_years != 0)
    {
        if (m_years == 1)
        {
            result.push_back(std::to_string(m_years) + " year");
        }
        else
        {
            result.push_back(std::to_string(m_years) + " years");
        }
    }
    if (m_days != 0)
    {
        if (m_days == 1)
        {
            result.push_back(std::to_string(m_days) + " day");
        }
        else
        {
            result.push_back(std::to_string(m_days) + " days");
        }
    }
    if (m_hours != 0)
    {
        if (m_hours == 1)
        {
            result.push_back(std::to_string(m_hours) + " hour");
        }
        else
        {
            result.push_back(std::to_string(m_hours) + " hours");
        }
    }
    if (m_minutes != 0)
    {
        if (m_minutes == 1)
        {
            result.push_back(std::to_string(m_minutes) + " minute");
        }
        else
        {
            result.push_back(std::to_string(m_minutes) + " minutes");
        }
    }
    if (seconds != 0)
    {
        if (seconds == 1)
        {
            result.push_back(std::to_string(seconds) + " second");
        }
        else
        {
            result.push_back(std::to_string(seconds) + " seconds");
        }
    }

    std::string resultString;

    if (result.size() == 1)
    {
        return result.front();
    }
    else
    {
        for (auto it = result.begin(); it != result.end() - 1; ++it)
        {
            resultString.append(*it + ", ");
        }
        resultString.pop_back(); // remove last space character
        resultString.pop_back(); // remove last ,
        resultString.append(" and " + result.back());
    }
    return resultString;
}

std::string refactor_format_duration(int seconds)
{
    if (seconds == 0)
        return "now";

    std::vector<std::string> times;
    auto add = [&](auto unit, auto time)
    {
        if (time == 0)
            return;
        times.push_back(std::to_string(time) + unit + (time > 1 ? "s" : ""));
    };

    add(" year", seconds / 31536000);
    add(" day", (seconds / 86400) % 365);
    add(" hour", (seconds / 3600) % 24);
    add(" minute", (seconds / 60) % 60);
    add(" second", seconds % 60);

    std::string result = times[0];
    for (std::size_t i = 1; i < times.size() - 1; ++i)
    {
        result.append(", " + times[i]);
    }
    if (times.size() > 1)
    {
        result.append(" and " + times.back());
    }

    return result;
}

int main()
{
    int seconds = 3662;
    std::cout << format_duration(seconds) << '\n';
    std::cout << refactor_format_duration(seconds) << '\n';
}
