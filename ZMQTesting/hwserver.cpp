//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

#define MSG_BYTES   40000000

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    char* r = new char[MSG_BYTES];
    for (int i = 0; i < MSG_BYTES; i++){
        r[i] = ((rand() / (float) RAND_MAX)*256.0f) > 127 ? 1 : 0;
    }

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        uint32_t req = (uint32_t)*(static_cast<uint32_t*>(request.data()));
        //req |= ((uint32_t) data[1]) << 8;
        //req |= ((uint32_t) data[2]) << 16;
        //req |= ((uint32_t) data[3]) << 24;

        //  Do some 'work'
        //sleep(0.05);
        //printf("First Element: %d Size: %d\n", req, request.size());

        //  Send reply back to client
        zmq::message_t reply (r, MSG_BYTES, NULL);
        //reply.data() = r;
        //memcpy (reply.data (), r, 30000);
        socket.send (reply);
    }
    return 0;
}
