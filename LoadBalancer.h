#include "Webserver.h"
#include "Request.h"
#include <string>
#include <queue>
#ifndef LOADBALANCER_H
#define LOADBALANCER_H
using namespace std;

class LoadBalancer{
    public:
        queue<Request> requestQueue;
        vector<WebServer*> servers;
        int maxServers;
        int maxIdle;
        int currIdle;

        LoadBalancer();
        LoadBalancer(int numServers, int numRequests, int maxServers, int maxIdle);
        ~LoadBalancer();

        void fillInitialQueue(int numRequests);
        void generateNewRequestsRandom(int time);
        void dispatchRequests();
        void processRequests(int time);
        string adjustWebServers(int time);
};

#endif