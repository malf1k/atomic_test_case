#include <iostream>

#include "objectmanager.h"

using namespace std;

int main()
{


    ObjectManager om;

    string input;
    while(true)
    {
        cout << "Allow commands:" << endl <<\
            "1: \tstart_creation"   << endl <<\
            "2: \tstop_creation"    << endl <<\
            "3: \tstart_processing" << endl <<\
            "4: \tstop_processing"  << endl <<\
            "5: \tstart_all"        << endl <<\
            "6: \tstop_all"         << endl <<\
            "7: \tset_new_rule"     << endl <<\
            "0: \texit"             << endl <<\
            endl ;
        getline(cin, input);

        if(input == "1" || input == "start_creation")
        {
            // om.startCreation(number_sequences);
        }
        else if( input == "2" || input == "stop_creation")
        {
            // om.stopCreation();
        }
        else if( input == "3" || input == "start_processing")
        {
            // om.startProcessing();
        }
        else if( input == "4" || input == "stop_processing")
        {
            // om.startProcessing();
        }
        else if( input == "5" || input == "start_all")
        {
            om.startAll();
        }
        else if( input == "6" || input == "stop_all")
        {
            // om.stop_all();
        }
        else if( input == "7" || input == "set_new_rule")
        {
            string new_rule;
            cout << "set new rule if format: R<G<B or RGB or rgb" << endl;
            getline(cin, new_rule);
            om.setNewRule(new_rule);
        }
        else if( input == "0" || input == "exit")
        {
            break;
        }


        // if(input == "exit" || input == "7")
        //     break;
        // else if(input == "start_all")
        //     om.start_all();
        // else
        //     cout << endl << "This command \"" << input <<"\" is undef " << endl;
        // cout << endl;
    }

    return 0;
}

