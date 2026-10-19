#pragma once

#include "Person.h"
#include "Schedule.h"

/**
 * @brief Класс для представления врача поликлиники
 */
class Doctor : public Person
{
private:
    std::string specialization;
    int experienceYears;
    Schedule schedule;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Doctor();

    /**
     * @brief Конструктор с параметрами
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param id Идентификатор / табельный номер
     * @param specialization Специализация врача
     * @param experienceYears Стаж работы в годах
     * @param schedule Расписание приема
     */
    Doctor(const std::string& surname, const std::string& name,
           const std::string& patronymic, const std::string& id,
           const std::string& specialization, const int experienceYears,
           const Schedule& schedule);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Doctor() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Doctor(const Doctor& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Doctor& operator=(const Doctor& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Doctor(Doctor&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Doctor& operator=(Doctor&& other) noexcept;

    /**
     * @brief Получить специальность врача
     * @return Константная ссылка на строку специальности
     */
    const std::string& GetSpecialization() const;

    /**
     * @brief Установить специальность врача
     * @param specialization Новая специальность
     */
    void SetSpecialization(const std::string& specialization);

    /**
     * @brief Получить стаж работы
     * @return Количество лет стажа
     */
    int GetExperienceYears() const;

    /**
     * @brief Установить стаж работы
     * @param years Количество лет стажа
     */
    void SetExperienceYears(const int years);

    /**
     * @brief Получить расписание приема (константная версия)
     * @return Константная ссылка на расписание
     */
    const Schedule& GetSchedule() const;

    /**
     * @brief Получить расписание приема (неконстантная версия)
     * @return Ссылка на расписание
     */
    Schedule& GetSchedule();

    /**
     * @brief Установить расписание приема
     * @param schedule Новое расписание
     */
    void SetSchedule(const Schedule& schedule);

    /**
     * @brief Получить номер кабинета
     * @return Константная ссылка на строку номера кабинета
     */
    const std::string& GetCabinet() const;

    /**
     * @brief Полная строковая информация о враче
     * @return Строка с подробной информацией
     */
    std::string ToString() const override;

    /**
     * @brief Сводная информация о враче
     * @return Строка со сводкой для отчетов
     */
    std::string GetSummary() const override;

    /**
     * @brief Оператор проверки равенства врачей
     * @param other Врач для сравнения
     * @return true, если врачи равны, иначе false
     */
    bool operator==(const Doctor& other) const;

    /**
     * @brief Оператор проверки неравенства врачей
     * @param other Врач для сравнения
     * @return true, если врачи не равны, иначе false
     */
    bool operator!=(const Doctor& other) const;
};
