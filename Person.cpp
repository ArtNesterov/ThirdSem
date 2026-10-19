#include "Person.h"
#include <utility>

Person::Person()
    : surname(""), name(""), patronymic(""), id("")
{
}

Person::Person(const std::string& surname, const std::string& name,
               const std::string& patronymic, const std::string& id)
    : surname(surname), name(name), patronymic(patronymic), id(id)
{
}

Person::Person(const Person& other)
    : surname(other.surname),
      name(other.name),
      patronymic(other.patronymic),
      id(other.id)
{
}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        surname = other.surname;
        name = other.name;
        patronymic = other.patronymic;
        id = other.id;
    }
    return *this;
}

Person::Person(Person&& other) noexcept
    : surname(std::move(other.surname)),
      name(std::move(other.name)),
      patronymic(std::move(other.patronymic)),
      id(std::move(other.id))
{
}

Person& Person::operator=(Person&& other) noexcept
{
    if (this != &other)
    {
        surname = std::move(other.surname);
        name = std::move(other.name);
        patronymic = std::move(other.patronymic);
        id = std::move(other.id);
    }
    return *this;
}

const std::string& Person::GetSurname() const
{
    return surname;
}

void Person::SetSurname(const std::string& newSurname)
{
    surname = newSurname;
}

const std::string& Person::GetName() const
{
    return name;
}

void Person::SetName(const std::string& newName)
{
    name = newName;
}

const std::string& Person::GetPatronymic() const
{
    return patronymic;
}

void Person::SetPatronymic(const std::string& newPatronymic)
{
    patronymic = newPatronymic;
}

const std::string& Person::GetId() const
{
    return id;
}

void Person::SetId(const std::string& newId)
{
    id = newId;
}

std::string Person::GetFullName() const
{
    std::string fullName = surname + " " + name;
    if (!patronymic.empty())
    {
        fullName += " " + patronymic;
    }
    return fullName;
}

std::string Person::ToString() const
{
    std::string res = "[Человек] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " | Идентификатор: " + id;
    }
    return res;
}

std::string Person::GetSummary() const
{
    return ToString();
}

bool Person::operator==(const Person& other) const
{
    return surname == other.surname &&
           name == other.name &&
           patronymic == other.patronymic &&
           id == other.id;
}

bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}
