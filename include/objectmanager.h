#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>


#include "colorobject.h"

/**
 * Sequence - набор объектов ColorObject
 * Collection - очередь которая состоит из Sequence
 */
using Sequence = std::vector<ColorObject>;
using Collection = std::queue<Sequence>;

using Rule = std::vector<Color>;


/**
 * @brief The ObjectManager class
 * Создает и управляет коллекциями объктов
 */
class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    /**
     * @brief createRandomSeq - создает последовательность элементов
     * @param elements_in_sequence - количество элементов в последовательности
     */
    void createRandomSeq(const uint32_t elements_in_sequence = 10);
    /**
     * @brief sortSeqByRule - сортирует последовательность seq по заданному правилу rule
     * @param seq - последовательность для сортировки
     * @param rule - правило по которуму следует выполнить сортировку
     * @return отсортированная последовательность
     * \details сортировка реализована путем разделения
     */
    Sequence sortSeqByRule(const Sequence& seq,
                           const Rule& rule =
                           {Color::RED, Color::GREEN, Color::BLUE});
    /**
     * @brief getSeqFromQueue
     * @return возвращает последовательность из очереди (если очередь не пуста
     */
    Sequence getSeqFromQueue();
    /**
     * @brief setNewRule - устанавливает новое правило для сортировки
     * @param rule - новое правило
     */
    void setNewRule(std::string rule);


    /**
     * @brief startCreation - создает поток генерации коллекции данных и отпускает его
     * @param number_sequences - количество элементов в очереди
     * @param elements_in_sequence - количество элементов в каждом элементе очереди
     */
    void startCreation(const uint32_t number_sequences = 100,
                       const uint32_t elements_in_sequence = 10);
    /**
     * @brief startProcessing - создает поток сортировки данных
     */
    void startProcessing();
    /**
     * @brief startAll - вызывает функции startCreation и startProcessing
     * @param number_sequences - количество элементов в очереди
     * @param elements_in_sequence - количество элементов в каждом элементе очереди
     */
    void startAll(const uint32_t number_sequences = 100,
                  const uint32_t elements_in_sequence = 10);
    /**
     * @brief stopCreation - устанавливает переменную m_creation_tread_stop
     * в true - следует остановить поток создания
     */
    void stopCreation();
    /**
     * @brief stopProcessing - устанавливает переменную m_processing_thread_stop
     * в true - следует остановить поток сортировки
     */
    void stopProcessing();
    /**
     * @brief stopAll - вызывает функции stopCreation и stopProcessing
     */
    void stopAll();

private:

    Rule m_rule = {Color::RED, Color::GREEN, Color::BLUE};
    std::unique_ptr<Collection> m_queue;    ///< очередь для хранения последовательностей

    /**
     * @brief m_creation_collection_finished - статус выполнения потока создания
     *  - true - поток закончил создание
     *  - false - поток не закончил создание
     */
    std::atomic<bool> m_creation_collection_finished = false;
    /**
     * @brief m_creation_thread_started - статус потока создания
     * - true - поток создания запущен
     * - false - поток создания не запущен
     */
    std::atomic<bool> m_creation_thread_started = false;
    /**
     * @brief m_processing_thread_started - статус потока сортировки
     * - true - поток сортировки запущен
     * - false - поток сортировки не запущен
     */
    std::atomic<bool> m_processing_thread_started = false;
    /**
     * @brief m_stop_creation_tread -
     * - true - требуется остановить поток сортировки
     * - false - не требуется остановить поток сортировки
     */
    std::atomic<bool> m_stop_creation_tread = false;
    /**
     * @brief m_stop_processing_thread
     * - true - требуется остановить поток создания
     * - false - не требуется остановить поток создания
     */
    std::atomic<bool> m_stop_processing_thread = false;

    /**
     * @brief m_mt - для ограничения доступа к m_queue
     */
    std::mutex m_mt ;
    /**
     * @brief m_cv - позволяет синхронизовать потоки и
     * использовать механизм ожидания и оповещения потоков
     */
    std::condition_variable m_cv;

    /**
     * @brief addSeqToQueue - добавление последовательности в очередь
     * @param seq - последовательность для добавления в очередь
     */
    void addSeqToQueue(const Sequence& seq);

    /**
     * @brief printSeq - вспомогательная функция для вывода и отображдения последовательности
     * @param seq - последовательность которую требуется отобразить
     */
    void printSeq(const Sequence& seq);

    /**
     * @brief log - вспомогательная функция для отображения форматированного сообщения
     * формат отображения: "Имя функции      Номер потока   Сообщение"
     * @param m - сообщение для вывода
     * @param f - функция из которой вызвана функция log
     * @param t - номер потока в котором вызвана функция log
     */
    void log(const char* m,
             const char* f,
             std::thread::id t = std::this_thread::get_id()
             );
};
