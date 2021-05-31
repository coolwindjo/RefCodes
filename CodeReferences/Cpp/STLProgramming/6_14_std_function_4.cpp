#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <vector>
using namespace std;
using namespace std::placeholders;

class NotificationCenter
{
private:
    /*/
    map< string, function< void(void*) > > noti_map;
    /*/
    using HANDLER = function< void(void*) >;
    map< string, vector<HANDLER> > noti_map;
    //*/
public:
    NotificationCenter(/* args */) {}
    ~NotificationCenter() {}

    void Register(string key, HANDLER h)
    {
        noti_map[key].push_back(h);
    }

    void Notify(string key, void* param)
    {
        vector<HANDLER> &v = noti_map[key];
        for (auto &f : v) {
            f(param);
        }
    }
};

/*/
    void f1(void* p)                {cout<<"f1"<<endl;}
    void f2(void* p, int a, int b)  {cout<<"f2"<<endl;}
/*/
class HandlerFunctions
{
public:
    void f1(void* p)                {cout<<"f1"<<endl;}
    void f2(void* p, int a, int b)  {cout<<"f2"<<endl;}
};
//*/

int main()
{

    NotificationCenter nc;
    /*/
    nc.Register("CONNECT_WIFI", &f1);
    nc.Register("CONNECT_WIFI", bind(&f2, _1, 0, 0));
    /*/
    HandlerFunctions hf;
    nc.Register("CONNECT_WIFI", bind(&HandlerFunctions::f1, ref(hf), _1));
    nc.Register("CONNECT_WIFI", bind(&HandlerFunctions::f2, ref(hf), _1, 0, 0));
    //*/

    nc.Notify("CONNECT_WIFI", (void*)0);
    return 0;
}