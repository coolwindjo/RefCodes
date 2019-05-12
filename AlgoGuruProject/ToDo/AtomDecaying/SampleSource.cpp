#pragma GCC optimize("O3")
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>
using namespace std;

struct Atom_t {
	int x, y, dir, energy, idx;
};
struct doubleDistAtoms {
	int doubleDist, i, j;
};
typedef pair<int, int> pii;

int arAtomD[1001];
Atom_t atomQ[4][1001];
int arAtomEnergy[1001], qidx;
doubleDistAtoms doubleDistTwoAtomsQ[12000002];

void SimulateAtomMove(const int dirIdx, int(&arNumAtomsByDir)[4], int &qidx, int &numAtoms)
{
	for (int atomIdx = 0; atomIdx < arNumAtomsByDir[dirIdx]; ++atomIdx)
	{
		int isCollided = 0;
		// added{
		for (int addDirIdx = 0; (dirIdx + addDirIdx) < 3; addDirIdx++)
		{
			const int otherDirIdx = ((dirIdx + addDirIdx) + 1);
			//} added
			for (int otherAtomIdx = 0; otherAtomIdx < arNumAtomsByDir[otherDirIdx]; ++otherAtomIdx)
			{
				const int distX = abs(atomQ[dirIdx][atomIdx].x - atomQ[otherDirIdx][otherAtomIdx].x);
				const int distY = abs(atomQ[dirIdx][atomIdx].y - atomQ[otherDirIdx][otherAtomIdx].y);

				// added{
				if (((dirIdx == 0) || (dirIdx == 2)) && (otherDirIdx == (dirIdx+1)))
				{
					//} added

					// on a line
					if (((!distX && distY) && (dirIdx == 0))
						|| ((distX && !distY) && (dirIdx == 2)))
					{
						isCollided = 1;
						doubleDistTwoAtomsQ[qidx++] = { ((distY == 0) ? distX : distY),
							atomQ[dirIdx][atomIdx].idx,atomQ[otherDirIdx][otherAtomIdx].idx };
					}

					continue;
				}
								
				if ((distX == distY) && (distX > 0))
				{
					// 2 dim2
					isCollided = 1;
					doubleDistTwoAtomsQ[qidx++] = { 2*distX,
						atomQ[dirIdx][atomIdx].idx,atomQ[otherDirIdx][otherAtomIdx].idx };
				}

			}

		}	// for (int addDirIdx = 0; (dirIdx + addDirIdx) < 3; addDirIdx++)

		if (isCollided == 0)
			numAtoms--;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	int t, n;
	//freopen("sample_input.txt","r", stdin);
	cin >> t;

	int arNumAtomsByDir[4];
	for (int tc = 1; tc <= t; ++tc)
	{
		int qidx = 0;
		cin >> n;
		arNumAtomsByDir[0] = arNumAtomsByDir[1] = arNumAtomsByDir[2] = arNumAtomsByDir[3] = 0;
		for (int atomIdx = 0; atomIdx < n; ++atomIdx)
		{
			int x, y, dirIdx, energy;
			cin >> x >> y >> dirIdx >> energy;
			atomQ[dirIdx][arNumAtomsByDir[dirIdx]++] = { x,y,dirIdx,energy,atomIdx };
			arAtomEnergy[atomIdx] = energy;
			arAtomD[atomIdx] = -1;
		}

		SimulateAtomMove(0, arNumAtomsByDir, qidx, n);
		SimulateAtomMove(1, arNumAtomsByDir, qidx, n);
		SimulateAtomMove(2, arNumAtomsByDir, qidx, n);

		sort(doubleDistTwoAtomsQ, doubleDistTwoAtomsQ + qidx,
			 [&](const doubleDistAtoms &a, const doubleDistAtoms &b) {
			return a.doubleDist < b.doubleDist;
		});

		int ans = 0;
		for (int shortestDistIdx = 0; n && shortestDistIdx<qidx; ++shortestDistIdx)
		{
			if (arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].i] == doubleDistTwoAtomsQ[shortestDistIdx].doubleDist)
			{
				// atom i is already updated!
				if (arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].j] == -1)
				{
					// atom j is not visited
					arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].j] = doubleDistTwoAtomsQ[shortestDistIdx].doubleDist;
					ans += arAtomEnergy[doubleDistTwoAtomsQ[shortestDistIdx].j];
					n--;
				}
			}
			else if (arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].i] == -1) 
			{
				// atom i is not visited
				if (arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].j] == -1)
				{
					// both are first visit
					arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].i] = arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].j] = doubleDistTwoAtomsQ[shortestDistIdx].doubleDist;
					ans += arAtomEnergy[doubleDistTwoAtomsQ[shortestDistIdx].i] + arAtomEnergy[doubleDistTwoAtomsQ[shortestDistIdx].j];
					n -= 2;
				}
				else if (arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].j] == doubleDistTwoAtomsQ[shortestDistIdx].doubleDist)
				{
					// atom j is already updated!
					arAtomD[doubleDistTwoAtomsQ[shortestDistIdx].i] = doubleDistTwoAtomsQ[shortestDistIdx].doubleDist;
					n--;
					ans += arAtomEnergy[doubleDistTwoAtomsQ[shortestDistIdx].i];
				}
			}
		}

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}