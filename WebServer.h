/**
 * @file WebServer.h
 * @brief Defines the WebServer class, which simulates a web server processing requests.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include "Request.h"

using namespace std;

/**
 * @class WebServer
 * @brief Simulates a web server that processes requests.
 *
 * The WebServer class is responsible for managing the processing of web requests. 
 * It tracks whether it is busy, the time remaining for the current request, 
 * and how long it has been idle.
 */
class WebServer {
    public:
        Request currentRequest;  ///< The current request being processed by the server.
        int timeRemaining;       ///< The remaining time to process the current request.
        bool busy;               ///< Flag indicating whether the server is busy.
        int cyclesIdle;          ///< Tracks the number of idle cycles when the server is not processing a request.

        /**
         * @brief Default constructor for WebServer. Initializes server state as idle.
         */
        WebServer();

        /**
         * @brief Assigns a request to the web server and marks it as busy.
         * 
         * @param req The request to be assigned to the server.
         */
        void assignRequest(Request& req);

        /**
         * @brief Processes the current request by decrementing its time.
         *
         * If the request is completed, the server is marked as idle.
         * @param time The time step for processing.
         * @return True if the server is still busy, false if idle.
         */
        bool processRequest(int time);

        /**
         * @brief Completes the current request, marks the server as idle, and resets its idle cycle.
         */
        void completeRequest();
};

#endif
