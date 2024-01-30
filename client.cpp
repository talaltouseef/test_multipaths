#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

char* IP = "127.0.0.1";
int PORT = 12000;
char* MY_IP1 = "127.0.0.1";
int MY_PORT1 = 12001;
char* MY_IP2 = "127.0.0.1";
int MY_PORT2 = 12002;

int main() {
    // Create a UDP socket
    int sockfd1 = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd1 < 0) {
        std::cerr << "Failed to create socket 1" << std::endl;
        return 1;
    }

    // Create a UDP socket
    int sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd2 < 0) {
        std::cerr << "Failed to create socket 2" << std::endl;
        return 1;
    }

    // Client address
    struct sockaddr_in clientAddr1;
    memset(&clientAddr1, 0, sizeof(clientAddr1));
    clientAddr1.sin_family = AF_INET;
    clientAddr1.sin_port = htons(MY_PORT1);  // Replace with the client port
    clientAddr1.sin_addr.s_addr = inet_addr(MY_IP1);  // Replace with the client IP address

    // Client address
    struct sockaddr_in clientAddr2;
    memset(&clientAddr2, 0, sizeof(clientAddr2));
    clientAddr2.sin_family = AF_INET;
    clientAddr2.sin_port = htons(MY_PORT2);  // Replace with the client port
    clientAddr2.sin_addr.s_addr = inet_addr(MY_IP2);  // Replace with the client IP address


    if (bind(sockfd1, (struct sockaddr *) &clientAddr1, sizeof(clientAddr1)) < 0) {
        std::cerr << "Failed to bind socket 1" << std::endl;
        return 1;
    }

    if (bind(sockfd2, (struct sockaddr *) &clientAddr2, sizeof(clientAddr2)) < 0) {
    std::cerr << "Failed to bind socket 2" << std::endl;
    return 1;
    }

    // Server address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);  // Replace with the server port
    serverAddr.sin_addr.s_addr = inet_addr(IP);  // Replace with the server IP address

    // Data to send
    const char* data1 = "Hello, server! From socket 1";
    const char* data2 = "Hello, server! From socket 2";

    // Send data to the server
    ssize_t numBytesSent1 = sendto(sockfd1, data1, strlen(data1), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (numBytesSent1 < 0) {
        std::cerr << "Failed to send data socket 1" << std::endl;
        return 1;
    }

    ssize_t numBytesSent2 = sendto(sockfd2, data2, strlen(data2), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (numBytesSent2 < 0) {
        std::cerr << "Failed to send data socket 2" << std::endl;
        return 1;
    }

    std::cout << "Data sent to the server" << std::endl;

    // Close the socket
    close(sockfd1);
    close(sockfd2);

    return 0;
}
