#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

int main()
{
    std::string url;
    addrinfo hints;
    addrinfo *servInfo;
    addrinfo *originalServInfo;

    std::memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    std::cout << "Please enter a domain name: " << std::endl;

    std::cin >> url;

    int status = getaddrinfo(url.c_str(), NULL, &hints, &servInfo);

    if (status != 0)
    {
        std::cerr << "Error: " << gai_strerror(status) << std::endl;

        return 1;
    }

    char ipv4str[INET_ADDRSTRLEN];

    originalServInfo = servInfo;

    while (servInfo != nullptr)
    {
        sockaddr_in *ipv4 = (sockaddr_in *)servInfo->ai_addr;

        inet_ntop(AF_INET, &(ipv4->sin_addr), ipv4str, sizeof(ipv4str));

        std::cout << "The IPv4 Address is: " << ipv4str << std::endl;

        servInfo = servInfo->ai_next;
    }

    freeaddrinfo(originalServInfo);

    return 0;
}