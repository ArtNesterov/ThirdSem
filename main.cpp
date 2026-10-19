#include <iostream>
#include <vector>
#include <memory>
#include <windows.h>
#include "Person.h"
#include "Doctor.h"
#include "Patient.h"
#include "Schedule.h"
#include "Appointment.h"
#include "Polyclinic.h"

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0 при успешном завершении программы
 */
int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Schedule therapistSchedule("Пн - Пт", "08:00", "14:00", "Кабинет 101");
    Schedule surgeonSchedule("Вт, Чт", "10:00", "16:00", "Кабинет 205");
    Schedule ophthalmologistSchedule("Пн, Ср, Пт", "12:00", "18:00", "Кабинет 310");

    auto doc1 = std::make_shared<Doctor>(
        "Иванов", "Иван", "Иванович", "DOC-001",
        "Врач-терапевт", 12, therapistSchedule);

    auto doc2 = std::make_shared<Doctor>(
        "Смирнова", "Елена", "Сергеевна", "DOC-002",
        "Врач-хирург", 8, surgeonSchedule);

    auto doc3 = std::make_shared<Doctor>(
        "Кузнецов", "Павел", "Алексеевич", "DOC-003",
        "Врач-офтальмолог", 15, ophthalmologistSchedule);

    auto pat1 = std::make_shared<Patient>(
        "Петров", "Петр", "Петрович", "ID-1001",
        "1234567890123456", "15.05.1985", "+7 (916) 111-22-33");

    auto pat2 = std::make_shared<Patient>(
        "Сидорова", "Анна", "Владимировна", "ID-1002",
        "9876543210987654", "22.11.1992", "+7 (926) 444-55-66");

    auto pat3 = std::make_shared<Patient>(
        "Васильев", "Дмитрий", "Николаевич", "ID-1003",
        "5555444433332222", "03.09.1978", "+7 (903) 777-88-99");

    // Коллекция базового класса Person и полиморфный вывод по требованию инструкции
    std::vector<std::shared_ptr<Person>> people = { doc1, pat1, doc2, pat2, doc3, pat3 };
    for (const auto& personPtr : people)
    {
        std::cout << personPtr->ToString() << "\n";
    }
    std::cout << "\n";

    Polyclinic polyclinic("Городская клиническая поликлиника № 12", "г. Москва, ул. Здоровья, д. 7");
    polyclinic.AddDoctor(doc1);
    polyclinic.AddDoctor(doc2);
    polyclinic.AddDoctor(doc3);
    polyclinic.AddPatient(pat1);
    polyclinic.AddPatient(pat2);
    polyclinic.AddPatient(pat3);

    auto app1 = polyclinic.RegisterAppointment(doc1, pat1, "20.10.2026 09:30");
    auto app2 = polyclinic.RegisterAppointment(doc2, pat2, "21.10.2026 11:00");
    auto app3 = polyclinic.RegisterAppointment(doc3, pat1, "22.10.2026 14:15");

    std::cout << "ЗАДАНИЕ 1\n";
    std::cout << polyclinic.GetDoctorsSummary() << "\n";

    std::cout << "ЗАДАНИЕ 2\n";
    std::cout << polyclinic.GetPatientsSummary() << "\n";

    std::cout << "ЗАДАНИЕ 3\n";
    std::cout << "Информация о записи пациента к врачу:\n";
    std::cout << polyclinic.GetAppointmentInfo(app1->GetId()) << "\n";
    std::cout << "Информация о записях пациента по номеру полиса 1234567890123456:\n";
    std::cout << polyclinic.GetPatientAppointmentsInfo("1234567890123456") << "\n";

    return 0;
}
