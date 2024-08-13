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

    void createRandomSeq(const int& number = 100);
    void addSeqToQeue(const Sequence & seq);


    Sequence getSeqFromQueue();
    Sequence sortSeqByRule(const Sequence& seq,
                           const Rule &rule =
                           {Color::RED, Color::GREEN, Color::BLUE}
                           );

    void printSeq(const Sequence& seq);

    void startAll(const int& number_sequences = 100);
    void stopAll();
    void startCreation(const int& number_sequences);
    void stopCreation();
    void startProcessing();
    void stopProcessing();
    void setNewRule(std::string rule);


private:

    Collection *m_queue = nullptr;

    int cnt;

    std::atomic<bool> m_creation_collection_finished = false;

    std::atomic<bool> m_creation_thread_started = false;
    std::atomic<bool> m_processing_thread_started = false;
    std::atomic<bool> m_creation_tread_stop = false;
    std::atomic<bool> m_processing_thread_stop = false;

    Rule m_rule = {Color::RED, Color::GREEN, Color::BLUE};

    std::mutex m_mt ;
    std::condition_variable m_cv;


    void subseqJoining(Sequence &sorted_seq,
                       const std::vector<Sequence>& sorted_subseq);

    void log(const char* m,
             const char* f,
             std::thread::id t = std::this_thread::get_id()
             );
};
