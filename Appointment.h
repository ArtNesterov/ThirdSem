#pragma once

#include <string>
#include <memory>
#include <set>
#include <map>
#include "Doctor.h"
#include "Patient.h"

/**
 * @brief Класс для представления записи пациента к врачу
 */
class Appointment
{
private:
    static std::set<int> existingIds;
    static std::map<int, int> idRefCount;
    int id;
    std::shared_ptr<Doctor> doctor;
    std::shared_ptr<Patient> patient;
    std::string appointmentDateTime;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Appointment();

    /**
     * @brief Конструктор с параметрами и проверкой уникальности ID
     * @param id Идентификатор записи
     * @param doctor Указатель на врача
     * @param patient Указатель на пациента
     * @param appointmentDateTime Дата и время приема
     */
    Appointment(const int id,
                const std::shared_ptr<Doctor>& doctor,
                const std::shared_ptr<Patient>& patient,
                const std::string& appointmentDateTime);

    /**
     * @brief Деструктор с освобождением идентификатора из реестра
     */
    ~Appointment();

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Appointment(const Appointment& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Appointment& operator=(const Appointment& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Appointment(Appointment&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Appointment& operator=(Appointment&& other) noexcept;

    /**
     * @brief Получить идентификатор записи
     * @return Идентификатор записи
     */
    int GetId() const;

    /**
     * @brief Установить идентификатор записи с проверкой на дубликат
     * @param id Новый идентификатор записи
     */
    void SetId(const int id);

    /**
     * @brief Получить врача
     * @return Константная ссылка на умный указатель врача
     */
    const std::shared_ptr<Doctor>& GetDoctor() const;

    /**
     * @brief Установить врача
     * @param doctor Указатель на врача
     */
    void SetDoctor(const std::shared_ptr<Doctor>& doctor);

    /**
     * @brief Получить пациента
     * @return Константная ссылка на умный указатель пациента
     */
    const std::shared_ptr<Patient>& GetPatient() const;

    /**
     * @brief Установить пациента
     * @param patient Указатель на пациента
     */
    void SetPatient(const std::shared_ptr<Patient>& patient);

    /**
     * @brief Получить дату и время приема
     * @return Константная ссылка на строку даты и времени
     */
    const std::string& GetAppointmentDateTime() const;

    /**
     * @brief Установить дату и время приема
     * @param dateTime Новая дата и время
     */
    void SetAppointmentDateTime(const std::string& dateTime);

    /**
     * @brief Проверить, существует ли запись с указанным ID
     * @param id Идентификатор для проверки
     * @return true, если ID уже занят, иначе false
     */
    static bool IsIdExists(const int id);

    /**
     * @brief Очистить статический реестр занятых идентификаторов
     */
    static void ResetRegistry();

    /**
     * @brief Полная строковая информация о записи к врачу
     * @return Строка с описанием записи
     */
    std::string ToString() const;

    /**
     * @brief Сводная информация о записи к врачу
     * @return Краткая строка с описанием записи
     */
    std::string GetSummary() const;

    /**
     * @brief Оператор проверки равенства записей
     * @param other Запись для сравнения
     * @return true, если записи равны, иначе false
     */
    bool operator==(const Appointment& other) const;

    /**
     * @brief Оператор проверки неравенства записей
     * @param other Запись для сравнения
     * @return true, если записи не равны, иначе false
     */
    bool operator!=(const Appointment& other) const;
};
