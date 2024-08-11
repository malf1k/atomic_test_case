#include "objectmanager.h"
#include <iostream>
#include <random>
#include <thread>

using namespace std::chrono_literals;

ObjectManager::ObjectManager() {

    cnt = 0;
    m_queue = new Collection;
}

ObjectManager::~ObjectManager()
{
    if(m_queue) {
        delete m_queue;
        m_queue = nullptr;
    }

}

void ObjectManager::createRandomSeq(const int &number)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 3);

    Sequence seq ;

    for(auto i = 0; i < number; i++)
        seq.push_back(static_cast<Color>(dist(gen)));


    log(std::this_thread::get_id(), __FUNCTION__, "before lock");
    std::unique_lock<std::mutex> lock(m_mt);
    log(std::this_thread::get_id(), __FUNCTION__, "after lock");

    addSeqToQeue(seq);
    // printSeq(seq);
    // std::cout<< std::this_thread::get_id() << " Generating thread m_queue->size() "<< m_queue->size() << std::endl;
    log(std::this_thread::get_id(), __FUNCTION__, "before notyfy_one");
    m_cv.notify_one();
}

void ObjectManager::addSeqToQeue(const Sequence &seq)
{
    if (m_queue == nullptr)
        m_queue = new Collection;
    m_queue->push(seq);
}

Sequence ObjectManager::getSeqFromQueue()
{
    cnt ++;
    std::cout <<cnt << "\t";
    log(std::this_thread::get_id(), __FUNCTION__, "lock(m_mt)");

    std::unique_lock<std::mutex> lock(m_mt);
    m_cv.wait(lock, [this] () {
        log(std::this_thread::get_id(), __FUNCTION__, "m_cv.wait");
        return !m_queue->empty();
    });

    log(std::this_thread::get_id(), __FUNCTION__, "after m_cv.wait");

    auto front_q = m_queue->front();
    m_queue->pop();

    return std::move(front_q);
}

Sequence ObjectManager::sortSeqByRule(const Sequence &seq, const Rule &rule)
{
    Sequence sorted_seq;

    std::vector<Sequence> sorted_subseq;
    sorted_subseq.reserve(rule.size());

    for (size_t i = 0; i < rule.size(); ++i) {
        sorted_subseq.emplace_back();
    }

    for(auto item : seq)
    {
        if(item.getColor() == Color::NONE)
        {
            continue;
        }

        if ( item.getColor() < rule[1])
        {
            sorted_subseq.at(0).push_back(item);
        }
        else if (item.getColor() > rule[1])
        {
            sorted_subseq.at(2).push_back(item);
        }
        else
        {
            sorted_subseq.at(1).push_back(item);
        }

    }

    subseqJoining(sorted_seq, sorted_subseq);

    return sorted_seq;
}

void ObjectManager::printSeq(const Sequence &seq)
{
    std::string str;
    for(auto item: seq)
    {
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

void ObjectManager::start()
{
    std::thread t1([this]{
        for(auto i = 0; i < 100; i++)
            createRandomSeq(100);
    });

    std::thread t2([this] {
        while(true)
        {
            auto s = getSeqFromQueue();
            auto ss = sortSeqByRule(s);
            // printSeq(ss);
            if(m_queue->empty())
                break;
        }

    });

    // t1.detach();
    t1.join();
    t2.join();
}

void ObjectManager::subseqJoining(Sequence &sorted_seq, const std::vector<Sequence> &sorted_subseq)
{
    for(auto item_seq : sorted_subseq)
    {
        // FIXME: тут может быть проблема, требуется отладка
        sorted_seq.insert(sorted_seq.end(),
                          item_seq.begin(),
                          item_seq.end());
    }
}



void ObjectManager::log(std::thread::id t, const char*  f, const char* m)
{
    std::cout << f << "\t" << t << "\t" << m << std::endl;
}
