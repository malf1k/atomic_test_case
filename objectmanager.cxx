#include "objectmanager.h"

ObjectManager::ObjectManager() {

    m_queue = new Collection;
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
