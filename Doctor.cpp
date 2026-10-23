#include "Doctor.h"
#include <utility>

Doctor::Doctor()
    : Person(), specialization(""), experienceYears(0), schedule()
{
}

Doctor::Doctor(const std::string& surname, const std::string& name,
               const std::string& patronymic, const std::string& id,
               const std::string& specialization, const int experienceYears,
               const Schedule& schedule)
    : Person(surname, name, patronymic, id),
      specialization(specialization),
      experienceYears(experienceYears),
      schedule(schedule)
{
}

Doctor::Doctor(const Doctor& other)
    : Person(other),
      specialization(other.specialization),
      experienceYears(other.experienceYears),
      schedule(other.schedule)
{
}

Doctor& Doctor::operator=(const Doctor& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        specialization = other.specialization;
        experienceYears = other.experienceYears;
        schedule = other.schedule;
    }
    return *this;
}

Doctor::Doctor(Doctor&& other) noexcept
    : Person(std::move(other)),
      specialization(std::move(other.specialization)),
      experienceYears(other.experienceYears),
      schedule(std::move(other.schedule))
{
    other.experienceYears = 0;
}

Doctor& Doctor::operator=(Doctor&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(std::move(other));
        specialization = std::move(other.specialization);
        experienceYears = other.experienceYears;
        schedule = std::move(other.schedule);
        other.experienceYears = 0;
    }
    return *this;
}

const std::string& Doctor::GetSpecialization() const
{
    return specialization;
}

void Doctor::SetSpecialization(const std::string& spec)
{
    specialization = spec;
}

int Doctor::GetExperienceYears() const
{
    return experienceYears;
}

void Doctor::SetExperienceYears(const int years)
{
    experienceYears = years;
}

const Schedule& Doctor::GetSchedule() const
{
    return schedule;
}

Schedule& Doctor::GetSchedule()
{
    return schedule;
}

void Doctor::SetSchedule(const Schedule& sched)
{
    schedule = sched;
}

const std::string& Doctor::GetCabinet() const
{
    return schedule.GetCabinet();
}

std::string Doctor::ToString() const
{
    std::string res = "[Врач] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    res += " | Специальность: " + specialization;
    res += " | Стаж: " + std::to_string(experienceYears) + " лет";
    res += " | " + schedule.ToString();
    return res;
}

std::string Doctor::GetSummary() const
{
    std::string res = "Врач: " + GetFullName();
    res += " | Специальность: " + specialization;
    res += " | Кабинет: " + schedule.GetCabinet();
    res += " | График: " + schedule.GetDaysOfWeek() + " (" +
           schedule.GetStartTime() + " - " + schedule.GetEndTime() + ")";
    return res;
}

bool Doctor::operator==(const Doctor& other) const
{
    return Person::operator==(other) &&
           specialization == other.specialization &&
           experienceYears == other.experienceYears &&
           schedule == other.schedule;
}

bool Doctor::operator!=(const Doctor& other) const
{
    return !(*this == other);
}
