#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <jackaudioio.hpp>

#include "PI/singlesample.h"

#include "rt-wdf_lib/Libs/rt-wdf/rt-wdf.h"

// Circuits
//#include "Circuits/wdfCCTAx1Tree.hpp"
//#include "Circuits/wdfCCTAx4Tree.hpp"
//#include "Circuits/wdfJTM45Tree.hpp"
//#include "Circuits/wdfSwitchTree.hpp"
#include "Circuits/wdfTonestackTree.hpp"

using std::cout;
using std::endl;

class SampleLooper: public JackCpp::AudioIO {

private:
    SingleSample    *sample;
    wdfTree *myWdfTree;

public:
    /// Audio Callback Function, output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){

        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {
            sample->get_frame(nframes, outBufs[0]);
            for (unsigned int sample = 0; sample < nframes; sample++)
            {
                //float inVoltage = outBufs[0][sample];
                myWdfTree->setInputValue(outBufs[0][sample]);
                myWdfTree->cycleWave();
                outBufs[0][sample] = { (float)(myWdfTree->getOutputValue()) };
            }
        }
        return 0;
    }

    /// Constructor
    SampleLooper(std::string fileName, float playbackRate) :
        JackCpp::AudioIO("sample_looper", 0,1){

        reserveInPorts(2);
        reserveOutPorts(2);

        /// allocate the sample player
        sample = new SingleSample(fileName);
        sample->set_rate(playbackRate);

        myWdfTree = new wdfTonestackTree();
        myWdfTree->initTree();
        myWdfTree->adaptTree();
    }
};


/// MAIN
int main(int argc, char *argv[]){
    // WDF stuff
    //wdfTree *myWdfTree;

    float playbackRate = 2.0;

    if(argc<=1){
        cout << "Pass path to wav-file as argument!" << endl;
        return 0;
    }

    /// Create looper with filename from first commandline arg
    SampleLooper * t = new SampleLooper( std::string(argv[1]), playbackRate );

    /// Start the jack client (also starts loop)
    t->start();

    /// connect mono loop port to stereo output ports
    t->connectToPhysical(0,0);
    t->connectToPhysical(0,1);

    ///print names
    cout << "Output port(s):" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;

    /// Run until ENTER key
    printf("### Press ENTER to quit ###\n");
    getchar();

    /// Break down
    t->disconnectOutPort(0); // Discconect out port.
    t->close();	// Stop client.
    delete t;	// Always clean up after yourself.
    exit(0);
}
