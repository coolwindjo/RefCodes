#include <iostream>
//#define STR
#ifdef STR
#include <string>
#else 
#include <list>
#endif
using namespace std;

inline static const int WarnIfNot(const int condFlag, const char* condition){
    if (condFlag == 0){
        cout << "Warning:[" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond)) 
#define P_IFNOT(cond, var) if(!W_IFNOT(cond)) cout << "= " << (var) << "\n";
#define FOR_INC(i,from,to) for(int (i)=(from); (i)<(to); (i)++)
#define FOR_DEC(i,from,to) for(int (i)=(from); (i)>=(to); (i)--)
#define FOR(i,to) FOR_INC((i),0,(to))

#ifdef STR
typedef string lc;
#else 
typedef list<char> lc;
#endif

const int MAX_S = 600000 + 1;
const int MAX_N = 500000 + 1;
char str[MAX_S];
char cmd[MAX_N];
int pos;
lc::iterator itPos;

const int Input(){
    int numCmds = 0;
    cin >> str;
    cin >> numCmds;
    FOR(i, numCmds){
        char c = 0;
        cin >> c;
        switch(c){
        case 'P':
            cin >> c;
            break;
        case 'L':
            c = 1;
            break;
        case 'D':
            c = 2;
            break;
        case 'B':
            c = 3;
            break;
        }
        cmd[i] = c;
    }
    return numCmds;
}

lc lcL;
int len = 0;
const int ParseStr(){
    while(str[len] != '\0'){
        lcL.push_back(str[len++]);
    }
    itPos = lcL.end();
    return len;
}

char* GetStr(){
    int i = 0;
    for(lc::iterator it = lcL.begin(); it != lcL.end() ;i++,it++){
        str[i] = *it;
    }
    str[i] = '\0';
    return str;
}

int Left(int pos){
    if (pos <= 0) return pos;
    pos--;
#ifdef STR
//    if (itPos == lcL.begin()) return pos;
#else 
#endif
    itPos--;
    return pos;
}

int Right(int pos){
    if (pos >= len) return pos;
    pos++;
#ifdef STR
//    if (itPos == lcL.end()) return pos;
#else 
#endif
    itPos++;
    return pos;
}

int Del(int pos){
    if (pos <= 0) return pos;
    lc::iterator it = itPos;
    lcL.erase(--it);
    len = (int)lcL.size();
    return --pos;
}

int Ins(int pos, char alpha){
    if (pos < 0) return pos;
    if (pos > len) return pos;
    lcL.insert(itPos, alpha);
#ifdef STR
    if (itPos != lcL.end()) itPos++;
#else 
#endif
    len = (int)lcL.size();
    return ++pos;
}

void EditStr(const int numCmds){
    int pos = ParseStr();
    FOR(i, numCmds){
        char a = cmd[i];
        switch(a){
        case 1:
            pos = Left(pos);
#ifdef TEST
            a = '<';
#endif
            break;
        case 2:
            pos = Right(pos);
#ifdef TEST
            a = '>';
#endif
            break;
        case 3:
            pos = Del(pos);
#ifdef TEST
            a = '~';
#endif
            break;
        default:
            pos = Ins(pos, a);
            break;
        }

#ifdef TEST
        cout << a << *itPos <<  pos << GetStr() <<endl;
#endif
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    const int numCmds = Input();

    EditStr(numCmds);

    cout << GetStr() <<endl;

    return 0;
}