#pragma once

#include <string>

/**
 * @brief Базовый класс для представления человека
 */
class Person
{
protected:
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string id;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Person();

    /**
     * @brief Конструктор с параметрами
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param id Идентификатор 
     */
    Person(const std::string& surname, const std::string& name,
           const std::string& patronymic = "", const std::string& id = "");

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Person() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Person(const Person& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Person& operator=(const Person& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Person(Person&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Person& operator=(Person&& other) noexcept;

    /**
     * @brief Получить фамилию
     * @return Константная ссылка на фамилию
     */
    const std::string& GetSurname() const;

    /**
     * @brief Установить фамилию
     * @param surname Новая фамилия
     */
    void SetSurname(const std::string& surname);

    /**
     * @brief Получить имя
     * @return Константная ссылка на имя
     */
    const std::string& GetName() const;

    /**
     * @brief Установить имя
     * @param name Новое имя
     */
    void SetName(const std::string& name);

    /**
     * @brief Получить отчество
     * @return Константная ссылка на отчество
     */
    const std::string& GetPatronymic() const;

    /**
     * @brief Установить отчество
     * @param patronymic Новое отчество
     */
    void SetPatronymic(const std::string& patronymic);

    /**
     * @brief Получить идентификатор
     * @return Константная ссылка на идентификатор
     */
    const std::string& GetId() const;

    /**
     * @brief Установить идентификатор
     * @param id Новый идентификатор
     */
    void SetId(const std::string& id);

    /**
     * @brief Получить полное ФИО
     * @return Строка формата "Фамилия Имя Отчество"
     */
    std::string GetFullName() const;

    /**
     * @brief Виртуальный метод строкового представления объекта
     * @return Строка с информацией о человеке
     */
    virtual std::string ToString() const;

    /**
     * @brief Виртуальный метод получения сводной информации
     * @return Строка со сводкой
     */
    virtual std::string GetSummary() const;

    /**
     * @brief Оператор проверки равенства объектов
     * @param other Объект для сравнения
     * @return true, если объекты равны, иначе false
     */
    bool operator==(const Person& other) const;

    /**
     * @brief Оператор проверки неравенства объектов
     * @param other Объект для сравнения
     * @return true, если объекты не равны, иначе false
     */
    bool operator!=(const Person& other) const;
};
