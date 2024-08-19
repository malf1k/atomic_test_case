#include "objectmanager.h"
#include <iostream>
#include <random>
#include <thread>

using namespace std::chrono_literals;

ObjectManager::ObjectManager() {

    m_queue = std::make_unique<Collection>();
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::createRandomSeq(const uint32_t elements_in_sequence)
{
    uint32_t seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed1);
    std::uniform_int_distribution<int> dist(1, 3);

    Sequence seq;


    for(auto i = 0; i < elements_in_sequence; i++){
        seq.push_back(static_cast<Color>(dist(gen)));
    }
    std::unique_lock<std::mutex> lock(m_mt);
    printSeq(seq);
    addSeqToQueue(seq);
    m_cv.notify_one();
}

void ObjectManager::addSeqToQueue(const Sequence &seq)
{
    m_queue->push(seq);
}

Sequence ObjectManager::getSeqFromQueue()
{
    std::unique_lock<std::mutex> lock(m_mt);
    m_cv.wait(lock, [this] () {
        return !m_queue->empty();
    });

    auto front_q = m_queue->front();
    m_queue->pop();

    return std::move(front_q);
}

Sequence ObjectManager::sortSeqByRule(const Sequence &seq, const Rule &rule)
{
    Sequence sorted_seq;

    std::vector<Sequence> sorted_subseq;
    sorted_subseq.reserve(rule.size());

    for (size_t i = 0; i < rule.size(); ++i)
        sorted_subseq.emplace_back();

    for(auto item : seq) {
        if(item.getColor() == Color::NONE)
            continue;

        if (item.getColor() == rule.at(0))
            sorted_subseq.at(0).push_back(item);
        else if (item.getColor() == rule.at(1))
            sorted_subseq.at(1).push_back(item);
        else
            sorted_subseq.at(2).push_back(item);
    }
    subseqJoining(sorted_seq, sorted_subseq);
    return sorted_seq;
}


void ObjectManager::startAll(const uint32_t number_sequences, const uint32_t elements_in_sequence)
{
    startCreation(number_sequences, elements_in_sequence);
    startProcessing();
}

void ObjectManager::stopAll()
{
    stopCreation();
    stopProcessing();
}



void ObjectManager::startCreation(const uint32_t number_sequences,
                                  const uint32_t elements_in_sequence)
{
    if(m_creation_thread_started == true)
        std::cout << "creation_thread is work" << std::endl;
    else {
        m_creation_thread_started = true;
        m_creation_tread_stop = false;
        m_creation_collection_finished = false;
        std::thread t([this, number_sequences, elements_in_sequence] {
            for(auto i = 0; i < number_sequences; i++)
            {
                if(m_creation_tread_stop == true)
                    break;
                createRandomSeq(elements_in_sequence);
            }
            m_creation_collection_finished = true;
            m_creation_thread_started = false;
        });

        if(t.joinable())
            t.detach();
    }
}

void ObjectManager::stopCreation()
{
    m_creation_tread_stop = true;
}

void ObjectManager::startProcessing()
{
    if(m_processing_thread_started == true)
        std::cout << "processing_thread is work" << std::endl;
    else {
        m_processing_thread_started = true;
        std::thread t([this] {
            m_processing_thread_stop = false;

            while(!m_processing_thread_stop)
            {
                auto seq = sortSeqByRule(getSeqFromQueue(), m_rule);
                printSeq(seq);
                std::unique_lock<std::mutex> lock(m_mt);
                if(m_queue->empty() && m_creation_collection_finished)
                {
                    m_processing_thread_started = false;
                    break;
                }
            }
            m_processing_thread_started = false;
        });

        if(t.joinable())
            t.detach();
    }
}

void ObjectManager::stopProcessing()
{
    m_processing_thread_stop = true;
}

void ObjectManager::setNewRule(std::string rule)
{
    m_rule.clear();
    for(auto i : rule)
    {
        if (i == 'R' || i == 'r')
            m_rule.push_back(Color::RED);
        else if (i == 'G' || i == 'g')
            m_rule.push_back(Color::GREEN);
        else if (i == 'B' || i == 'b')
            m_rule.push_back(Color::BLUE);
    }
}

void ObjectManager::subseqJoining(Sequence &sorted_seq, const std::vector<Sequence> &sorted_subseq)
{
    for(auto item_seq : sorted_subseq)
        sorted_seq.insert(sorted_seq.end(),
                          item_seq.begin(),
                          item_seq.end());
}



void ObjectManager::printSeq(const Sequence &seq)
{
    std::string str;
    for(auto item: seq) {
        switch (item.getColor()) {
        case Color::RED:
            str.push_back('R');
            break;
        case Color::GREEN:
            str.push_back('G');
            break;
        case Color::BLUE:
            str.push_back('B');
            break;
        default:
            str.push_back('N');
            break;
        }
        str.push_back(' ');
    }
    std::cout << str <<std::endl;
}


void ObjectManager::log(const char *m, const char *f, std::thread::id t)
{
    std::cout << f << "\t" << t << "\t" << m << std::endl;
}
