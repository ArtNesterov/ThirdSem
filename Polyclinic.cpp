#include "Polyclinic.h"
#include <utility>

Polyclinic::Polyclinic()
    : name(""), address(""), nextAppointmentId(1)
{
}

Polyclinic::Polyclinic(const std::string& name, const std::string& address)
    : name(name), address(address), nextAppointmentId(1)
{
}

Polyclinic::Polyclinic(const Polyclinic& other)
    : name(other.name),
      address(other.address),
      doctors(other.doctors),
      patients(other.patients),
      appointments(other.appointments),
      nextAppointmentId(other.nextAppointmentId)
{
}

Polyclinic& Polyclinic::operator=(const Polyclinic& other)
{
    if (this != &other)
    {
        name = other.name;
        address = other.address;
        doctors = other.doctors;
        patients = other.patients;
        appointments = other.appointments;
        nextAppointmentId = other.nextAppointmentId;
    }
    return *this;
}

Polyclinic::Polyclinic(Polyclinic&& other) noexcept
    : name(std::move(other.name)),
      address(std::move(other.address)),
      doctors(std::move(other.doctors)),
      patients(std::move(other.patients)),
      appointments(std::move(other.appointments)),
      nextAppointmentId(other.nextAppointmentId)
{
    other.nextAppointmentId = 1;
}

Polyclinic& Polyclinic::operator=(Polyclinic&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        address = std::move(other.address);
        doctors = std::move(other.doctors);
        patients = std::move(other.patients);
        appointments = std::move(other.appointments);
        nextAppointmentId = other.nextAppointmentId;
        other.nextAppointmentId = 1;
    }
    return *this;
}

const std::string& Polyclinic::GetName() const
{
    return name;
}

void Polyclinic::SetName(const std::string& n)
{
    name = n;
}

const std::string& Polyclinic::GetAddress() const
{
    return address;
}

void Polyclinic::SetAddress(const std::string& addr)
{
    address = addr;
}

void Polyclinic::AddDoctor(Doctor* doctor)
{
    if (doctor)
    {
        doctors.push_back(doctor);
    }
}

void Polyclinic::AddPatient(Patient* patient)
{
    if (patient)
    {
        patients.push_back(patient);
    }
}

Appointment* Polyclinic::RegisterAppointment(
    Doctor* doctor,
    Patient* patient,
    const std::string& dateTime)
{
    while (Appointment::IsIdExists(nextAppointmentId))
    {
        nextAppointmentId++;
    }
    const int apptId = nextAppointmentId++;
    Appointment* appt = new Appointment(apptId, doctor, patient, dateTime);
    appointments.push_back(appt);
    return appt;
}

Doctor* Polyclinic::FindDoctorById(const std::string& doctorId) const
{
    for (const auto& doc : doctors)
    {
        if (doc && doc->GetId() == doctorId)
        {
            return doc;
        }
    }
    return nullptr;
}

Doctor* Polyclinic::FindDoctorBySurname(const std::string& surname) const
{
    for (const auto& doc : doctors)
    {
        if (doc && doc->GetSurname() == surname)
        {
            return doc;
        }
    }
    return nullptr;
}

Patient* Polyclinic::FindPatientByPolicy(const std::string& policyNumber) const
{
    for (const auto& pat : patients)
    {
        if (pat && pat->GetPolicyNumber() == policyNumber)
        {
            return pat;
        }
    }
    return nullptr;
}

Appointment* Polyclinic::FindAppointmentById(const int appointmentId) const
{
    for (const auto& app : appointments)
    {
        if (app && app->GetId() == appointmentId)
        {
            return app;
        }
    }
    return nullptr;
}

std::vector<Appointment*> Polyclinic::FindAppointmentsByPatientPolicy(const std::string& policyNumber) const
{
    std::vector<Appointment*> result;
    for (const auto& app : appointments)
    {
        if (app && app->GetPatient() && app->GetPatient()->GetPolicyNumber() == policyNumber)
        {
            result.push_back(app);
        }
    }
    return result;
}

std::vector<Appointment*> Polyclinic::FindAppointmentsByDoctorId(const std::string& doctorId) const
{
    std::vector<Appointment*> result;
    for (const auto& app : appointments)
    {
        if (app && app->GetDoctor() && app->GetDoctor()->GetId() == doctorId)
        {
            result.push_back(app);
        }
    }
    return result;
}

std::string Polyclinic::GetDoctorsSummary() const
{
    std::string summary = "=== Сводная информация о врачах поликлиники ===\n";
    if (!name.empty())
    {
        summary += "Учреждение: " + name + "\n";
    }
    if (!address.empty())
    {
        summary += "Адрес: " + address + "\n";
    }
    summary += "Всего врачей: " + std::to_string(doctors.size()) + "\n";
    summary += "--------------------------------------------------\n";

    if (doctors.empty())
    {
        summary += "Список врачей пуст.\n";
        return summary;
    }

    int idx = 1;
    for (const auto& doc : doctors)
    {
        if (doc)
        {
            summary += std::to_string(idx++) + ". " + doc->GetSummary() + "\n";
        }
    }
    return summary;
}

std::string Polyclinic::GetPatientsSummary() const
{
    std::string summary = "=== Сводная информация о пациентах поликлиники ===\n";
    if (!name.empty())
    {
        summary += "Учреждение: " + name + "\n";
    }
    summary += "Всего зарегистрированных пациентов: " + std::to_string(patients.size()) + "\n";
    summary += "--------------------------------------------------\n";

    if (patients.empty())
    {
        summary += "Список пациентов пуст.\n";
        return summary;
    }

    int idx = 1;
    for (const auto& pat : patients)
    {
        if (pat)
        {
            summary += std::to_string(idx++) + ". " + pat->GetSummary() + "\n";
        }
    }
    return summary;
}

std::string Polyclinic::GetAppointmentInfo(const int appointmentId) const
{
    const auto app = FindAppointmentById(appointmentId);
    if (!app)
    {
        return "Запись с идентификатором " + std::to_string(appointmentId) + " не найдена.\n";
    }
    return app->ToString() + "\n";
}

std::string Polyclinic::GetPatientAppointmentsInfo(const std::string& policyNumber) const
{
    const auto pat = FindPatientByPolicy(policyNumber);
    if (!pat)
    {
        return "Пациент с полисом ОМС " + policyNumber + " не найден.\n";
    }

    const auto appts = FindAppointmentsByPatientPolicy(policyNumber);
    if (appts.empty())
    {
        return "Записей к врачу для пациента " + pat->GetFullName() + " не найдено.\n";
    }

    std::string res;
    for (const auto& a : appts)
    {
        if (a)
        {
            res += a->ToString() + "\n";
        }
    }
    return res;
}

const std::vector<Doctor*>& Polyclinic::GetDoctors() const
{
    return doctors;
}

const std::vector<Patient*>& Polyclinic::GetPatients() const
{
    return patients;
}

const std::vector<Appointment*>& Polyclinic::GetAppointments() const
{
    return appointments;
}

size_t Polyclinic::GetDoctorCount() const
{
    return doctors.size();
}

size_t Polyclinic::GetPatientCount() const
{
    return patients.size();
}

size_t Polyclinic::GetAppointmentCount() const
{
    return appointments.size();
}
