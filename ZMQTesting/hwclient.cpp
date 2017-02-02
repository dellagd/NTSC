#include <zmq.hpp>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <iostream>

#define MSG_SIZE    10000000

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://ghc29.ghc.andrew.cmu.edu:5555");

    srand(time(NULL));
    unsigned char* dat = new unsigned char[MSG_SIZE];
    for (int i = 0; i < MSG_SIZE; i++){
        dat[i] = (unsigned char) ((rand() / (float) RAND_MAX) * 256.0);
    }

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 100; request_nbr++) {
        std::cout << "Before Request" << std::endl;
        zmq::message_t request (MSG_SIZE);
        std::cout << "After Request" << std::endl;

        memcpy (request.data (), dat, MSG_SIZE);
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        std::cout << "Received World " << request_nbr << std::endl;
    }

    delete [] dat;
    return 0;
}
