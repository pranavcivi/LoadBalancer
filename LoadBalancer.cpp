#include "LoadBalancer.h"
#include "Webserver.h"
#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

LoadBalancer::LoadBalancer(int numServers, int numRequests, int maxServers, int maxIdle) : maxServers(maxServers), maxIdle(maxIdle) {
    // allocate initial webservers
    for(int i = 0; i < numServers; i++){
        this->servers.push_back(new WebServer());
    }
    // create initial requests
    for(int i = 0; i < numRequests; i++){
        this->requestQueue.push(Request());
    }

    currIdle = numServers;
    srand(time(0));
}

// this function was completed using ChatGPT
// deallocated memory used by the vector holding WebServer objects
LoadBalancer::~LoadBalancer(){
    for(WebServer *server : this->servers){
        delete server;
    }
}

// this function was completed using ChatGPT
// randomly add new requests to simulate a real world scenario
void LoadBalancer::generateNewRequestsRandom(int time){
    if (rand() % 10 == 0){
        this->requestQueue.push(Request());
        cout << "Request randomly added at: " << time << endl;
    }
}

// take requests from the queue and assign to the next available web server
void LoadBalancer::dispatchRequests(){
    int index = 0;
    for(WebServer *server : this->servers){
        if(!server->busy && !requestQueue.empty()){
            cout << "Assigned request to server #" << (index+1);
            server->assignRequest(requestQueue.front());
            requestQueue.pop();
        }
        index++;
    }
}

// make each webserver work on its request (decrease the request time by 1)
void LoadBalancer::processRequests(int time){
    currIdle = this->servers.size();
    for(WebServer *server : this->servers){
        bool busy = server->processRequest(time);
        if(busy){
            currIdle--;
        }
    }
}

/*
    go through all the webservers in the vector
    1. if there are too many requests, add more webservers DONE
    2. if there are too many idle servers, delete the idle ones DONE
    3. do not add more than maxServers servers DONE
    4. Randomly add new requests to simulate real world scenarios DONE
*/
string LoadBalancer::adjustWebServers(int time){

    // add new requests to existing servers. add to idle servers first. done in dispatchRequest()
    // If still not enough, add more but total cannot be more than maxServers
    if(this->requestQueue.size() > this->servers.size()){
        int serversNeeded = this->requestQueue.size() - this->servers.size();
        int serversPossible = maxServers - this->servers.size();
        int serversToAdd = min(serversNeeded, serversPossible);

        for(int i = 0; i < serversToAdd; i++){
            cout << "Allocating new webserver to handle load" << endl;
            this->servers.push_back(new WebServer());
        }
    }

    // delete idle servers
    for(auto it = this->servers.begin(); it != this->servers.end();){
        WebServer* webserver = *it;
        // cout << "cycles idle: " << webserver->cyclesIdle << " maxIdle: " << this->maxIdle << endl;
        if(webserver->cyclesIdle >= this->maxIdle){
            cout << "Deallocating server for being idle too long" << endl;
            delete webserver;
            it = this->servers.erase(it);
        } else {
            it++;
        }
        // cout << "size of servers: " << this->servers.size() << endl;
    }
    

    return "";
}



