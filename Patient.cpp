#include "Patient.h"
#include <utility>

Patient::Patient()
    : Person(), policyNumber(""), birthDate(""), phone("")
{
}

Patient::Patient(const std::string& surname, const std::string& name,
                 const std::string& patronymic, const std::string& id,
                 const std::string& policyNumber, const std::string& birthDate,
                 const std::string& phone)
    : Person(surname, name, patronymic, id),
      policyNumber(policyNumber),
      birthDate(birthDate),
      phone(phone)
{
}

Patient::Patient(const Patient& other)
    : Person(other),
      policyNumber(other.policyNumber),
      birthDate(other.birthDate),
      phone(other.phone)
{
}

Patient& Patient::operator=(const Patient& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        policyNumber = other.policyNumber;
        birthDate = other.birthDate;
        phone = other.phone;
    }
    return *this;
}

Patient::Patient(Patient&& other) noexcept
    : Person(std::move(other)),
      policyNumber(std::move(other.policyNumber)),
      birthDate(std::move(other.birthDate)),
      phone(std::move(other.phone))
{
}

Patient& Patient::operator=(Patient&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(std::move(other));
        policyNumber = std::move(other.policyNumber);
        birthDate = std::move(other.birthDate);
        phone = std::move(other.phone);
    }
    return *this;
}

const std::string& Patient::GetPolicyNumber() const
{
    return policyNumber;
}

void Patient::SetPolicyNumber(const std::string& policy)
{
    policyNumber = policy;
}

const std::string& Patient::GetBirthDate() const
{
    return birthDate;
}

void Patient::SetBirthDate(const std::string& date)
{
    birthDate = date;
}

const std::string& Patient::GetPhone() const
{
    return phone;
}

void Patient::SetPhone(const std::string& ph)
{
    phone = ph;
}

std::string Patient::ToString() const
{
    std::string res = "[Пациент] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    res += " | Полис ОМС: " + (policyNumber.empty() ? "нет" : policyNumber);
    res += " | Дата рождения: " + (birthDate.empty() ? "не указана" : birthDate);
    res += " | Телефон: " + (phone.empty() ? "не указан" : phone);
    return res;
}

std::string Patient::GetSummary() const
{
    std::string res = "Пациент: " + GetFullName();
    res += " | Полис ОМС: " + (policyNumber.empty() ? "нет" : policyNumber);
    res += " | Дата рожд.: " + (birthDate.empty() ? "--" : birthDate);
    res += " | Тел.: " + (phone.empty() ? "--" : phone);
    return res;
}

bool Patient::operator==(const Patient& other) const
{
    return Person::operator==(other) &&
           policyNumber == other.policyNumber &&
           birthDate == other.birthDate &&
           phone == other.phone;
}

bool Patient::operator!=(const Patient& other) const
{
    return !(*this == other);
}
