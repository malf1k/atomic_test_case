#include <iostream>
#include <string>

#include "objectmanager.h"

using namespace std;

uint32_t setNumber(const string& message)
{
    uint32_t number;
    cout << message << endl;
    cin >> number;
    return number;
}

void sendStartMessage()
{
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
}

int main()
{
    ObjectManager om;
    sendStartMessage();
    string input;
    while(true)
    {
        getline(cin, input);

        if(input == "1" || input == "start_creation")
        {
            uint32_t number_sequences = setNumber("Set number of sequence");
            uint32_t elements_in_sequence = setNumber("Set elements in sequence");
            om.startCreation(number_sequences, elements_in_sequence);
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
            uint32_t number_sequences = setNumber("Set number of sequence");
            uint32_t elements_in_sequence = setNumber("Set elements in sequence");
            om.startAll(number_sequences, elements_in_sequence);
        }
        else if( input == "6" || input == "stop_all")
        {
            om.stopAll();
        }
        else if( input == "7" || input == "set_new_rule")
        {
            string new_rule;
            cout << "Set new rule if format: R<G<B or RGB or rgb" << endl;
            getline(cin, new_rule);
            om.setNewRule(new_rule);
        }
        else if( input == "?")
        {
            sendStartMessage();
        }
        else if( input == "0" || input == "exit")
        {
            om.stopAll();
            break;
        }
        else
        {
            if(input != "")
            {
                cout << "This command not definition - " << input << endl;
                sendStartMessage();
            }
        }
    }

    return 0;
}

