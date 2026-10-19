#include "Schedule.h"
#include <utility>

Schedule::Schedule()
    : daysOfWeek(""), startTime(""), endTime(""), cabinet("")
{
}

Schedule::Schedule(const std::string& daysOfWeek, const std::string& startTime,
                   const std::string& endTime, const std::string& cabinet)
    : daysOfWeek(daysOfWeek), startTime(startTime), endTime(endTime), cabinet(cabinet)
{
}

Schedule::Schedule(const Schedule& other)
    : daysOfWeek(other.daysOfWeek),
      startTime(other.startTime),
      endTime(other.endTime),
      cabinet(other.cabinet)
{
}

Schedule& Schedule::operator=(const Schedule& other)
{
    if (this != &other)
    {
        daysOfWeek = other.daysOfWeek;
        startTime = other.startTime;
        endTime = other.endTime;
        cabinet = other.cabinet;
    }
    return *this;
}

Schedule::Schedule(Schedule&& other) noexcept
    : daysOfWeek(std::move(other.daysOfWeek)),
      startTime(std::move(other.startTime)),
      endTime(std::move(other.endTime)),
      cabinet(std::move(other.cabinet))
{
}

Schedule& Schedule::operator=(Schedule&& other) noexcept
{
    if (this != &other)
    {
        daysOfWeek = std::move(other.daysOfWeek);
        startTime = std::move(other.startTime);
        endTime = std::move(other.endTime);
        cabinet = std::move(other.cabinet);
    }
    return *this;
}

const std::string& Schedule::GetDaysOfWeek() const
{
    return daysOfWeek;
}

void Schedule::SetDaysOfWeek(const std::string& days)
{
    daysOfWeek = days;
}

const std::string& Schedule::GetStartTime() const
{
    return startTime;
}

void Schedule::SetStartTime(const std::string& time)
{
    startTime = time;
}

const std::string& Schedule::GetEndTime() const
{
    return endTime;
}

void Schedule::SetEndTime(const std::string& time)
{
    endTime = time;
}

const std::string& Schedule::GetCabinet() const
{
    return cabinet;
}

void Schedule::SetCabinet(const std::string& cab)
{
    cabinet = cab;
}

std::string Schedule::ToString() const
{
    std::string res = "Кабинет: " + (cabinet.empty() ? "не указан" : cabinet);
    res += " | Дни приема: " + (daysOfWeek.empty() ? "не указаны" : daysOfWeek);
    res += " | Время: " + (startTime.empty() ? "--:--" : startTime) + " - " + (endTime.empty() ? "--:--" : endTime);
    return res;
}

bool Schedule::operator==(const Schedule& other) const
{
    return daysOfWeek == other.daysOfWeek &&
           startTime == other.startTime &&
           endTime == other.endTime &&
           cabinet == other.cabinet;
}

bool Schedule::operator!=(const Schedule& other) const
{
    return !(*this == other);
}
