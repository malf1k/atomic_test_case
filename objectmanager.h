#pragma once

#include <queue>
#include <vector>

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

    void createRandomSeq(const int& number = 100);
    void addSeqToQeue(const Sequence & seq);


    Sequence getSeqFromQueue();
    Sequence sortSeqByRule(const Sequence& seq,
                           const Rule &rule =
                           {Color::RED, Color::GREEN, Color::BLUE}
                           );

    void printSeq(const Sequence& seq);



private:

    Collection *m_queue = nullptr;
    // Sequence *m_seq = nullptr;

    void subseqJoining(Sequence &sorted_seq, const std::vector<Sequence>& sorted_subseq);


};
