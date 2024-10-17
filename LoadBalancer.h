/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class, which manages web servers and distributes requests to them.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Webserver.h"
#include "Request.h"
#include <string>
#include <queue>

using namespace std;

/**
 * @class LoadBalancer
 * @brief Manages a pool of web servers and dispatches web requests to them.
 *
 * The LoadBalancer class handles the distribution of requests across multiple web servers.
 * It manages a request queue, web servers, and ensures that servers are scaled up or down
 * based on the load.
 */
class LoadBalancer {
    public:
        queue<Request> requestQueue;    ///< Queue holding incoming requests.
        vector<WebServer*> servers;     ///< A vector of pointers to WebServer objects.
        int maxServers;                 ///< The maximum number of servers allowed.
        int maxIdle;                    ///< The maximum number of idle cycles before scaling down.
        int currIdle;                   ///< The current number of idle servers.

        /**
         * @brief Default constructor for LoadBalancer.
         */
        LoadBalancer();

        /**
         * @brief Constructor for LoadBalancer with parameters to initialize server settings.
         *
         * @param numServers The initial number of servers.
         * @param numRequests The number of initial requests.
         * @param maxServers The maximum number of servers allowed.
         * @param maxIdle The maximum number of idle cycles.
         */
        LoadBalancer(int numServers, int numRequests, int maxServers, int maxIdle);

        /**
         * @brief Destructor for LoadBalancer. Cleans up dynamically allocated web servers.
         */
        ~LoadBalancer();

        /**
         * @brief Fills the request queue with a given number of initial requests.
         *
         * @param numRequests The number of requests to add to the queue.
         */
        void fillInitialQueue(int numRequests);

        /**
         * @brief Generates new requests at random intervals.
         *
         * @param time The current time step, used to control request generation.
         */
        void generateNewRequestsRandom(int time);

        /**
         * @brief Dispatches requests from the queue to available web servers.
         */
        void dispatchRequests();

        /**
         * @brief Processes requests across all web servers.
         *
         * @param time The current time step for processing requests.
         */
        void processRequests(int time);

        /**
         * @brief Adjusts the number of web servers based on the current load.
         *
         * Scales up or down based on the number of requests and idle servers.
         * @param time The current time step for scaling servers.
         * @return A string indicating the action taken (e.g., scaling up or down).
         */
        string adjustWebServers(int time);
};

#endif
