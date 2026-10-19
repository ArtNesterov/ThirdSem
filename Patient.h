#pragma once

#include "Person.h"

/**
 * @brief Класс для представления пациента поликлиники
 */
class Patient : public Person
{
private:
    std::string policyNumber;
    std::string birthDate;
    std::string phone;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Patient();

    /**
     * @brief Конструктор с параметрами
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param id Идентификатор (паспорт/СНИЛС)
     * @param policyNumber Номер полиса ОМС
     * @param birthDate Дата рождения
     * @param phone Номер контактного телефона
     */
    Patient(const std::string& surname, const std::string& name,
            const std::string& patronymic, const std::string& id,
            const std::string& policyNumber, const std::string& birthDate,
            const std::string& phone);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Patient() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Patient(const Patient& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Patient& operator=(const Patient& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Patient(Patient&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Patient& operator=(Patient&& other) noexcept;

    /**
     * @brief Получить номер полиса ОМС
     * @return Константная ссылка на строку полиса
     */
    const std::string& GetPolicyNumber() const;

    /**
     * @brief Установить номер полиса ОМС
     * @param policy Новый номер полиса
     */
    void SetPolicyNumber(const std::string& policy);

    /**
     * @brief Получить дату рождения
     * @return Константная ссылка на строку даты рождения
     */
    const std::string& GetBirthDate() const;

    /**
     * @brief Установить дату рождения
     * @param date Новая дата рождения
     */
    void SetBirthDate(const std::string& date);

    /**
     * @brief Получить номер телефона
     * @return Константная ссылка на номер телефона
     */
    const std::string& GetPhone() const;

    /**
     * @brief Установить номер телефона
     * @param phone Новый номер телефона
     */
    void SetPhone(const std::string& phone);

    /**
     * @brief Полная строковая информация о пациенте
     * @return Строка с подробной информацией
     */
    std::string ToString() const override;

    /**
     * @brief Сводная информация о пациенте
     * @return Строка со сводкой для отчетов
     */
    std::string GetSummary() const override;

    /**
     * @brief Оператор проверки равенства пациентов
     * @param other Пациент для сравнения
     * @return true, если пациенты равны, иначе false
     */
    bool operator==(const Patient& other) const;

    /**
     * @brief Оператор проверки неравенства пациентов
     * @param other Пациент для сравнения
     * @return true, если пациенты не равны, иначе false
     */
    bool operator!=(const Patient& other) const;
};
