#include "../../ProbSolvStart.h"

class IProbSolv
{
public:
    explicit IProbSolv(){}
    virtual ~IProbSolv(){}
    void Solve(){
        cout << typeid(*this).name() << ":\n";
        _Solve();
        cout << "\n";
   }
private:
    virtual void _Solve() = 0;
};
