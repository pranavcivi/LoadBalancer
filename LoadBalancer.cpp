#include "LoadBalancer.h"
#include "Webserver.h"
#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Constructs a LoadBalancer with a specified number of web servers and requests.
 *
 * The constructor initializes the load balancer with the given number of web servers, 
 * fills the request queue with the specified number of requests, and sets the maximum 
 * allowable number of servers and idle cycles before a server is deallocated.
 *
 * @param numServers The initial number of servers.
 * @param numRequests The number of requests to populate the request queue with.
 * @param maxServers The maximum number of web servers allowed.
 * @param maxIdle The maximum number of idle cycles allowed before a server is deallocated.
 */
LoadBalancer::LoadBalancer(int numServers, int numRequests, int maxServers, int maxIdle) 
    : maxServers(maxServers), maxIdle(maxIdle) {
    // allocate initial webservers
    for (int i = 0; i < numServers; i++) {
        this->servers.push_back(new WebServer());
    }
    // create initial requests
    for (int i = 0; i < numRequests; i++) {
        this->requestQueue.push(Request());
    }

    currIdle = numServers;
    srand(time(0));
}

/**
 * @brief Destructor for LoadBalancer.
 *
 * Deallocates memory used by the vector holding dynamically allocated WebServer objects.
 */
LoadBalancer::~LoadBalancer() {
    for (WebServer *server : this->servers) {
        delete server;
    }
}

/**
 * @brief Randomly adds new requests to the queue to simulate real-world scenarios.
 *
 * At random intervals (10% chance), a new request is added to the queue.
 * 
 * @param time The current simulation time.
 */
void LoadBalancer::generateNewRequestsRandom(int time) {
    if (rand() % 100 <= 10) {
        this->requestQueue.push(Request());
        cout << "Request randomly added at: " << time << endl;
    }
}

/**
 * @brief Dispatches requests from the queue to available web servers.
 *
 * This method assigns requests to the next available web server, starting from the 
 * first server and working through the list of servers.
 */
void LoadBalancer::dispatchRequests() {
    int index = 0;
    for (WebServer *server : this->servers) {
        if (!server->busy && !requestQueue.empty()) {
            cout << "Assigned request to server #" << (index + 1);
            server->assignRequest(requestQueue.front());
            requestQueue.pop();
        }
        index++;
    }
}

/**
 * @brief Processes all requests across the web servers.
 *
 * This method makes each web server work on its assigned request by reducing the remaining
 * processing time by one. It also tracks the number of idle servers.
 *
 * @param time The current simulation time.
 */
void LoadBalancer::processRequests(int time) {
    currIdle = this->servers.size();
    for (WebServer *server : this->servers) {
        bool busy = server->processRequest(time);
        if (busy) {
            currIdle--;
        }
    }
}

/**
 * @brief Adjusts the number of web servers based on the load.
 *
 * This method performs the following tasks:
 * 1. Adds new servers if there are more requests than available servers, but does not exceed maxServers.
 * 2. Deallocates idle servers if they have been idle for too many cycles (based on maxIdle).
 * 3. Simulates real-world scenarios by randomly adding new requests.
 *
 * @param time The current simulation time.
 * @return A string indicating actions taken by the load balancer.
 */
string LoadBalancer::adjustWebServers(int time) {
    // Add new requests to existing servers. Add to idle servers first. Done in dispatchRequest()
    // If still not enough, add more but total cannot be more than maxServers
    if (this->requestQueue.size() > this->servers.size()) {
        int serversNeeded = this->requestQueue.size() - this->servers.size();
        int serversPossible = maxServers - this->servers.size();
        int serversToAdd = min(serversNeeded, serversPossible);

        for (int i = 0; i < serversToAdd; i++) {
            cout << "Allocating new webserver to handle load" << endl;
            this->servers.push_back(new WebServer());
        }
    }

    // Delete idle servers
    for (auto it = this->servers.begin(); it != this->servers.end();) {
        WebServer* webserver = *it;
        if (webserver->cyclesIdle >= this->maxIdle) {
            cout << "Deallocating server for being idle too long" << endl;
            delete webserver;
            it = this->servers.erase(it);
        } else {
            it++;
        }
    }

    return "";
}
