#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

char* IP = "127.0.0.1";
int PORT = 12345;
char* MY_IP = "127.0.0.1";
int MY_PORT = 12344;

int main() {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Client address
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(MY_PORT);  // Replace with the client port
    clientAddr.sin_addr.s_addr = inet_addr(MY_IP);  // Replace with the client IP address


    if (bind(sockfd, (struct sockaddr *) &clientAddr, sizeof(clientAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    // Server address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);  // Replace with the server port
    serverAddr.sin_addr.s_addr = inet_addr(IP);  // Replace with the server IP address

    // Data to send
    const char* data = "Hello, server!";

    // Send data to the server
    ssize_t numBytesSent = sendto(sockfd, data, strlen(data), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (numBytesSent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return 1;
    }

    std::cout << "Data sent to the server" << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}
