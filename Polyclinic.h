#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"

/**
 * @brief Класс для управления поликлиникой
 */
class Polyclinic
{
private:
    std::string name;
    std::string address;
    std::vector<std::shared_ptr<Doctor>> doctors;
    std::vector<std::shared_ptr<Patient>> patients;
    std::vector<std::shared_ptr<Appointment>> appointments;
    int nextAppointmentId;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Polyclinic();

    /**
     * @brief Конструктор с параметрами
     * @param name Название поликлиники
     * @param address Адрес поликлиники
     */
    Polyclinic(const std::string& name, const std::string& address);

    /**
     * @brief Деструктор по умолчанию
     */
    ~Polyclinic() = default;

    /**
     * @brief Конструктор копирования (глубокое копирование)
     * @param other Копируемый объект
     */
    Polyclinic(const Polyclinic& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Polyclinic& operator=(const Polyclinic& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Polyclinic(Polyclinic&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Polyclinic& operator=(Polyclinic&& other) noexcept;

    /**
     * @brief Получить название поликлиники
     * @return Константная ссылка на название
     */
    const std::string& GetName() const;

    /**
     * @brief Установить название поликлиники
     * @param name Новое название
     */
    void SetName(const std::string& name);

    /**
     * @brief Получить адрес поликлиники
     * @return Константная ссылка на адрес
     */
    const std::string& GetAddress() const;

    /**
     * @brief Установить адрес поликлиники
     * @param address Новый адрес
     */
    void SetAddress(const std::string& address);

    /**
     * @brief Регистрация нового врача в поликлинике
     * @param doctor Умный указатель на врача
     */
    void AddDoctor(const std::shared_ptr<Doctor>& doctor);

    /**
     * @brief Регистрация нового пациента в поликлинике
     * @param patient Умный указатель на пациента
     */
    void AddPatient(const std::shared_ptr<Patient>& patient);

    /**
     * @brief Запись пациента к врачу на прием
     * @param doctor Врач
     * @param patient Пациент
     * @param dateTime Дата и время приема
     * @return Созданный объект записи на прием
     */
    std::shared_ptr<Appointment> RegisterAppointment(const std::shared_ptr<Doctor>& doctor,
                                                     const std::shared_ptr<Patient>& patient,
                                                     const std::string& dateTime);

    /**
     * @brief Поиск врача по идентификатору
     * @param doctorId Идентификатор врача
     * @return Указатель на врача или nullptr
     */
    std::shared_ptr<Doctor> FindDoctorById(const std::string& doctorId) const;

    /**
     * @brief Поиск врача по фамилии
     * @param surname Фамилия врача
     * @return Указатель на врача или nullptr
     */
    std::shared_ptr<Doctor> FindDoctorBySurname(const std::string& surname) const;

    /**
     * @brief Поиск пациента по номеру полиса ОМС
     * @param policyNumber Номер полиса
     * @return Указатель на пациента или nullptr
     */
    std::shared_ptr<Patient> FindPatientByPolicy(const std::string& policyNumber) const;

    /**
     * @brief Поиск записи по идентификатору
     * @param appointmentId Идентификатор записи
     * @return Указатель на запись или nullptr
     */
    std::shared_ptr<Appointment> FindAppointmentById(const int appointmentId) const;

    /**
     * @brief Поиск всех записей пациента по номеру полиса ОМС
     * @param policyNumber Номер полиса
     * @return Список записей пациента
     */
    std::vector<std::shared_ptr<Appointment>> FindAppointmentsByPatientPolicy(const std::string& policyNumber) const;

    /**
     * @brief Поиск всех записей врача по его идентификатору
     * @param doctorId Идентификатор врача
     * @return Список записей к данному врачу
     */
    std::vector<std::shared_ptr<Appointment>> FindAppointmentsByDoctorId(const std::string& doctorId) const;

    /**
     * @brief Получить сводную информацию обо всех врачах поликлиники
     * @return Строка со сводной информацией о врачах
     */
    std::string GetDoctorsSummary() const;

    /**
     * @brief Получить сводную информацию о пациентах
     * @return Строка со сводной информацией о пациентах
     */
    std::string GetPatientsSummary() const;

    /**
     * @brief Получить информацию о записи по идентификатору
     * @param appointmentId Идентификатор записи
     * @return Строка с описанием записи
     */
    std::string GetAppointmentInfo(const int appointmentId) const;

    /**
     * @brief Получить информацию о записях пациента к врачу по номеру полиса ОМС
     * @param policyNumber Номер полиса ОМС
     * @return Строка со списком записей пациента к врачам
     */
    std::string GetPatientAppointmentsInfo(const std::string& policyNumber) const;

    /**
     * @brief Получить список всех врачей
     * @return Константная ссылка на вектор врачей
     */
    const std::vector<std::shared_ptr<Doctor>>& GetDoctors() const;

    /**
     * @brief Получить список всех пациентов
     * @return Константная ссылка на вектор пациентов
     */
    const std::vector<std::shared_ptr<Patient>>& GetPatients() const;

    /**
     * @brief Получить список всех записей
     * @return Константная ссылка на вектор записей
     */
    const std::vector<std::shared_ptr<Appointment>>& GetAppointments() const;

    /**
     * @brief Получить количество врачей
     * @return Число врачей в поликлинике
     */
    size_t GetDoctorCount() const;

    /**
     * @brief Получить количество пациентов
     * @return Число зарегистрированных пациентов
     */
    size_t GetPatientCount() const;

    /**
     * @brief Получить количество записей на прием
     * @return Число созданных записей
     */
    size_t GetAppointmentCount() const;
};
