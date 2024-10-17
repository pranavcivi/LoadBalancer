#include "LoadBalancer.h"
#include "Webserver.h"
#include "Request.h"
#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(0));
    
    int maxServers = 25; 
    int maxIdle = 20;

    // cout << "Number of servers: ";
    // cin >> numServers;
    // cout << "Time to Run: ";
    // cin >> timeToRun;
    // cout << numServers << " " << timeToRun << endl;
    int numServers = 10;
    double timeToRun = 10000;

    // create loadbalancer with requests = numServers x 100
    LoadBalancer loadBalancer(numServers, numServers*100, maxServers, maxIdle);

    for(int currTime = 0; currTime < timeToRun; currTime++){
        cout << "Clock Cycle: " << currTime+1 << endl;
        string status = loadBalancer.adjustWebServers(currTime); // TODO: add/remove web servers as necessary
        loadBalancer.generateNewRequestsRandom(currTime); // randomly add new requests to the request queue to simulate real world
        loadBalancer.dispatchRequests(); // give requests to the web servers
        loadBalancer.processRequests(currTime); // have each of the webservers process their current requests
         
        cout << "----------------------------------------------------------" << endl;
        if(status == "successful early exit"){
            cout << status << endl;
            return 0;
        }
    }

    
    return 0;
}
