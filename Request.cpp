#include "Request.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Constructs a Request object with randomly generated IP addresses and a random processing time.
 *
 * The constructor initializes the source and destination IP addresses using the generateIP() method
 * and assigns a random processing time between 1 and 100.
 */
Request::Request() {
    ipIN = generateIP();
    ipOUT = generateIP();
    timeLeft = rand() % 100 + 1;
}

/**
 * @brief Generates a random IP address in the format "xxx.xxx.xxx.xxx".
 *
 * Each octet of the IP address is a random number between 0 and 255.
 *
 * @return A string representing the generated IP address.
 */
string Request::generateIP() {
    stringstream ip;
    for (int i = 0; i < 4; ++i) {
        ip << (rand() % 256);
        if (i < 3) ip << ".";
    }
    return ip.str();
}
