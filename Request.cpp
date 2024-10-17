#include "Request.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

Request::Request(){
    ipIN = generateIP();
    ipOUT = generateIP();
    timeLeft = rand() % 100 + 1;
}

// this function was completed using ChatGPT
// generates a random ip address
string Request::generateIP() {
    stringstream ip;
    for (int i = 0; i < 4; ++i) {
        ip << (rand() % 256);
        if (i < 3) ip << ".";
    }
    return ip.str();
}
