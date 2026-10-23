#include "CppUnitTest.h"

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

#include "Person.h"
#include "Schedule.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Polyclinic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(PersonTests)
    {
    public:
        /**
         * @brief Проверка конструкторов, сеттеров и геттеров Person
         */
        TEST_METHOD(ConstructorsAndGetters_Test)
        {
            Person p1;
            Assert::IsTrue(p1.GetSurname().empty());
            Assert::IsFalse(p1.GetId().empty());

            Person p2("Иванов", "Иван", "Иванович", "ID-1");
            Assert::AreEqual(std::string("Иванов"), p2.GetSurname());
            Assert::AreEqual(std::string("Иван"), p2.GetName());
            Assert::AreEqual(std::string("Иванович"), p2.GetPatronymic());
            Assert::AreEqual(std::string("ID-1"), p2.GetId());
            Assert::AreEqual(std::string("Иванов Иван Иванович"), p2.GetFullName());

            p1.SetSurname("Петров");
            p1.SetName("Петр");
            p1.SetId("NEW-ID");
            Assert::AreEqual(std::string("Петров"), p1.GetSurname());
            Assert::AreEqual(std::string("Петр"), p1.GetName());
            Assert::AreEqual(std::string("NEW-ID"), p1.GetId());
        }

        /**
         * @brief Проверка валидации ID (id не может быть пустым)
         */
        TEST_METHOD(IdValidation_Test)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                Person p("Иванов", "Иван", "Иванович", "");
            });

            Assert::ExpectException<std::invalid_argument>([]() {
                Person p("Иванов", "Иван", "Иванович", "   ");
            });

            Person p;
            Assert::ExpectException<std::invalid_argument>([&]() {
                p.SetId("");
            });
        }

        /**
         * @brief Проверка операторов равенства Person
         */
        TEST_METHOD(Equality_Test)
        {
            Person p1("Иванов", "Иван", "Иванович", "ID-1");
            Person p2("Иванов", "Иван", "Иванович", "ID-1");
            Person p3("Петров", "Петр", "Петрович", "ID-2");

            Assert::IsTrue(p1 == p2);
            Assert::IsFalse(p1 != p2);
            Assert::IsTrue(p1 != p3);
        }

        /**
         * @brief Проверка правила пяти для Person
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            Person orig("Сидоров", "Сидор", "Сидорович", "ID-10");
            Person copy(orig);
            Assert::IsTrue(orig == copy);

            Person assigned;
            assigned = orig;
            Assert::IsTrue(orig == assigned);

            Person moved(std::move(copy));
            Assert::AreEqual(std::string("Сидоров"), moved.GetSurname());

            Person moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(std::string("Сидоров"), moveAssigned.GetSurname());
        }
    };

    TEST_CLASS(ScheduleTests)
    {
    public:
        /**
         * @brief Проверка конструктора, геттеров и сеттеров Schedule
         */
        TEST_METHOD(ConstructorsAndGetters_Test)
        {
            Schedule s1;
            Assert::IsTrue(s1.GetDaysOfWeek().empty());

            Schedule s2("Пн - Пт", "08:00", "14:00", "Кабинет 101");
            Assert::AreEqual(std::string("Пн - Пт"), s2.GetDaysOfWeek());
            Assert::AreEqual(std::string("08:00"), s2.GetStartTime());
            Assert::AreEqual(std::string("14:00"), s2.GetEndTime());
            Assert::AreEqual(std::string("Кабинет 101"), s2.GetCabinet());

            s1.SetCabinet("Кабинет 200");
            Assert::AreEqual(std::string("Кабинет 200"), s1.GetCabinet());
            Assert::IsTrue(s2.ToString().find("Кабинет 101") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти и сравнения Schedule
         */
        TEST_METHOD(RuleOfFiveAndEquality_Test)
        {
            Schedule s1("Пн", "09:00", "15:00", "101");
            Schedule s2(s1);
            Assert::IsTrue(s1 == s2);

            Schedule s3;
            s3 = s1;
            Assert::IsTrue(s1 == s3);

            Schedule moved(std::move(s2));
            Assert::AreEqual(std::string("101"), moved.GetCabinet());

            Schedule moveAssigned;
            moveAssigned = std::move(s3);
            Assert::AreEqual(std::string("101"), moveAssigned.GetCabinet());
        }
    };

    TEST_CLASS(DoctorTests)
    {
    public:
        /**
         * @brief Проверка создания врача, наследования и полиморфизма
         */
        TEST_METHOD(DoctorAndPolymorphism_Test)
        {
            Schedule s("Пн-Пт", "08:00", "14:00", "101");
            auto doc = std::make_shared<Doctor>("Иванов", "Иван", "Иванович", "DOC-1", "Терапевт", 10, s);

            Assert::AreEqual(std::string("Терапевт"), doc->GetSpecialization());
            Assert::AreEqual(10, doc->GetExperienceYears());
            Assert::AreEqual(std::string("101"), doc->GetCabinet());

            std::shared_ptr<Person> person = doc;
            Assert::IsTrue(person->ToString().find("Терапевт") != std::string::npos);
            Assert::IsTrue(doc->GetSummary().find("Иванов") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти для Doctor
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            Schedule s("Пн", "08:00", "12:00", "101");
            Doctor d1("Иванов", "И.", "И.", "D-1", "Терапевт", 5, s);
            Doctor copy(d1);
            Assert::IsTrue(d1 == copy);

            Doctor assigned;
            assigned = d1;
            Assert::IsTrue(d1 == assigned);

            Doctor moved(std::move(copy));
            Assert::AreEqual(std::string("Терапевт"), moved.GetSpecialization());

            Doctor moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(std::string("Терапевт"), moveAssigned.GetSpecialization());
        }
    };

    TEST_CLASS(PatientTests)
    {
    public:
        /**
         * @brief Проверка создания пациента, наследования и полиморфизма
         */
        TEST_METHOD(PatientAndPolymorphism_Test)
        {
            auto pat = std::make_shared<Patient>("Петров", "Петр", "Петрович", "ID-1", "1234567890123456", "15.05.1985", "+7-916-111");

            Assert::AreEqual(std::string("1234567890123456"), pat->GetPolicyNumber());
            Assert::AreEqual(std::string("15.05.1985"), pat->GetBirthDate());
            Assert::AreEqual(std::string("+7-916-111"), pat->GetPhone());

            std::shared_ptr<Person> person = pat;
            Assert::IsTrue(person->ToString().find("1234567890123456") != std::string::npos);
            Assert::IsTrue(pat->GetSummary().find("Петров") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти для Patient
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            Patient p1("Петров", "П.", "П.", "P-1", "123456", "01.01.1990", "+7");
            Patient copy(p1);
            Assert::IsTrue(p1 == copy);

            Patient assigned;
            assigned = p1;
            Assert::IsTrue(p1 == assigned);

            Patient moved(std::move(copy));
            Assert::AreEqual(std::string("123456"), moved.GetPolicyNumber());

            Patient moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(std::string("123456"), moveAssigned.GetPolicyNumber());
        }
    };

    TEST_CLASS(AppointmentTests)
    {
    public:
        /**
         * @brief Проверка создания записи, геттеров и строкового представления
         */
        TEST_METHOD(Appointment_Test)
        {
            Schedule s("Пн - Пт", "08:00", "14:00", "101");
            auto doc = std::make_shared<Doctor>("Иванов", "Иван", "Иванович", "DOC-1", "Терапевт", 10, s);
            auto pat = std::make_shared<Patient>("Петров", "Петр", "Петрович", "ID-1", "123456", "01.01.1980", "+7-999-111");

            Appointment app(101, doc, pat, "25.10.2026 10:00");
            Assert::AreEqual(101, app.GetId());
            Assert::IsTrue(app.GetDoctor() == doc);
            Assert::IsTrue(app.GetPatient() == pat);
            Assert::AreEqual(std::string("25.10.2026 10:00"), app.GetAppointmentDateTime());

            Assert::IsTrue(app.ToString().find("Иванов") != std::string::npos);
            Assert::IsTrue(app.GetSummary().find("25.10.2026 10:00") != std::string::npos);
        }

        /**
         * @brief Проверка валидации ID записи и проверки отсутствия дубликатов
         */
        TEST_METHOD(IdValidationAndUniqueness_Test)
        {
            Schedule s("Пн", "08:00", "12:00", "101");
            auto doc = std::make_shared<Doctor>("Иванов", "И.", "И.", "D-1", "Терапевт", 5, s);
            auto pat = std::make_shared<Patient>("Петров", "П.", "П.", "P-1", "123", "01.01.1990", "+7");

            Assert::ExpectException<std::invalid_argument>([&]() {
                Appointment invalidApp(0, doc, pat, "20.10.2026 10:00");
            });

            Assert::ExpectException<std::invalid_argument>([&]() {
                Appointment invalidApp(-5, doc, pat, "20.10.2026 10:00");
            });

            Appointment app1(201, doc, pat, "20.10.2026 10:00");

            // Проверка, что ID уже занят (id проверка, что такого нет)
            Assert::ExpectException<std::invalid_argument>([&]() {
                Appointment duplicateApp(201, doc, pat, "20.10.2026 11:00");
            });
        }

        /**
         * @brief Проверка правила пяти для Appointment
         */
        TEST_METHOD(RuleOfFive_Test)
        {
            Schedule s("Пн", "08:00", "12:00", "205");
            auto doc = std::make_shared<Doctor>("Смирнов", "Е.", "П.", "D-2", "Хирург", 5, s);
            auto pat = std::make_shared<Patient>("Васильев", "Д.", "Н.", "P-2", "999888", "10.02.1995", "+7");

            Appointment app1(301, doc, pat, "20.10.2026 12:00");
            Appointment copy(app1);
            Assert::IsTrue(app1 == copy);

            Appointment assigned;
            assigned = app1;
            Assert::IsTrue(app1 == assigned);

            Appointment moved(std::move(copy));
            Assert::AreEqual(301, moved.GetId());
            Assert::AreEqual(std::string("20.10.2026 12:00"), moved.GetAppointmentDateTime());

            Appointment moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(301, moveAssigned.GetId());
        }
    };

    TEST_CLASS(PolyclinicTests)
    {
    public:
        /**
         * @brief Проверка добавления и поиска врачей и пациентов
         */
        TEST_METHOD(AddAndFind_Test)
        {
            Polyclinic clinic("Поликлиника № 12", "ул. Мира, 5");
            Assert::AreEqual(std::string("Поликлиника № 12"), clinic.GetName());

            Schedule s("Пн-Пт", "08:00", "14:00", "101");
            auto doc = std::make_shared<Doctor>("Иванов", "И.", "И.", "D1", "Терапевт", 10, s);
            auto pat = std::make_shared<Patient>("Петров", "П.", "П.", "P1", "123456", "01.01.1990", "+7");

            clinic.AddDoctor(doc);
            clinic.AddPatient(pat);

            Assert::AreEqual(static_cast<size_t>(1), clinic.GetDoctorCount());
            Assert::AreEqual(static_cast<size_t>(1), clinic.GetPatientCount());
            Assert::IsTrue(clinic.FindDoctorById("D1") == doc);
            Assert::IsTrue(clinic.FindDoctorBySurname("Иванов") == doc);
            Assert::IsTrue(clinic.FindPatientByPolicy("123456") == pat);
        }

        /**
         * @brief Проверка Задания 1: сводная информация обо всех врачах
         */
        TEST_METHOD(Task1_DoctorsSummary_Test)
        {
            Polyclinic clinic("Поликлиника № 12", "ул. Мира, 5");
            Assert::IsTrue(clinic.GetDoctorsSummary().find("Список врачей пуст") != std::string::npos);

            Schedule s("Пн-Пт", "08:00", "14:00", "101");
            clinic.AddDoctor(std::make_shared<Doctor>("Иванов", "Иван", "Иванович", "D1", "Терапевт", 10, s));

            std::string summary = clinic.GetDoctorsSummary();
            Assert::IsTrue(summary.find("Всего врачей: 1") != std::string::npos);
            Assert::IsTrue(summary.find("Иванов Иван Иванович") != std::string::npos);
            Assert::IsTrue(summary.find("Терапевт") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 2: сводная информация о пациентах
         */
        TEST_METHOD(Task2_PatientsSummary_Test)
        {
            Polyclinic clinic;
            Assert::IsTrue(clinic.GetPatientsSummary().find("Список пациентов пуст") != std::string::npos);

            clinic.AddPatient(std::make_shared<Patient>("Петров", "Петр", "Петрович", "P1", "1234567890123456", "15.05.1985", "+7(916)111"));

            std::string summary = clinic.GetPatientsSummary();
            Assert::IsTrue(summary.find("Всего зарегистрированных пациентов: 1") != std::string::npos);
            Assert::IsTrue(summary.find("Петров Петр Петрович") != std::string::npos);
            Assert::IsTrue(summary.find("1234567890123456") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 3: информация о записи пациента к врачу
         */
        TEST_METHOD(Task3_AppointmentInfo_Test)
        {
            Polyclinic clinic;
            Schedule s("Пн - Пт", "08:00", "14:00", "101");
            auto doc = std::make_shared<Doctor>("Иванов", "Иван", "Иванович", "D1", "Терапевт", 10, s);
            auto pat = std::make_shared<Patient>("Петров", "Петр", "Петрович", "P1", "1234567890123456", "15.05.1985", "+7-916-111");

            clinic.AddDoctor(doc);
            clinic.AddPatient(pat);

            auto app = clinic.RegisterAppointment(doc, pat, "25.10.2026 10:30");
            Assert::IsTrue(app->GetId() > 0);
            Assert::IsTrue(clinic.FindAppointmentById(app->GetId()) == app);

            std::string appInfo = clinic.GetAppointmentInfo(app->GetId());
            Assert::IsTrue(appInfo.find("Иванов Иван Иванович") != std::string::npos);
            Assert::IsTrue(appInfo.find("Петров Петр Петрович") != std::string::npos);

            std::string patInfo = clinic.GetPatientAppointmentsInfo("1234567890123456");
            Assert::IsTrue(patInfo.find("Иванов Иван Иванович") != std::string::npos);

            Assert::IsTrue(clinic.GetAppointmentInfo(9999).find("не найдена") != std::string::npos);
            Assert::IsTrue(clinic.GetPatientAppointmentsInfo("000000").find("не найден") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти и глубокого копирования Polyclinic
         */
        TEST_METHOD(RuleOfFive_DeepCopy_Test)
        {
            Polyclinic clinic1("Исходная", "Адрес 1");
            Schedule s("Пн-Пт", "08:00", "14:00", "101");
            auto doc = std::make_shared<Doctor>("Иванов", "И.", "И.", "D1", "Терапевт", 10, s);
            auto pat = std::make_shared<Patient>("Петров", "П.", "П.", "P1", "123", "01.01.1990", "+7");

            clinic1.AddDoctor(doc);
            clinic1.AddPatient(pat);
            clinic1.RegisterAppointment(doc, pat, "20.10.2026 10:00");

            Polyclinic clinic2(clinic1);
            Assert::AreEqual(clinic1.GetDoctorCount(), clinic2.GetDoctorCount());
            Assert::AreEqual(clinic1.GetPatientCount(), clinic2.GetPatientCount());
            Assert::AreEqual(clinic1.GetAppointmentCount(), clinic2.GetAppointmentCount());
            Assert::IsTrue(clinic1.GetDoctors()[0] != clinic2.GetDoctors()[0]);

            Polyclinic clinic3;
            clinic3 = clinic1;
            Assert::AreEqual(clinic1.GetDoctorCount(), clinic3.GetDoctorCount());

            Polyclinic clinic4(std::move(clinic2));
            Assert::AreEqual(static_cast<size_t>(1), clinic4.GetDoctorCount());

            Polyclinic clinic5;
            clinic5 = std::move(clinic3);
            Assert::AreEqual(static_cast<size_t>(1), clinic5.GetDoctorCount());
        }
    };
}
