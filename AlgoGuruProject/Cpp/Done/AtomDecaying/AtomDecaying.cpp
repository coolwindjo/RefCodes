#include "../../ProbSolvStart.h"

// #define PQII

#ifdef PQII
typedef priority_queue<ii> pqii;
typedef enum {
	eX = 0, eY, eXY_LEN
} XorY_e;
#endif // PQII

typedef enum {
	eU = 0, eD, eL, eR, eDIR_LEN
} Dir_e;

constexpr int N_DIR[eDIR_LEN] = {eD, eU, eR, eL};
constexpr int INIT_MAP_SIZE = 1000 + 1;
constexpr int MAX_DBLD_TIME = 2 * 2 * INIT_MAP_SIZE;

typedef struct Atom
{
	explicit Atom(int inX, int inY, int inDir, int inEnrg)
		: x(inX), y(inY), dir(inDir), enrg(inEnrg)
	{}
	int x;
	int y;
	int dir;
	int enrg;
} Atom_t;

// time, (at1, at2)
typedef i_ii Crash;
class ProbSolve
{
	int m_numAtomsN;
	vector<Crash> m_vCrashes;
	vector<Atom_t> m_vAtoms;
	vvi m_vviAtomIdx;
#ifdef PQII
	pqii m_pqiiAtmIdxByX;
	pqii m_pqiiAtmIdxByY;
#endif // PQII

public:
	explicit ProbSolve(const int N) {
		m_numAtomsN = N;
		FOR(i, eDIR_LEN){
			vi viEmpty;
			m_vviAtomIdx.push_back(viEmpty);
		}
		FOR(atIdx, m_numAtomsN) {
			int x, y, dir, enrg;
			cin >> x >> y >> dir >> enrg;
			m_vAtoms.push_back(Atom(x, y, dir, enrg));
			m_vviAtomIdx[dir].push_back(atIdx);
#ifdef PQII
			m_pqiiAtmIdxByX.push(ii(x, atIdx));
			m_pqiiAtmIdxByY.push(ii(y, atIdx));
#endif // PQII
		}

		_Solve();
	}
	virtual ~ProbSolve(){}

private:
	void _Solve() {
		// Find orthogonal crashes of earlier time than the times of relative atoms
		_FindOrthoCrash();
	
#ifdef TEST
		cout << "\nUpdated Atom list\n";
		FOR(atIdx, m_vAtoms.size()) {
			const Atom_t atm = m_vAtoms[atIdx];
			cout << atm.dir << "(" << atm.x << "," << atm.y << ")\t";
		}
		cout << "\nUpdated Crash list\n";
		FOR(crIdx, m_vCrashes.size()) {
			const Crash dbldtime_at1at2 = m_vCrashes[crIdx];
			cout << dbldtime_at1at2.first <<
				"(" << dbldtime_at1at2.second.first << "," << dbldtime_at1at2.second.second << ")\t";
		}
		cout << "\n";
#endif // TEST

		_FindLinearCrash();

#ifdef PQII
		// Generate Y sorted lists for the same X for vertical linear crash
		// U-D for each pair of same X
		vector<pqii> vpqiiSortedYListsForSameXs;
		_FillSortedYListsForSameX(vpqiiSortedYListsForSameXs);
#ifdef TEST
		FOR(i, vpqiiSortedYListsForSameXs.size()) {
			_PrintAtoms(vpqiiSortedYListsForSameXs[i]);
		}
#endif // TEST

		// Generate X sorted lists for the same Y for horizontral linear crash
		// L-R for each pair of same Y
		vector<pqii> vpqiiSortedXListsForSameYs;
		_FillSortedXListsForSameY(vpqiiSortedXListsForSameYs);
#ifdef TEST
		FOR(i, vpqiiSortedXListsForSameYs.size()) {
			_PrintAtoms(vpqiiSortedXListsForSameYs[i]);
		}
#endif // TEST

		// Find linear crashes and update dbldTimes of atoms
		const int numXs = (int)vpqiiSortedYListsForSameXs.size();
		FOR(xIdx, numXs) {
			_FindLinearCrash(vpqiiSortedYListsForSameXs[xIdx]);
		}
		const int numYs = (int)vpqiiSortedXListsForSameYs.size();
		FOR(yIdx, numYs) {
			_FindLinearCrash(vpqiiSortedXListsForSameYs[yIdx]);
		}
#endif // PQII

#ifdef TEST
		cout << "\nFinal Atom list\n";
		FOR(atIdx, m_vAtoms.size()) {
			const Atom_t atm = m_vAtoms[atIdx];
			cout << atm.dir << "(" << atm.x << "," << atm.y << ")\t";
		}

		cout << "\nFinal Crash list\n";
		FOR(crIdx, m_vCrashes.size()) {
			const Crash dbldtime_at1at2 = m_vCrashes[crIdx];
			cout << dbldtime_at1at2.first <<
				"(" << dbldtime_at1at2.second.first << "," << dbldtime_at1at2.second.second << ")\t";
		}
		cout << "\n";
#endif // TEST

		// Sum up the energy of atoms with the limited time
		const int energySum = _SumUpEnergy();
		cout << energySum << "\n";
	}

	void _FindOrthoCrash()
	{
		for(int atI : m_vviAtomIdx[eD]) {
			for(int atJ : m_vviAtomIdx[eR]) {
				const Atom_t &at1 = m_vAtoms[atI];
				const Atom_t &at2 = m_vAtoms[atJ];
				const int xVector = at1.x - at2.x;
				const int yVector = at1.y - at2.y;
				if (xVector == yVector) {
					const int dbldTime = 2 * xVector;
					m_vCrashes.push_back(Crash(dbldTime, ii(atI, atJ)));
				}
			}
		}
		for(int atI : m_vviAtomIdx[eL]) {
			for(int atJ : m_vviAtomIdx[eU]) {
				const Atom_t &at1 = m_vAtoms[atI];
				const Atom_t &at2 = m_vAtoms[atJ];
				const int xVector = at1.x - at2.x;
				const int yVector = at1.y - at2.y;
				if (xVector == yVector) {
					const int dbldTime = 2 * xVector;
					m_vCrashes.push_back(Crash(dbldTime, ii(atI, atJ)));
				}
			}
		}
		for(int atI : m_vviAtomIdx[eD]) {
			for(int atJ : m_vviAtomIdx[eL]) {
				const Atom_t &at1 = m_vAtoms[atI];
				const Atom_t &at2 = m_vAtoms[atJ];
				const int xVector = at2.x - at1.x;
				const int yVector = at1.y - at2.y;
				if (xVector == yVector) {
					const int dbldTime = 2 * xVector;
					m_vCrashes.push_back(Crash(dbldTime, ii(atI, atJ)));
				}
			}
		}
		for(int atI : m_vviAtomIdx[eR]) {
			for(int atJ : m_vviAtomIdx[eU]) {
				const Atom_t &at1 = m_vAtoms[atI];
				const Atom_t &at2 = m_vAtoms[atJ];
				const int xVector = at2.x - at1.x;
				const int yVector = at1.y - at2.y;
				if (xVector == yVector) {
					const int dbldTime = 2 * xVector;
					m_vCrashes.push_back(Crash(dbldTime, ii(atI, atJ)));
				}
			}
		}
	}

	void _FindLinearCrash()
	{
		for(int atI : m_vviAtomIdx[eD]) {
			for(int atJ : m_vviAtomIdx[eU]) {
				const Atom_t &at1 = m_vAtoms[atI];
				const Atom_t &at2 = m_vAtoms[atJ];
				const int xVector = at1.x - at2.x;
				if (xVector != 0) continue;
		
				const int yVector = at1.y - at2.y;
				if (yVector > 0) {
					const int dbldTime = yVector;
					m_vCrashes.push_back(Crash(dbldTime, ii(atI, atJ)));
				}
			}
		}
		for(int atI : m_vviAtomIdx[eL]) {
			for(int atJ : m_vviAtomIdx[eR]) {
				const Atom_t &at1 = m_vAtoms[atI];
				const Atom_t &at2 = m_vAtoms[atJ];
				const int yVector = at1.y - at2.y;
				if (yVector != 0) continue;

				const int xVector = at1.x - at2.x;
				if (xVector > 0) {
					const int dbldTime = xVector;
					m_vCrashes.push_back(Crash(dbldTime, ii(atI, atJ)));
				}
			}
		}
	}

	int _SumUpEnergy() {
		int enrgSum = 0;
		sort(m_vCrashes.begin(), m_vCrashes.end());
		m_vCrashes.erase(unique(m_vCrashes.begin(), m_vCrashes.end()), m_vCrashes.end());
		const int numCrashes = (int)m_vCrashes.size();
		FOR(crIdx, numCrashes) {
			const Crash dbldTime_at1at2 = m_vCrashes[crIdx];
			Atom_t &atm1 = m_vAtoms[dbldTime_at1at2.second.first];
			Atom_t &atm2 = m_vAtoms[dbldTime_at1at2.second.second];
			const int dbldTime = dbldTime_at1at2.first;
			if ((atm1.enrg < 0) && (atm1.enrg != -dbldTime)) continue;
			if ((atm2.enrg < 0) && (atm2.enrg != -dbldTime)) continue;
			if (atm1.enrg > 0) {
				enrgSum += atm1.enrg;
				atm1.enrg = -dbldTime;
			}
			if (atm2.enrg > 0) {
				enrgSum += atm2.enrg;
				atm2.enrg = -dbldTime;
			}
		}
		return enrgSum;
	}

#ifdef PQII
	void _FindLinearCrash(pqii & pqiiSortedList)
	{
		stack<ii> atmS;
		while (!pqiiSortedList.empty()) {
			const ii XorY_atIdx = pqiiSortedList.top(); pqiiSortedList.pop();
			const Atom_t atm = m_vAtoms[XorY_atIdx.second];
			if (!atmS.empty()) {
				const ii prev_XorY_atIdx = atmS.top();
				// filter out duplicate atom index
				if (XorY_atIdx.second == prev_XorY_atIdx.second) continue;
				const Atom_t prev_atm = m_vAtoms[prev_XorY_atIdx.second];
				const int dbldTime = prev_XorY_atIdx.first - XorY_atIdx.first;
				if ((prev_atm.dir == eD) || (prev_atm.dir == eL)) {
					if ((atm.dir == eU) || (atm.dir == eR)) {
						const int smallerIdx = min(XorY_atIdx.second, prev_XorY_atIdx.second);
						const int biggerIdx = max(XorY_atIdx.second, prev_XorY_atIdx.second);
						m_vCrashes.push_back(Crash(dbldTime, ii(smallerIdx, biggerIdx)));
						atmS.pop();
						continue;
					}
				}
			}
			atmS.push(XorY_atIdx);
		}
	}

	void _FillSortedYListsForSameX(std::vector<pqii> &vpqiiSortedYListsForSameXs)
	{
		_FillSortedLists(eX, m_pqiiAtmIdxByX, vpqiiSortedYListsForSameXs);
	}

	void _FillSortedXListsForSameY(std::vector<pqii> &vpqiiSortedXListsForSameYs)
	{
		_FillSortedLists(eY, m_pqiiAtmIdxByY, vpqiiSortedXListsForSameYs);
	}

	void _FillSortedLists(const XorY_e XorY, pqii &pqiiAtmIdxByXorY, std::vector<pqii> &vpqiiSrtdXorYListsForSmYorXs)
	{
		Dir_e validDir = eDIR_LEN;
		if (XorY == eX) {
			validDir = eU;
		}
		else {
			validDir = eR;
		}
		int prevXorY = INF;
		ii prev_XorY_atIdx = make_pair(INF, INF);
		while (!pqiiAtmIdxByXorY.empty()) {
			const ii XorY_atIdx = pqiiAtmIdxByXorY.top(); pqiiAtmIdxByXorY.pop();
			const int ai = XorY_atIdx.second;
			const Atom_t atm = m_vAtoms[ai];
			if ((atm.dir != validDir) && (atm.dir != N_DIR[validDir])) continue;
			if (prev_XorY_atIdx.first != INF) {
				// from the second one
				const int prevAi = prev_XorY_atIdx.second;
				const Atom_t prevAtm = m_vAtoms[prevAi];
				if (XorY_atIdx.first == prev_XorY_atIdx.first) {
					// from the second one of the same XorY
					ii prev_YorX_atIdx;
					ii YorX_atIdx;
					if (XorY == eX) {
						prev_YorX_atIdx = ii(prevAtm.y, prevAi);
						YorX_atIdx = ii(atm.y, ai);
					}
					else {
						prev_YorX_atIdx = ii(prevAtm.x, prevAi);
						YorX_atIdx = ii(atm.x, ai);
					}
					if (XorY_atIdx.first != prevXorY) {
						pqii pqiiSortedAtmIdxByYorX;
						pqiiSortedAtmIdxByYorX.push(prev_YorX_atIdx);
						pqiiSortedAtmIdxByYorX.push(YorX_atIdx);
						vpqiiSrtdXorYListsForSmYorXs.push_back(pqiiSortedAtmIdxByYorX);
					}
					else {
						vpqiiSrtdXorYListsForSmYorXs.back().push(YorX_atIdx);
					}
					prevXorY = XorY_atIdx.first;
				}
			}
			prev_XorY_atIdx = XorY_atIdx;
		}
	}

	void _PrintAtoms(pqii & pqiiAtIdxByXorY) {
		cout << "\n";
		pqii pqiiTmp;
		while (!pqiiAtIdxByXorY.empty()) {
			const ii XorY_atIdx = pqiiAtIdxByXorY.top(); pqiiAtIdxByXorY.pop();
			const int ai = XorY_atIdx.second;
			const Atom_t atm = m_vAtoms[ai];
			cout << atm.dir << "(" << atm.x << "," << atm.y << ")\t";
			pqiiTmp.push(XorY_atIdx);
		}
		pqiiAtIdxByXorY = pqiiTmp;
		cout << "\n";
	}
#endif // PQII
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
		int N = 0;
		cin >> N;
		cout << "#" << tc + 1 << " ";
		ProbSolve ps(N);
	}
	return 0;
}