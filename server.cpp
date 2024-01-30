#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

char* MY_IP = "127.0.0.1";
int MY_PORT = 12000;

int main() {
    // Create a UDP socket
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Bind the socket to a specific address and port
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(MY_PORT); // Change this to the desired port number
    serverAddress.sin_addr.s_addr = inet_addr(MY_IP);  // Replace with the server IP address

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    // Listen for incoming messages
    char buffer[1024];
    struct sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        // Receive message from client
        ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                                     (struct sockaddr *) &clientAddress, &clientAddressLength);
        if (bytesRead < 0) {
            std::cerr << "Failed to receive message" << std::endl;
            return 1;
        }

        // Print the received message
        std::cout << "Received message from " << inet_ntoa(clientAddress.sin_addr) << "." << ntohs(clientAddress.sin_port) << ": " << buffer << std::endl;
    }

    // Close the socket
    close(serverSocket);

    return 0;
}
