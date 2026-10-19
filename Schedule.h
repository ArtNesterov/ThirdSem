#pragma once

#include <string>

/**
 * @brief Класс для представления расписания приема врача
 */
class Schedule
{
private:
    std::string daysOfWeek;
    std::string startTime;
    std::string endTime;
    std::string cabinet;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Schedule();

    /**
     * @brief Конструктор с параметрами
     * @param daysOfWeek Дни приема
     * @param startTime Время начала приема
     * @param endTime Время окончания приема
     * @param cabinet Номер кабинета
     */
    Schedule(const std::string& daysOfWeek, const std::string& startTime,
             const std::string& endTime, const std::string& cabinet);

    /**
     * @brief Деструктор по умолчанию
     */
    ~Schedule() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Schedule(const Schedule& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Schedule& operator=(const Schedule& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Schedule(Schedule&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Schedule& operator=(Schedule&& other) noexcept;

    /**
     * @brief Получить дни приема
     * @return Константная ссылка на строку дней приема
     */
    const std::string& GetDaysOfWeek() const;

    /**
     * @brief Установить дни приема
     * @param days Новые дни приема
     */
    void SetDaysOfWeek(const std::string& days);

    /**
     * @brief Получить время начала приема
     * @return Константная ссылка на время начала
     */
    const std::string& GetStartTime() const;

    /**
     * @brief Установить время начала приема
     * @param time Новое время начала
     */
    void SetStartTime(const std::string& time);

    /**
     * @brief Получить время окончания приема
     * @return Константная ссылка на время окончания
     */
    const std::string& GetEndTime() const;

    /**
     * @brief Установить время окончания приема
     * @param time Новое время окончания
     */
    void SetEndTime(const std::string& time);

    /**
     * @brief Получить номер кабинета
     * @return Константная ссылка на номер кабинета
     */
    const std::string& GetCabinet() const;

    /**
     * @brief Установить номер кабинета
     * @param cabinet Новый номер кабинета
     */
    void SetCabinet(const std::string& cabinet);

    /**
     * @brief Строковое представление расписания
     * @return Строка с описанием расписания и кабинета
     */
    std::string ToString() const;

    /**
     * @brief Оператор проверки равенства расписаний
     * @param other Расписание для сравнения
     * @return true, если расписания равны, иначе false
     */
    bool operator==(const Schedule& other) const;

    /**
     * @brief Оператор проверки неравенства расписаний
     * @param other Расписание для сравнения
     * @return true, если расписания не равны, иначе false
     */
    bool operator!=(const Schedule& other) const;
};
