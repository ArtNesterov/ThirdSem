#include "Person.h"
#include <utility>
#include <stdexcept>

size_t Person::nextId = 0;

Person::Person()
    : surname(""), name(""), patronymic(""), id(std::to_string(++nextId))
{
}

Person::Person(const std::string& surname, const std::string& name,
               const std::string& patronymic, const std::string& id)
    : surname(surname), name(name), patronymic(patronymic), id(id)
{
    if (this->id.empty() || this->id.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("ID не может быть пустым");
    }
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

void Person::SetSurname(const std::string& s)
{
    surname = s;
}

const std::string& Person::GetName() const
{
    return name;
}

void Person::SetName(const std::string& n)
{
    name = n;
}

const std::string& Person::GetPatronymic() const
{
    return patronymic;
}

void Person::SetPatronymic(const std::string& p)
{
    patronymic = p;
}

const std::string& Person::GetId() const
{
    return id;
}

void Person::SetId(const std::string& newId)
{
    if (newId.empty() || newId.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("Идентификатор (id) не может быть пустым");
    }
    id = newId;
}

std::string Person::GetFullName() const
{
    std::string fullName = surname;
    if (!name.empty())
    {
        if (!fullName.empty()) fullName += " ";
        fullName += name;
    }
    if (!patronymic.empty())
    {
        if (!fullName.empty()) fullName += " ";
        fullName += patronymic;
    }
    return fullName;
}

size_t Person::GetNextId()
{
    return nextId;
}

void Person::ResetNextId(const size_t start)
{
    nextId = start;
}

std::string Person::ToString() const
{
    std::string res = GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    return res;
}

std::string Person::GetSummary() const
{
    return GetFullName();
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
