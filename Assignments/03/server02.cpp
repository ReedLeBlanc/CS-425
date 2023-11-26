#include <iostream>
#include <thread>
#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
const uint16_t DefaultPort = 8131;

int main(int argc, char* argv[]) {
    uint16_t port = argc > 1 ? std::stol(argv[1]) : DefaultPort;
    Connection connection(port);

    // Create a thread to handle incoming connections
    std::thread thread([&connection]() {
        while (connection) {
            Session session(connection.accept());
            std::string msg;
            session >> msg;
            HTTPRequest request(msg);
            const char* root = "/home/faculty/shreiner/public_html/03";
            HTTPResponse response(request, root);
            session << response;
        }
    });

    // Wait for the thread to join
    thread.join();

    return 0;
}