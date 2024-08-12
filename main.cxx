#include <iostream>
#include <string>

#include "objectmanager.h"

using namespace std;

int main()
{


    ObjectManager om;
    string start_message = "Allow commands:\n"s +
                           "1: \tstart_creation\n"s +
                           "2: \tstop_creation\n"s +
                           "3: \tstart_processing\n"s +
                           "4: \tstop_processing\n"s +
                           "5: \tstart_all\n"s +
                           "6: \tstop_all\n"s +
                           "7: \tset_new_rule\n"s +
                           "?: \tshow start_message\n"s +
                           "0: \texit\n"s
                           ;
    cout << start_message;
    string input;
    while(true)
    {
        getline(cin, input);

        if(input == "1" || input == "start_creation")
        {
            uint number_sequences;
            cout << "Set number_sequence" << endl;
            cin >> number_sequences;

            om.startCreation(number_sequences);
        }
        else if( input == "2" || input == "stop_creation")
        {
            om.stopCreation();
        }
        else if( input == "3" || input == "start_processing")
        {
            om.startProcessing();
        }
        else if( input == "4" || input == "stop_processing")
        {
            om.stopProcessing();
        }
        else if( input == "5" || input == "start_all")
        {
            uint number_sequences;
            cout << "Set number_sequence" << endl;
            cin >> number_sequences;
            om.startAll(number_sequences);
        }
        else if( input == "6" || input == "stop_all")
        {
            om.stopAll();
        }
        else if( input == "7" || input == "set_new_rule")
        {
            string new_rule;
            cout << "set new rule if format: R<G<B or RGB or rgb" << endl;
            getline(cin, new_rule);
            om.setNewRule(new_rule);
        }
        else if( input == "?")
        {
            cout << start_message;
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

