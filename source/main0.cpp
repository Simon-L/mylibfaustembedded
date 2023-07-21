// Copied from llvm-test.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

#include "faust/dsp/llvm-dsp.h"
#include "faust/audio/dummy-audio.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/misc.h"

// To do CPU native compilation
#ifndef JIT_TARGET
#define JIT_TARGET ""
#endif

static void printList(const std::vector<std::string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        std::cout << "item: " << list[i] << "\n";
    }
}

void foo(int argc, const char* argv[])
{ 
  std::string error_msg;
  llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", "import(\"stdfaust.lib\");process = os.osc(440);", argc, argv, JIT_TARGET, error_msg, -1);
  if (!factory) {
      std::cerr << "Cannot create factory : " << error_msg;
      exit(EXIT_FAILURE);
  }
  
  std::cout << "getCompileOptions " << factory->getCompileOptions() << std::endl;
  printList(factory->getLibraryList());
  printList(factory->getIncludePathnames());
  
  dsp* DSP = factory->createDSPInstance();
  if (!DSP) {
      std::cerr << "Cannot create instance "<< std::endl;
      exit(EXIT_FAILURE);
  }
  
  std::cout << "getName " << factory->getName() << std::endl;
  std::cout << "getSHAKey " << factory->getSHAKey() << std::endl;
  
  dummyaudio audio(1);
  if (!audio.init("FaustDSP", DSP)) {
      exit(EXIT_FAILURE);
  }
  
  audio.start();
  audio.stop();
  
  delete DSP;
  deleteDSPFactory(factory);
}

int main(int argc, char* argv[])
{
    std::cout << "Libfaust version : " << getCLibFaustVersion () << std::endl;
    std::cout << "getDSPMachineTarget " << getDSPMachineTarget() << std::endl;
    
    int fargc = argc - 1;
    char* fargv[fargc];
    
    for (size_t i = 0; i < fargc; i++) {
        fargv[i] = argv[i+1]; 
        std::cout << i << " : " << fargv[i] << std::endl;
    }
    auto cfargv = const_cast<const char **>(fargv);
    foo(fargc, cfargv);
    
    return 0;
}

