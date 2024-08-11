#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>


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

    void startAll();
    void stopAll();
    void startCreation(int number_sequences);
    void stopCreation();
    void startProcessint();
    void stopProcessing();
    void setNewRule(std::string rule);


private:

    Collection *m_queue = nullptr;

    int cnt;

    bool m_creation_collection_finished = false;

    bool m_creation_thread_started = false;
    bool m_processing_thread_started = false;

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
