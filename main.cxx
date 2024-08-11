// #include <iostream>
// #include <time.h>
#include <thread>

#include "objectmanager.h"

void generate (ObjectManager& om, const int& queue_size, const int& seq_size);

using namespace std;

int main()
{


    ObjectManager om;

    om.start();
    // om.createRandomSeq();

    // auto ss = om.sortSeqByRule(om.getSeqFromQueue());


    // om.printSeq(s);
    // om.printSeq(ss);

    return 0;
}



void generate(ObjectManager& om, const int& queue_size, const int& seq_size)
{
    for(int i = 0; i < queue_size; i++)
    {
        om.createRandomSeq(seq_size);
    }

}
