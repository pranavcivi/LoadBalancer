/**
 * @file Request.h
 * @brief Defines the Request class, which represents a web request.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @class Request
 * @brief Represents a web request with source and destination IP addresses, processing time, and job type.
 *
 * The Request class holds information about the request, including the IP addresses involved, 
 * the time left to process the request, and the job type.
 */
class Request {
    public:
        string ipIN;      ///< The source IP address of the request.
        string ipOUT;     ///< The destination IP address of the request.
        int timeLeft;     ///< The time remaining to process the request.
        char jobType;     ///< The type of job requested (e.g., different types of web requests).

        /**
         * @brief Default constructor for Request. Initializes random IPs and job type.
         */
        Request();

        /**
         * @brief Generates a random IP address.
         * @return A string representing the generated IP address.
         */
        string generateIP();
};

#endif
