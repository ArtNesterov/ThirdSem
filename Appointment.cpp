#include "Appointment.h"
#include <utility>
#include <stdexcept>

std::set<int> Appointment::existingIds;
std::map<int, int> Appointment::idRefCount;

Appointment::Appointment()
    : id(0), doctor(nullptr), patient(nullptr), appointmentDateTime("")
{
}

Appointment::Appointment(const int id,
                         const std::shared_ptr<Doctor>& doctor,
                         const std::shared_ptr<Patient>& patient,
                         const std::string& appointmentDateTime)
    : id(id),
      doctor(doctor),
      patient(patient),
      appointmentDateTime(appointmentDateTime)
{
    if (this->id <= 0)
    {
        throw std::invalid_argument("ID записи должен быть больше нуля");
    }
    if (existingIds.find(this->id) != existingIds.end())
    {
        throw std::invalid_argument("Запись с ID " + std::to_string(this->id) + " уже существует");
    }
    existingIds.insert(this->id);
    idRefCount[this->id] = 1;
}

Appointment::~Appointment()
{
    if (id > 0)
    {
        auto it = idRefCount.find(id);
        if (it != idRefCount.end())
        {
            if (--it->second <= 0)
            {
                idRefCount.erase(it);
                existingIds.erase(id);
            }
        }
    }
}

Appointment::Appointment(const Appointment& other)
    : id(other.id),
      doctor(other.doctor),
      patient(other.patient),
      appointmentDateTime(other.appointmentDateTime)
{
    if (id > 0)
    {
        idRefCount[id]++;
    }
}

Appointment& Appointment::operator=(const Appointment& other)
{
    if (this != &other)
    {
        if (id > 0)
        {
            auto it = idRefCount.find(id);
            if (it != idRefCount.end() && --it->second <= 0)
            {
                idRefCount.erase(it);
                existingIds.erase(id);
            }
        }

        id = other.id;
        doctor = other.doctor;
        patient = other.patient;
        appointmentDateTime = other.appointmentDateTime;

        if (id > 0)
        {
            idRefCount[id]++;
        }
    }
    return *this;
}

Appointment::Appointment(Appointment&& other) noexcept
    : id(other.id),
      doctor(std::move(other.doctor)),
      patient(std::move(other.patient)),
      appointmentDateTime(std::move(other.appointmentDateTime))
{
    other.id = 0;
}

Appointment& Appointment::operator=(Appointment&& other) noexcept
{
    if (this != &other)
    {
        if (id > 0)
        {
            auto it = idRefCount.find(id);
            if (it != idRefCount.end() && --it->second <= 0)
            {
                idRefCount.erase(it);
                existingIds.erase(id);
            }
        }

        id = other.id;
        doctor = std::move(other.doctor);
        patient = std::move(other.patient);
        appointmentDateTime = std::move(other.appointmentDateTime);
        other.id = 0;
    }
    return *this;
}

int Appointment::GetId() const
{
    return id;
}

void Appointment::SetId(const int newId)
{
    if (newId <= 0)
    {
        throw std::invalid_argument("ID записи должен быть больше нуля");
    }
    if (newId != id && existingIds.find(newId) != existingIds.end())
    {
        throw std::invalid_argument("Запись с ID " + std::to_string(newId) + " уже существует");
    }
    if (id > 0)
    {
        auto it = idRefCount.find(id);
        if (it != idRefCount.end() && --it->second <= 0)
        {
            idRefCount.erase(it);
            existingIds.erase(id);
        }
    }
    id = newId;
    existingIds.insert(id);
    idRefCount[id] = 1;
}

const std::shared_ptr<Doctor>& Appointment::GetDoctor() const
{
    return doctor;
}

void Appointment::SetDoctor(const std::shared_ptr<Doctor>& doc)
{
    doctor = doc;
}

const std::shared_ptr<Patient>& Appointment::GetPatient() const
{
    return patient;
}

void Appointment::SetPatient(const std::shared_ptr<Patient>& pat)
{
    patient = pat;
}

const std::string& Appointment::GetAppointmentDateTime() const
{
    return appointmentDateTime;
}

void Appointment::SetAppointmentDateTime(const std::string& dateTime)
{
    appointmentDateTime = dateTime;
}

bool Appointment::IsIdExists(const int searchId)
{
    return existingIds.find(searchId) != existingIds.end();
}

void Appointment::ResetRegistry()
{
    existingIds.clear();
    idRefCount.clear();
}

std::string Appointment::ToString() const
{
    std::string res = "Запись на прием к врачу:\n";
    if (patient)
    {
        res += "  Пациент: " + patient->GetFullName() + " (Полис ОМС: " + patient->GetPolicyNumber() + ", Телефон: " + patient->GetPhone() + ")\n";
    }
    else
    {
        res += "  Пациент: не указан\n";
    }
    if (doctor)
    {
        res += "  Врач: " + doctor->GetFullName() + " (" + doctor->GetSpecialization() + ", " + doctor->GetCabinet() + ")\n";
        res += "  Расписание приема врача: " + doctor->GetSchedule().GetDaysOfWeek() + " (" +
               doctor->GetSchedule().GetStartTime() + " - " + doctor->GetSchedule().GetEndTime() + ")\n";
    }
    else
    {
        res += "  Врач: не указан\n";
    }
    res += "  Дата и время приема: " + appointmentDateTime;
    return res;
}

std::string Appointment::GetSummary() const
{
    std::string res = "Дата и время приема: " + appointmentDateTime;
    if (patient)
    {
        res += " | Пациент: " + patient->GetFullName();
    }
    if (doctor)
    {
        res += " | Врач: " + doctor->GetFullName() + " (" + doctor->GetSpecialization() + ", " + doctor->GetCabinet() + ")";
    }
    return res;
}

bool Appointment::operator==(const Appointment& other) const
{
    return id == other.id &&
           appointmentDateTime == other.appointmentDateTime &&
           doctor == other.doctor &&
           patient == other.patient;
}

bool Appointment::operator!=(const Appointment& other) const
{
    return !(*this == other);
}
