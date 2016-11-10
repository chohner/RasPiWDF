#include "midiman.h"

bool MidiMan::done;

MidiMan::MidiMan()
{


    // rtmidid intit
    midiin = new RtMidiIn(RtMidiIn::Api::UNSPECIFIED ,std::string("RtMidi Input Client"),(unsigned int) 100);

    //
    unsigned int nPorts = midiin->getPortCount();

    midiin->openPort( 0 );
    //    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );
    done = false;


    /// Initialize the note-message structure needed for
    /// temporary storage.
    noteMessage bb;
    bb.noteNumber           = -1;
    bb.velocity             = -1;
    bb.hasBeenProcessed     = false;
    tmpNote                 = &bb;




}



void MidiMan::setVerbose()
{
    isVerbose =true;

}

int MidiMan::get_rtmidi(int byteIDX)
{

    std::vector<unsigned char>  a;

    int nBytes = 1;

    int aa = 0;

    // this is kind of a dirty workaroud -
    // we loop over all in-massages and take the last one:
    while(nBytes>0)
    {

        midiin->getMessage(&a);

        nBytes = a.size();

        /// only do something if bytes are received
        if(nBytes!=0)
        {

            /// only give feedback if 'verbose-mode' is active
            if(isVerbose == true  )
            {
                std::cout << "received " << nBytes << "Bytes: " ;

                for (int i=0; i<nBytes; i++ )
                    std::cout <<  i << " = " << (int)a[i] << " -- " ;

                std::cout <<  std::endl;

            }


            aa = (int)a[byteIDX];

            val.push_back(aa);

        }




    }



    return aa;

}


//void MidiMan::finish(int ignore)
//{ done = true;
//}

//MidiMan::~MidiMan()
//{
//    //delete midiin;
//}

//std::vector<std::string> MidiMan::returnAllNames(){

//    return midiInputNames;
//}




//void MidiMan::updateMidiMessages(void* port_buf)
//{
//    /// This method just pushes the incoming midi messages into the
//    /// buffer for later processing!

//    jack_midi_event_t in_event;
//    jack_nframes_t event_count = jack_midi_get_event_count(port_buf);

//    if(event_count>0)
//    {

//        // std::cout << std::endl << "Got " <<   event_count << " messages!" << ": " << std::endl;

//        for(int i=0; i<event_count; i++)
//        {
//            jack_midi_event_get(&in_event, port_buf, i);
//            eventBuffer.push_back(in_event);
//        }

//        // std::cout << std::endl;
//    }

//}



//void MidiMan::parseMidiMessages()
//{
//    /// This method reads translates the raw MIDI messages stored in the buffer
//    /// into note messages used for the 'voicemanager'.

//    int b[3] ={0,0,0};

//    int aa = 0;
//    for(std::vector<jack_midi_event_t>::iterator  it = eventBuffer.begin(); it != eventBuffer.end();)
//    {

//        jack_midi_event_t tmp = eventBuffer.at(aa);

//        b[0] =  tmp.buffer[0];
//        b[1] =  tmp.buffer[1];
//        b[2] =  tmp.buffer[2];


//        // a debug output which shows the complete MIDI message"
//        std::cout << b[0] << " - "<< b[1] << " - " << b[2] << ";" << std::endl;

//        // got an onset = ?
//        if((b[0]==144 & b[2] != 0) )
//        {
//            addNoteOnMessage(b);
//            it = eventBuffer.erase(it);
//            std::cout <<  "ONSET \n";
//        }

//        // got an offset = ?
//        else  if (b[0]==144 & b[2] == 0)
//        {
//            this->addNoteOffMessage(b);
//            it = eventBuffer.erase(it);
//            std::cout <<  "OFFSET \n";
//        }

//        // got fader values?
//        else  if (b[0]==224 || b[0]==225)
//        {
//            ctlMessage m;
//            m.ctlNumber           = b[0];
//            m.value             = b[2];

//            this->faderMessages.push_back(m);
//            it = eventBuffer.erase(it);
//            std::cout <<  "FADER \n";
//        }
//        else
//        {
//            ++it;
//            ++aa;
//        }
//    }


//}

/////////////////////////////////////////////////////////////////////
/// Note messages getters and clearers
/////////////////////////////////////////////////////////////////////


//std::vector<noteMessage> MidiMan::getNoteOnMessages()
//{
//    return noteOnMessages;
//}

//void MidiMan::clearNoteOnMessages()
//{
//    noteOnMessages.clear();
//}

//std::vector<noteMessage> MidiMan::getNoteOffMessages()
//{
//    return noteOffMessages;
//}

//void MidiMan::clearNoteOffMessages()
//{
//    noteOffMessages.clear();
//}

//void MidiMan::eraseNoteOnMessage(int position)
//{
//    noteOffMessages.erase(noteOffMessages.begin() -1 +position);
//}

//void MidiMan::markOnMessageProcessed(int pos)
//{
//    noteMessage m =  noteOnMessages.at(pos) ;
//    m.hasBeenProcessed = true;
//    noteOnMessages.at(pos) = m;
//}

//void MidiMan::markOffMessageProcessed(int pos)
//{
//    noteMessage m =  noteOffMessages.at(pos) ;
//    m.hasBeenProcessed = true;
//    noteOffMessages.at(pos) = m;
//}

//////////////////////////////////////////////////////////////////
// FLUSH
//////////////////////////////////////////////////////////////////

void MidiMan::flushProcessedMessages()
{

    val.clear();


    //    int k=0;
    //    for(std::vector<noteMessage>::iterator  it2 = noteOffMessages.begin(); it2 != noteOffMessages.end();)
    //    {
    //        noteMessage t = noteOffMessages.at(k);
    //        if(t.hasBeenProcessed==true)
    //        {
    //            it2 = noteOffMessages.erase(it2);
    //        }
    //        else
    //        {
    //            ++it2;
    //            k++;
    //        }
    //    }

    //    k=0;
    //    for(std::vector<noteMessage>::iterator it2 = noteOnMessages.begin(); it2 != noteOnMessages.end();)
    //    {
    //        noteMessage t = noteOnMessages.at(k);
    //        if(t.hasBeenProcessed==true)
    //        {
    //            it2 = noteOnMessages.erase(it2);
    //        }
    //        else
    //        {
    //            ++it2;
    //        }
    //    }

}


/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

// THESE ARE USED WITH JACK MIDI:

// this function receives a pointer to 3 ints
// - and pushes them in as a note on event to be treated
//void MidiMan::addNoteOnMessage(int *in)
//{
//    // a debug output which shows the complete MIDI message"
//    // std::cout << in[0] << " - "<< in[1] << " - " << in[2] << ";" << std::endl;

//    tmpNote->hasBeenProcessed = false;
//    tmpNote->noteNumber = in[1];
//    tmpNote->velocity = in[2];
//    noteOnMessages.push_back(*tmpNote);

//}


//// this function receives a pointer to 3 ints
//// - and pushes them in as a note off event to be treated
//void MidiMan::addNoteOffMessage(int in[3])
//{
//    // a debug output which shows the complete MIDI message"
//    // std::cout << in[0] << " - "<< in[1] << " - " << in[2] << ";" << std::endl;

//    tmpNote->hasBeenProcessed = false;
//    tmpNote->noteNumber = in[1];
//    tmpNote->velocity = in[2];
//    noteOffMessages.push_back(*tmpNote);
//}





//void MidiMan::addFaderMessage(ctlMessage m)
//{
//    faderMessages.push_back(m);
//}


//ctlMessage MidiMan::getLastFaderMessage()
//{

//    ctlMessage m  = faderMessages.back();

//    faderMessages.clear();

//    return m;
//}



int MidiMan::getNumFaderMessages()
{

    int v  = (int) val.size();

    return v;
}





//void MidiMan::mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
//{
//    unsigned int nBytes = message->size();
//    for ( unsigned int i=0; i<nBytes; i++ )
//        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
//    if ( nBytes > 0 )
//        std::cout << "stamp = " << deltatime << std::endl;
//}


