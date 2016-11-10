/**
 * \class OscMan
 *
 *
 * \brief Class which parses the incoming OSC messages.
 *
 * This class parses the incoming OSC messages by
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/18$
 *
 * Contact: von_coler@tu-berlin.de
 *
 *
 */

#ifndef OSCMAN_H
#define OSCMAN_H

 
// works with 'self built'
#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include<iostream>
#include<vector>
#include<string>

struct dMess{
 std::string type;
 std::string path;
 double val;
} ;

struct iMess{
 std::string type;
 std::string path;
 int val;
} ;

class OscMan
{

private:



    /// the port to be opened
    int port;

    lo::ServerThread *st;

    // for each OSC message we store its path, value and type
    /// messages are only integers, at this point:
    std::vector<double> messages;
    std::vector<std::string> paths;
    std::vector<std::string> types;

    std::vector<dMess> dMessages;
    std::vector<iMess> iMessages;

    static int double_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);


public:

    OscMan(int p);

    void printAllMessages();

    double getLastMessage();

    dMess getLast_dMess();

    std::string getLastPath();

    std::string getLastType();

    int getNumberOfMessages();

    int getNumberOfdMess();


};

#endif
