#include "objectmanager.h"
#include <iostream>
#include <random>

ObjectManager::ObjectManager() {

    m_queue = new Collection;
}

void ObjectManager::createRandomSeq(const int &number)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 3);

    Sequence seq ;

    for(auto i = 0; i < number; i++)
        seq.push_back(static_cast<Color>(dist(gen)));
    addSeqToQeue(seq);
}

void ObjectManager::addSeqToQeue(const Sequence &seq)
{
    if (m_queue != nullptr)
        m_queue = new Collection;
    m_queue->push(seq);
}

Sequence ObjectManager::getSeqFromQueue()
{
    return m_queue->front();
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

Sequence ObjectManager::sortSeqByRule(const Sequence &seq, const Rule &rule)
{
    Sequence sorted_seq;

    std::vector<Sequence> sorted_subseq;
    sorted_subseq.reserve(rule.size());

    for (size_t i = 0; i < rule.size(); ++i) {
        sorted_subseq.emplace_back(); // Создаем пустой вектор и добавляем его в контейнер
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
    Color c;
    for(auto i: seq)
    {
        switch (i.getColor()) {
        case Color::RED:
             std::cout <<" "<< "RED";
            break;
        case Color::GREEN:
            std::cout <<" "<< "GREEN";
            break;
        case Color::BLUE:
            std::cout <<" "<< "BLUE";
            break;
        default:
            std::cout <<" "<< "NONE";
            break;
        }
    }
    std::cout << std::endl;
}
