#include "VoiceMail.h"
#include <iostream>
using namespace std;

int main()
{
    VoiceMail vm;
    vm.record("Call me back ASAP!");
    vm.playback();
    vm.erase();
    vm.playback();
    cout << "End of VoiceMail test" << endl;
}
