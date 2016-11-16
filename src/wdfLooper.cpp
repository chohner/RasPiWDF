/**
* \class SampleLooper
*
* \brief Just loops a WAV file!
*
* \author Henrik von Coler
*
* \version $Revision: 0.5 $
*
* \date $Date: 2016/08/14 14:16:20 $
*
*
* Contact: von_coler@tu-berlin.de
*
*
*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <jackaudioio.hpp>

#include "PI/singlesample.h"

using std::cout;
using std::endl;

/// SAMPLELOOPER
class SampleLooper: public JackCpp::AudioIO {

private:
    SingleSample    *sample;

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
            sample->get_frame(nframes,outBufs[0]);
        }
        return 0; /// Return 0 on success
    }

    /// Constructor
    SampleLooper(std::string fileName, float playbackRate) :
        JackCpp::AudioIO("sample_looper", 0,1){

        reserveInPorts(2);
        reserveOutPorts(2);

        /// allocate the sample player
        sample = new SingleSample(fileName);
        sample->set_rate(playbackRate);
    }
};


/// MAIN
int main(int argc, char *argv[]){
    float playbackRate = 1.0;

    if(argc<=1){
        cout << "Pass path to wav-file as argument!" << endl;
        return 0;
    }
    else if(argc==2) {
        playbackRate = 1.0;
    }
    else {
        playbackRate = atof(argv[2]);
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
