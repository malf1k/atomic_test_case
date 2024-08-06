#include <iostream>

#include "colorobject.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    ColorObject c1(Color::RED);

    shared_ptr<ColorObject> c2 ( new ColorObject(Color::BLUE));

    cout << "c2 color - " << static_cast<int> (c2->getColor()) << endl;
    cout << "c1 color - " << static_cast<int> (c1.getColor()) << endl;




    return 0;
}
