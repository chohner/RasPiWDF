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



class SampleLooper: public JackCpp::AudioIO {

private:

    SingleSample    *sample;

public:
    /// Audio Callback Function:
    /// - the output buffers are filled here
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

        ///return 0 on success
        return 0;
    }

    /// Constructor
    SampleLooper(std::string s) :
        JackCpp::AudioIO("sample_looper", 0,1){


        reserveInPorts(2);
        reserveOutPorts(2);


        /// allocate the sample player
        sample = new SingleSample(s);

        sample->set_rate(1.0);

    }

};

///
///
///
int main(int argc, char *argv[]){

    if(argc<=1)
    {
        cout << "Pass path to wav-file as argument!" << endl;
        return 0;
    }

    std::string s(argv[1]);

    /// initial ports from constructor created here.
    SampleLooper * t = new SampleLooper(s);

    /// activate the client
    t->start();

    /// connect sine ports to stereo ports
    t->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
    t->connectToPhysical(0,1);		// connects this client out port 1 to physical destination port 1

    ///print names
    cout << "Output port(s):" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;

    /// Run until ENTER key
    printf("### Press ENTER to quit ###\n");
    getchar();

    /// Break down
    t->disconnectOutPort(0); // Discconect out port.
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}
