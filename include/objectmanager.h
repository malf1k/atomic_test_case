#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>


#include "colorobject.h"


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

    void createRandomSeq(const uint32_t elements_in_sequence = 10);
    Sequence sortSeqByRule(const Sequence& seq,
                           const Rule& rule =
                           {Color::RED, Color::GREEN, Color::BLUE});
    Sequence getSeqFromQueue();
    void setNewRule(std::string rule);


    void startCreation(const uint32_t number_sequences = 100,
                       const uint32_t elements_in_sequence = 10);
    void startProcessing();
    void startAll(const uint32_t number_sequences = 100,
                  const uint32_t elements_in_sequence = 10);

    void stopCreation();
    void stopProcessing();
    void stopAll();

private:

    Rule m_rule = {Color::RED, Color::GREEN, Color::BLUE};
    std::unique_ptr<Collection> m_queue;

    std::atomic<bool> m_creation_collection_finished = false;
    std::atomic<bool> m_creation_thread_started = false;
    std::atomic<bool> m_processing_thread_started = false;
    std::atomic<bool> m_creation_tread_stop = false;
    std::atomic<bool> m_processing_thread_stop = false;

    std::mutex m_mt ;
    std::condition_variable m_cv;

    void addSeqToQueue(const Sequence& seq);

    void subseqJoining(Sequence &sorted_seq,
                       const std::vector<Sequence>& sorted_subseq);

    void printSeq(const Sequence& seq);

    void log(const char* m,
             const char* f,
             std::thread::id t = std::this_thread::get_id()
             );
};
