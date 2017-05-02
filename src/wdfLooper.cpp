#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <thread>

#include "jackaudioio.hpp"

#include "PI/singlesample.h"
#include "rt-wdf_lib/Libs/rt-wdf/rt-wdf.h"
#include "potis/potis.h"

// Circuits
//#include "Circuits/wdfCCTAx1Tree.hpp"
//#include "Circuits/wdfCCTAx4Tree.hpp"
//#include "Circuits/wdfJTM45Tree.hpp"
//#include "Circuits/wdfSwitchTree.hpp"
#include "Circuits/wdfTonestackTree.hpp"

using std::cout;
using std::endl;


class SampleLooper : public JackCpp::AudioIO {

private:
SingleSample  *sample;
wdfTree *myWdfTree;

public:

// Apply WDF Filter
static void wdf_callback(wdfTree *myWdfTree, jack_nframes_t nframes, audioBufVector outBufsWdf){
        for (unsigned int i_sample = 0; i_sample < nframes; i_sample++)
        {
                myWdfTree->setInputValue(outBufsWdf[0][i_sample]);
                myWdfTree->cycleWave();
                outBufsWdf[0][i_sample] = { (float)(myWdfTree->getOutputValue()) };
        }
}

// Adapt Filter Parameters by Poti
static void wdf_adaptParam(wdfTree *myWdfTree){
        extern Potis potis;
        float P0_s = 0;

        for (;;) {
                if (P0_s != potis.getPoti(0)) {
                        P0_s = potis.getPoti(0);
                        myWdfTree->setParam(2, P0_s + 0.0001);
                }
        }
}

/// Audio Callback Function, output buffers are filled here
virtual int audioCallback(jack_nframes_t nframes,
                          // A vector of pointers to each input port.
                          audioBufVector inBufs,
                          // A vector of pointers to each output port.
                          audioBufVector outBufs){

        std::thread wdfThread(SampleLooper::wdf_callback, myWdfTree, nframes, outBufs);

        // LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {
                sample->get_frame(nframes, outBufs[0]);
                wdfThread.join();  // join with audioCallback

        }
        return 0;
}

// Constructor
SampleLooper(std::string fileName, float playbackRate) :
        JackCpp::AudioIO("sample_looper", 0,1){

        reserveInPorts(2);
        reserveOutPorts(2);

        // allocate the sample player
        sample = new SingleSample(fileName);
        sample->set_rate(playbackRate);

        myWdfTree = new wdfTonestackTree();
        myWdfTree->initTree();
        myWdfTree->setSamplerate(44100);
        myWdfTree->adaptTree();

        // start adapt filter thread
        std::thread wdf_adaptParam_thread(SampleLooper::wdf_adaptParam, myWdfTree);
        wdf_adaptParam_thread.detach();

}
};  // Class SampleLooper


/// MAIN
int main(int argc, char *argv[]){

        if(argc<=1) {
                cout << "Pass path to wav-file as argument!" << endl;
                return 0;
        }

        // Create looper with filename from first commandline arg
        SampleLooper * t = new SampleLooper( std::string(argv[1]), 2.0 );

        // Start the jack client (also starts loop)
        t->start();

        // Start ADS and Potis
        setup_ads();
        std::thread readingThread(read_cont_values);
        readingThread.detach();
        
        // connect mono loop port to stereo output ports
        t->connectToPhysical(0,0);
        t->connectToPhysical(0,1);

        // Print Output ports
        cout << "Output port(s):" << endl;
        for(unsigned int i = 0; i < t->outPorts(); i++)
                cout << "\t" << t->getOutputPortName(i) << endl;

        // Run until ENTER key
        printf("### Press ENTER to quit ###\n");
        getchar();

        // Break down
        t->disconnectOutPort(0); // Discconect out port.
        t->close(); // Stop client.
        delete t; // Always clean up after yourself.
        powerdown_ads();
        exit(0);
}
