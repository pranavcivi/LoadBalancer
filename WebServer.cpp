/**
 * @file Webserver.h
 * @brief Definition and implementation of the WebServer class that handles web requests.
 */
#include "Webserver.h"
#include <string>
#include <iostream>
using namespace std;

/**
 * @class WebServer
 * @brief Simulates a web server that processes web requests.
 *
 * The WebServer class is responsible for handling incoming web requests,
 * processing them, and tracking how long it remains idle.
 */
WebServer::WebServer() : busy(false), cyclesIdle(0){}

/**
 * @brief Assigns a new request to the web server.
 *
 * This method assigns a request to the web server, marking the server as busy,
 * and resetting its idle cycle counter.
 *
 * @param req The Request object representing the web request to be processed.
 */
void WebServer::assignRequest(Request& req){
    currentRequest = req;
    busy = true;
    cyclesIdle = 0;
    cout << " with ipIN: " << req.ipIN << ", ipOUT: " << req.ipOUT << ", time: " << req.timeLeft << endl;
}

/**
 * @brief Processes the current request.
 *
 * This method decreases the remaining processing time of the current request by 1.
 * If the request is completed, the server is marked as idle. Otherwise, it continues
 * processing the request. If the server is idle, it tracks how long it has been idle.
 *
 * @param time The amount of time to simulate processing (decrements the request time by 1).
 * @return True if the server is busy (still processing a request), false if idle.
 */
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