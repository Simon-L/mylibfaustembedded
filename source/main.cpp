#include <iostream>
#include <string>

#include <fstream>
#include <sstream>
#include <thread>
#include <cstdio>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/libfaust.h"
#include "faust/audio/dummy-audio.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/misc.h"

using namespace std;

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        cout << "item: " << list[i] << "\n";
    }
}

// To do CPU native compilation
#ifndef JIT_TARGET
#define JIT_TARGET ""
#endif

void mytest()
{   
    string error_msg;
    llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(440);", 0, NULL, JIT_TARGET, error_msg, -1);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        printList(factory->getLibraryList());
        printList(factory->getIncludePathnames());  
    
        // Static tables initialisation
        factory->classInit(44100);
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
     
        // Use "manager" mode to test 'classInit'
        dummyaudio audio(44100, 512, 1 , 512 , true);
        if (!audio.init("FaustDSP", DSP)) {
            exit(EXIT_FAILURE);
        }
        
        audio.start();
        audio.stop();
        
        delete DSP;
        deleteDSPFactory(factory);
}

auto main() -> int
{
    std::cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    std::cout << "getDSPMachineTarget " << getDSPMachineTarget() << std::endl;
    
    mytest();
    
    return 0;
}
