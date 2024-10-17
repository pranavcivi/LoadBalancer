#include "Webserver.h"
#include <string>
#include <iostream>
using namespace std;

WebServer::WebServer() : busy(false), cyclesIdle(0){}

void WebServer::assignRequest(Request& req){
    currentRequest = req;
    busy = true;
    cyclesIdle = 0;
    cout << " with ipIN: " << req.ipIN << ", ipOUT: " << req.ipOUT << ", time: " << req.timeLeft << endl;
}

// continue processing a request (decrease time by 1).
// if it's done, print that it is done
// if it is not done, print that it is still working
// a webserver can only process its current request if it is busy
bool WebServer::processRequest(int time){
    if(busy){
        currentRequest.timeLeft--;

        if(currentRequest.timeLeft <= 0){
            cout << "Finished request from ipIN: " << currentRequest.ipIN << endl;
            busy = false;
            this->cyclesIdle = 0;
        }
        else{
            cout << "Server processing a request with time left: " << currentRequest.timeLeft << endl;
            this->cyclesIdle = 0;
        }
    }
    else{
        cout << "Server Idle for " << this->cyclesIdle << endl;
        this->cyclesIdle++;
    }

    return busy;
}