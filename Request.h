#include <string>
#include <cstdlib>
#include <ctime>
#ifndef REQUEST_H
#define REQUEST_H
using namespace std;

class Request{
    public:
        string ipIN;
        string ipOUT;
        int timeLeft;
        char jobType;
    
    Request();
    string generateIP();
};

#endif