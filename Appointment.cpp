#include "Appointment.h"
#include <utility>

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
}

Appointment::Appointment(const Appointment& other)
    : id(other.id),
      doctor(other.doctor),
      patient(other.patient),
      appointmentDateTime(other.appointmentDateTime)
{
}

Appointment& Appointment::operator=(const Appointment& other)
{
    if (this != &other)
    {
        id = other.id;
        doctor = other.doctor;
        patient = other.patient;
        appointmentDateTime = other.appointmentDateTime;
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
    id = newId;
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
