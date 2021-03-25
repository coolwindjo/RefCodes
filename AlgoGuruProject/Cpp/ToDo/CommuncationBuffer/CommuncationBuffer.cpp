#if 1
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

typedef struct st
{
	int packet_no;
	int prior_level;
	struct st *next;
}PACKET;

PACKET buffer;
PACKET *last_packet;

void Input_Packet(PACKET& p)
{
	cin >> p.packet_no >> p.prior_level; // packet_no, prior_level 입력
}

#define SUCCESS				(0)
#define ERROR_PUT_PACKET	(-1)
#define ERROR_BUF_EMPTY		(-2)


vii g_viiBuffer;

int Put_Packet_to_Buffer(PACKET& p)
{
	/*/
	PACKET *pac;

	pac = new PACKET();

	*pac = p;

	last_packet->next = pac;
	last_packet = pac;
	/*/
	g_viiBuffer.push_back(ii(p.prior_level, p.packet_no));
	//*/

	return SUCCESS;
}
int Get_Packet_from_Buffer(PACKET& p)
{
	/*/
	if (buffer.next == (PACKET*)0) return ERROR_BUF_EMPTY;
	p = *buffer.next;	// get the node that is the next to head
	delete buffer.next;

	buffer.next = p.next;	// connect third node to HEAD
	/*/
    if (g_viiBuffer.empty()) return ERROR_BUF_EMPTY;
	ii pac = g_viiBuffer.back();
	g_viiBuffer.pop_back();
	p.prior_level = pac.first;
	p.packet_no = pac.second;

	//*/
	
	return SUCCESS;
}

class ProbSolv
{
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}

private:
    int _Solve(){
        int N;
        PACKET packet;

        cin >> N;	// 패킷의 수 입력
        
        last_packet = &buffer;
        packet.next = NULL;
        // 패킷의 수신
        for (int i = 0; i < N; i++)
        {
            Input_Packet(packet);
            Put_Packet_to_Buffer(packet);
        }
        
   	sort(g_viiBuffer.begin(), g_viiBuffer.end(),
	[](const ii &a, const ii &b){
		if (a.first == b.first) {
			return a.second > b.second;
		}
		return a.first > b.first;
	});
        // 패킷 처리순서 출력
        while (Get_Packet_from_Buffer(packet) == SUCCESS)
        {
            cout << packet.packet_no << " ";
        }

        return 0;
    } // _Solve()

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int numTCs = 0;
    cin >> numTCs;
    FOR (tc, numTCs) {
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
