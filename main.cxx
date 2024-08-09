
#include "objectmanager.h"

using namespace std;

int main()
{
    ObjectManager om;
    om.createRandomSeq();

    auto s = om.getSeqFromQueue();

    auto ss = om.sortSeqByRule(s);

    om.printSeq(s);
    om.printSeq(ss);

    return 0;
}
