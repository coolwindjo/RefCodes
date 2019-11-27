// 8_Facade

#include <iostream>
using namespace std;

#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib") // Compile 옵션으로 들어갈 만한 Linking file을 내부에 박아넣을 수 있음

// SRP (Single Responsiblity Principal) : 단일 책임의 원칙
// - Module (Class, Function, Variable)은 단 하나만의 책임을 가져야 한다.

// TCP Server Programming을 하는데 필요한 Class와 절차를 
// 단순화시켜주는 상위 개념의 클래스를 제공하자.
// -> Facade Pattern
// => ACE (TCPServer, Process, Thread...)
// C++ Network Programming I / II (Server 기반의 Programming 에 Bible)
// => Boost::asio / Poco


class IPAddress
{
    SOCKADDR_IN addr;
public:
    IPAddress(const char* ip, short port)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip);
    }
    // string::c_str()의 원리
    SOCKADDR* getRawAddress()   // string -> const char*
    {
        return (SOCKADDR*)&addr;
    }

};

class Socket
{
    int sock;
public:
    Socket(int type)
    {
        sock = socket(PF_INET, type, 0); // TCP 소켓
    }

    // C++ 이름 탐색 법칙
    void bind(IPAddress* ip)
    {
        ::bind(sock, ip->getRawAddress(), sizeof(SOCKADDR_IN));
    }

    void listen(int backlog) { ::listen(sock, backlog); }
    void accept()
    {
        SOCKADDR_IN addr2 = { 0 };
        int sz = sizeof(addr2);

        ::accept(sock, (SOCKADDR*)&addr2, &sz);
    }
};


// 초기화/정리의 작업은 생성자/소멸자가 좋다 - RAII
class NetworkSystem
{
public:
    NetworkSystem()
    {
        WSADATA w;
        WSAStartup(0x202, &w); // 네트워크 라이브러리 초기화
    }

    ~NetworkSystem()
    {
        WSACleanup();
    }
};

// TCP 서버 프로그램을 하는데 필요한 클래스와 절차를
// 단순화시켜주는 상위 개념의 클래스를 제공하자.
// -> Facade Pattern

// => ACE (TCPServer, Process, Thread...)
//  C++ Network Programming I / II

// => boost asio / poco

class TCPServer
{
    NetworkSystem system;
    Socket sock;
public:
    TCPServer() : sock(SOCK_STREAM) {}

    void start(const char* ip, short port)
    {
        IPAddress ipaddr(ip, port);
        sock.bind(&ipaddr);
        sock.listen(5);
        sock.accept();
    }
};

int main()
{
    TCPServer server;
    server.start("127.0.0.1", 4000);
}



