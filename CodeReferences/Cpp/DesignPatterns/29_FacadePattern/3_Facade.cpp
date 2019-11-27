// 8_Facade

#include <iostream>
using namespace std;

#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib") // Compile �ɼ����� �� ���� Linking file�� ���ο� �ھƳ��� �� ����

// SRP (Single Responsiblity Principal) : ���� å���� ��Ģ
// - Module (Class, Function, Variable)�� �� �ϳ����� å���� ������ �Ѵ�.

// TCP Server Programming�� �ϴµ� �ʿ��� Class�� ������ 
// �ܼ�ȭ�����ִ� ���� ������ Ŭ������ ��������.
// -> Facade Pattern
// => ACE (TCPServer, Process, Thread...)
// C++ Network Programming I / II (Server ����� Programming �� Bible)
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
    // string::c_str()�� ����
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
        sock = socket(PF_INET, type, 0); // TCP ����
    }

    // C++ �̸� Ž�� ��Ģ
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


// �ʱ�ȭ/������ �۾��� ������/�Ҹ��ڰ� ���� - RAII
class NetworkSystem
{
public:
    NetworkSystem()
    {
        WSADATA w;
        WSAStartup(0x202, &w); // ��Ʈ��ũ ���̺귯�� �ʱ�ȭ
    }

    ~NetworkSystem()
    {
        WSACleanup();
    }
};

// TCP ���� ���α׷��� �ϴµ� �ʿ��� Ŭ������ ������
// �ܼ�ȭ�����ִ� ���� ������ Ŭ������ ��������.
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



