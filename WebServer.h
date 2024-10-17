#include <string>
#include "Request.h"
#ifndef WEBSERVER_H
#define WEBSERVER_H
using namespace std;

class WebServer{
    public:
        Request currentRequest;
        int timeRemaining;
        bool busy;
        int cyclesIdle;
    
    WebServer();
    void assignRequest(Request& req);
    bool processRequest(int time);
    void completeRequest();

};

#endif