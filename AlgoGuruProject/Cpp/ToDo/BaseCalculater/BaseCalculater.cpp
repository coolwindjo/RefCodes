#if 0
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"
constexpr char ALPHA[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int c2d(char c){
	if (c <= '9') return c - '0';
	return c - 'A' + 10;
}

class ProbSolv
{
	int m_B;
	string m_strS;
	string m_strD;
public:
    ProbSolv()
    {
		string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() >= 2){
				break;
            }
        }
		vstr vstrB_S_D = _SplitString(line, string(" \r\n\t"));
		m_B = std::stoi(vstrB_S_D[0]);
		m_strS = vstrB_S_D[1];
		m_strD = vstrB_S_D[2];
		
#ifdef TEST_OK
		for (auto str : vstrB_S_D){
			cout << str << " ";
		}
		cout <<endl;
#endif //TEST

        _Solve();
    }
    ~ProbSolv(){}
	
	vi Str2Vint(const string &str){
		string s = str;
		vi viS;
		if (s[0] == '-') {
			viS.push_back(-1);
			s = str.substr(1);
		}
		else {
			viS.push_back(1);
		}
		FOR(i, s.size()){
			int num;
			char c = s[i];
			num = c2d(c);
			viS.push_back(num);
		}
		return viS;
	}

	int GetSign(const int a, const int b){
		int sign = a*b;
		return sign;
	}
	
	ll Mult(const vi &viS, const vi &viD){
		int answer = 0;
		int lenS = viS.size() - 1;
		int lenD = viD.size() - 1;
		FOR_DEC(i, 1, viD.size()){
			int sum = 0;
			FOR_DEC(j, 1, viS.size()){
				sum += viD[i] * viS[j] * powl(m_B, lenS-j);
			}
#ifdef TEST_OK
			cout << "Test Sum(" << lenD-i << "): " << sum << endl;
#endif	// TEST	
			answer += sum * powl(m_B, lenD-i);
		}
#ifdef TEST_OK
		cout << "Test Answer : " << answer << endl;
#endif	// TEST	
		return answer;
	}
	
    vi vMultOpt(const vi &viS, const vi &viD){
		vi viAns;
		int lenS = viS.size() - 1;
		int lenD = viD.size() - 1;
		int maxLenAns = lenS + lenD;
		vi viReS;
		vi viReD;
		FOR(i, lenS){
			viReS.push_back(viS[lenS - i]);
		}
		FOR(i, lenD){
			viReD.push_back(viD[lenD - i]);
		}
		FOR(i, maxLenAns){
			viAns.push_back(0);
		}
		
		FOR(d, lenD){
			FOR(s, lenS){
				viAns[s+d] += viReS[s]*viReD[d];
			}
		}
		
		int carry = 0;
		FOR(i, viAns.size()){
			int carry_sum = viAns[i] + carry;
			viAns[i] = carry_sum % m_B;
			carry = carry_sum / m_B;
		}
		
		return viAns;
	}
	
	vi vMult(const vi &viS, const vi &viD){
		vi viAns;
		int lenS = viS.size() - 1;
		int lenD = viD.size() - 1;
		int maxLenAns = lenS + lenD;
		FOR(i, maxLenAns){
			viAns.push_back(0);
		}
		int kStart = 0;
		FOR_DEC(i, 1, viD.size()){
			vi viSum;
			int carry = 0;
			FOR_DEC(j, 1, viS.size()){
				int sum = (viD[i] * viS[j]) + carry;
				viSum.push_back(sum % m_B);
				carry = sum / m_B;
			}
			if (carry > 0){
				viSum.push_back(carry);
			}
#ifdef TEST_OK
			cout << "Test Sum(" << kStart << "): ";
			for (auto num: viSum){
				cout << num<< " ";
			}
			cout <<endl;
#endif //TEST
			carry = 0;
			FOR(k, viSum.size()){
				int sum = viAns[kStart+k] + viSum[k] + carry;
				viAns[kStart+k] = (sum % m_B);
				carry = sum / m_B;
			}
			if (carry > 0){
				viAns[kStart+viSum.size()]+=carry;
			}
			
			kStart++;
		}
		return viAns;
	}
	
	string ConvToBase(vi &viAns, const int B){
		string ans="";
		while(!viAns.empty()){
			if (viAns.back() == 0){
				viAns.pop_back();
			}
			else break;
		}
		FOR_DEC(i, 0, viAns.size()){
			ans += {ALPHA[viAns[i]]};
		}
		return ans;
	}

private:
    void _Solve(){
		vi viS = Str2Vint(m_strS);
		vi viD = Str2Vint(m_strD);
#ifdef TEST_OK
		cout << "Test viS : ";
		for (auto s : viS){
			cout << s << " ";
		}
		cout << endl;
		cout << "Test viD : ";
		for (auto d : viD){
			cout << d << " ";
		}
		cout << endl;
#endif	// TEST	
		int sign = GetSign(viS[0], viD[0]);
#ifdef TEST
		ll llAns = Mult(viS, viD);
		cout << "Test llAns: " << sign*llAns << endl;
#endif	// TEST	
		vi viAns = vMultOpt(viS, viD);
#ifdef TEST_OK
		cout << "Test viAns: ";
		for (auto num: viAns){
			cout << num<< " ";
		}
		cout <<endl;
#endif //TEST
		string strAns = ConvToBase(viAns, m_B);
		if (strAns.empty()) {
			cout << 0;
			return;
		}
		string strSign = sign == -1? "-" : "";
		string signedAns = strSign + strAns;
		
		cout << signedAns;
    } // _Solve()

#if 1 // 48dd
    vstr _SplitString(string line, const string &delims) {
#ifdef SPLIT_DEBUG
        cout << "\n1) line: " << line <<endl;
#endif
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' ';
        });
#ifdef SPLIT_DEBUG
        cout << "2) line: " << line <<endl;
#endif

        line.erase(newEnd, line.end());
#ifdef SPLIT_DEBUG
        cout << "3) line: " << line <<endl;
#endif

        while (line[line.length() - 1] == ' ') {
            line.pop_back();
        }
#ifdef SPLIT_DEBUG
        cout << "4) line: " << line <<endl;
#endif

        vstr vstrSplits;

        size_t prev = 0;
        size_t pos;
        while ((pos = line.find_first_of(delims, prev)) != string::npos) {
            if (pos > prev) {
                vstrSplits.push_back(line.substr(prev, pos-prev));
            }
#ifdef SPLIT_DEBUG
            for(string str : vstrSplits) {
                cout << str << " ";
            }
            cout <<endl;
#endif
            prev = pos + 1;
        }

        if (prev < line.length()) {
            vstrSplits.push_back(line.substr(prev, min(pos, line.length()) - prev + 1));
        }

        return vstrSplits;
    }
#endif

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
