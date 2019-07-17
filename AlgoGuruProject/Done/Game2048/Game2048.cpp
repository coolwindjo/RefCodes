#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static const int WarnIfNot(const int condFlag, const char* condition) {
	if (condFlag == 0)
	{
		cout << "Warning: [" << condition << "] is violated!\n";
	}
	return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT((cond))) cout << "= " << (var) <<endl;
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i),0,(to))
#define OOR(x,min,max) (((X)<(min)) || ((x)>(max)))

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef unsigned long long uint_t;
typedef queue<int> qi;

typedef enum {
	eR = 0, eD, eL, eU, eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = { {0,1},{1,0},{0,-1},{-1,0} };
constexpr int INF = 987654321;
constexpr int MAX_MOVES = 5;

//#define TEST
class CProbSolve
{
	int m_mapSizeN;
	int m_maxVal;

public:
	explicit CProbSolve(const int N) {
		m_mapSizeN = N;
		m_maxVal = 0;
		vvi map;
		FOR(row, m_mapSizeN) {
			vi viRow;
			FOR(col, m_mapSizeN) {
				int val = 0;
				cin >> val;
				viRow.push_back(val);
			}
			map.push_back(viRow);
		}
		_Solve(map);
	}
	virtual ~CProbSolve() {}

private:
	void _Solve(const vvi &map) {
		FOR(dir, eDIR_LEN) {
			_DFS(map, 1, (Dir_e)dir);
		}
		cout << m_maxVal;
	}

	void _DFS(const vvi &map, const int numMoves, const Dir_e dir) {
		vvi movedMap(map);
#if 1
		//const int numMerges = 
        _MoveWithQ(dir, movedMap);
#else
		//const int numMerges = 
        _Move(dir, movedMap);
#endif // 0

#ifdef TEST
		cout << endl;
		FOR(i, numMoves) cout << " ";
		cout << "#Moves:" << numMoves << " toward:" << dir;
		FOR(row, m_mapSizeN) {
			cout << endl;
			FOR(i, numMoves) cout << " ";
			FOR(col, m_mapSizeN) {
				cout << movedMap[row][col] << " ";
			}
		}
#endif // TEST

		if ((numMoves == MAX_MOVES)
            //|| (numMerges == 0) <= merges can be omitted for the next move.
            )
        {
			const int biggest = GetBiggest(movedMap);
			if (biggest > m_maxVal) {
				m_maxVal = biggest;
			}
#ifdef TEST
			cout << endl;
			FOR(i, numMoves) cout << " ";
			cout << "++++++++++Stop here!!++++++++" << endl;
#endif // TEST
			return;
		}

		FOR(nextDir, eDIR_LEN) {
			_DFS(movedMap, numMoves + 1, (Dir_e)nextDir);
		}
	}

	int _MoveWithQ(const Dir_e dir, vvi &mapOut) {
		int numMerges = 0;
		switch (dir)
		{
		case eR:
			FOR(row, m_mapSizeN) {
				qi qiVals;
				FOR_DEC(col, 0, m_mapSizeN) {
					const int val = mapOut[row][col];
					if (val > 0) {
						mapOut[row][col] = 0;
						qiVals.push(val);
					}
				}

				FOR_DEC(col, 0, m_mapSizeN) {
					_FillCell(row, col,
							  mapOut, qiVals, numMerges);
				}
			}
			break;
		case eD:
			FOR(col, m_mapSizeN) {
				qi qiVals;
				FOR_DEC(row, 0, m_mapSizeN) {
					const int val = mapOut[row][col];
					if (val > 0) {
						mapOut[row][col] = 0;
						qiVals.push(val);
					}
				}

				FOR_DEC(row, 0, m_mapSizeN) {
					_FillCell(row, col,
							  mapOut, qiVals, numMerges);
				}
			}
			break;
		case eL:
			FOR(row, m_mapSizeN) {
				qi qiVals;
				FOR_INC(col, 0, m_mapSizeN) {
					const int val = mapOut[row][col];
					if (val > 0) {
						mapOut[row][col] = 0;
						qiVals.push(val);
					}
				}

				FOR_INC(col, 0, m_mapSizeN) {
					_FillCell(row, col,
							  mapOut, qiVals, numMerges);
				}
			}
			break;
		case eU:
			FOR(col, m_mapSizeN) {
				qi qiVals;
				FOR_INC(row, 0, m_mapSizeN) {
					const int val = mapOut[row][col];
					if (val > 0) {
						mapOut[row][col] = 0;
						qiVals.push(val);
					}
				}

				FOR_INC(row, 0, m_mapSizeN) {
					_FillCell(row, col,
							  mapOut, qiVals, numMerges);
				}
			}
			break;
		default:
			P_IFNOT(dir < eDIR_LEN, dir);
			break;
		}

		return numMerges;
	}

	void _FillCell(const int row, const int col,
				   vvi &mapOut, qi &qiValsOut, int &numMergesOut) {
		int pivotVal = -1;

		// A. visit next
		while (!qiValsOut.empty()) {
			const int val = qiValsOut.front();

			// C. check to be merged
			if (val == pivotVal) {
				mapOut[row][col] = pivotVal * 2;
				pivotVal = -1;
				numMergesOut++;
#ifdef TEST
				cout << "\n" << val << " is merged to " << row << "," << col << ":" << mapOut[row][col];
#endif // TEST
				qiValsOut.pop();
				break;
			}
			else {
				if (pivotVal != -1) {
					pivotVal = -1;
					break;
				}
			}

			// D. set pivot
			pivotVal = val;
			mapOut[row][col] = pivotVal;
			qiValsOut.pop();
		}
	}

	int _Move(const Dir_e dir, vvi &mapOut) {
		int numMerges = 0;
		switch (dir)
		{
		case eR:
			FOR(row, m_mapSizeN) {
				int pivotVal = 0;
				int pivotCol = 0;
				int emptyCellCol = 0;
				FOR_DEC(col, 0, m_mapSizeN) {
					// A. visit next
					const int val = mapOut[row][col];
					if (val > 0) {
						if (pivotVal != 0) {
							// C. check to be merged
							if (pivotVal == val) {
								mapOut[row][pivotCol] = pivotVal * 2;
								pivotVal = 0;
								mapOut[row][col] = 0;
								numMerges++;
#ifdef TEST
								cout << "\n" << row << "," << col << ":" << val << " is merged to " << row << "," << pivotCol << ":" << mapOut[row][pivotCol];
#endif // TEST
								// G. set empty cell
								if (emptyCellCol == 0) {
									emptyCellCol = col;
								}
								continue;
							}
						}

						// D. set pivot
						pivotVal = val;
						if (emptyCellCol > 0) {
							pivotCol = emptyCellCol;

							// E. move pivot value into empty cell
							mapOut[row][emptyCellCol] = pivotVal;
							mapOut[row][col] = 0;
#ifdef TEST
							cout << "\n" << row << "," << col << ":" << pivotVal << " is moved to " << row << "," << emptyCellCol;
#endif // TEST
							// F. set next empty cell
							if (emptyCellCol > col) {
								--emptyCellCol;
							}
						}
						else {
							pivotCol = col;
						}
					}
					else {
						// B. set empty cell
						if (emptyCellCol == 0) {
							emptyCellCol = col;
						}
					}
				}
			}
			break;
		case eD:
			FOR(col, m_mapSizeN) {
				int pivotVal = 0;
				int pivotRow = 0;
				int emptyCellRow = 0;
				FOR_DEC(row, 0, m_mapSizeN) {
					// A. visit next
					const int val = mapOut[row][col];
					if (val > 0) {
						if (pivotVal != 0) {
							// C. check to be merged
							if (pivotVal == val) {
								mapOut[pivotRow][col] = pivotVal * 2;
								pivotVal = 0;
								mapOut[row][col] = 0;
								numMerges++;
#ifdef TEST
								cout << "\n" << row << "," << col << ":" << val << " is merged to " << pivotRow << "," << col << ":" << mapOut[pivotRow][col];
#endif // TEST
								// G. set empty cell
								if (emptyCellRow == 0) {
									emptyCellRow = row;
								}
								continue;
							}
						}

						// D. set pivot
						pivotVal = val;
						if (emptyCellRow > 0) {
							pivotRow = emptyCellRow;

							// E. move pivot value into empty cell
							mapOut[emptyCellRow][col] = pivotVal;
							mapOut[row][col] = 0;
#ifdef TEST
							cout << "\n" << row << "," << col << ":" << pivotVal << " is moved to " << emptyCellRow << "," << col;
#endif // TEST
							// F. set next empty cell
							if (emptyCellRow > row) {
								--emptyCellRow;
							}
						}
						else {
							pivotRow = row;
						}
					}
					else {
						// B. set empty cell
						if (emptyCellRow == 0) {
							emptyCellRow = row;
						}
					}
				}
			}
			break;
		case eL:
			FOR(row, m_mapSizeN) {
				int pivotVal = 0;
				int pivotCol = 0;
				int emptyCellCol = m_mapSizeN;
				FOR_INC(col, 0, m_mapSizeN) {
					// A. visit next
					const int val = mapOut[row][col];
					if (val > 0) {
						if (pivotVal != 0) {
							// C. check to be merged
							if (pivotVal == val) {
								mapOut[row][pivotCol] = pivotVal * 2;
								pivotVal = 0;
								mapOut[row][col] = 0;
								numMerges++;
#ifdef TEST
								cout << "\n" << row << "," << col << ":" << val << " is merged to " << row << "," << pivotCol << ":" << mapOut[row][pivotCol];
#endif // TEST
								// G. set empty cell
								if (emptyCellCol == m_mapSizeN) {
									emptyCellCol = col;
								}
								continue;
							}
						}

						// D. set pivot
						pivotVal = val;
						if (emptyCellCol < m_mapSizeN) {
							pivotCol = emptyCellCol;

							// E. move pivot value into empty cell
							mapOut[row][emptyCellCol] = pivotVal;
							mapOut[row][col] = 0;
#ifdef TEST
							cout << "\n" << row << "," << col << ":" << pivotVal << " is moved to " << row << "," << emptyCellCol;
#endif // TEST
							// F. set next empty cell
							if (emptyCellCol < col) {
								++emptyCellCol;
							}
						}
						else {
							pivotCol = col;
						}
					}
					else {
						// B. set empty cell
						if (emptyCellCol == m_mapSizeN) {
							emptyCellCol = col;
						}
					}
				}
			}
			break;
		case eU:
			FOR(col, m_mapSizeN) {
				int pivotVal = 0;
				int pivotRow = 0;
				int emptyCellRow = m_mapSizeN;
				FOR_INC(row, 0, m_mapSizeN) {
					// A. visit next
					const int val = mapOut[row][col];
					if (val > 0) {
						if (pivotVal != 0) {
							// C. check to be merged
							if (pivotVal == val) {
								mapOut[pivotRow][col] = pivotVal * 2;
								pivotVal = 0;
								mapOut[row][col] = 0;
								numMerges++;
#ifdef TEST
								cout << "\n" << row << "," << col << ":" << val << " is merged to " << pivotRow << "," << col << ":" << mapOut[pivotRow][col];
#endif // TEST
								// G. set empty cell
								if (emptyCellRow == m_mapSizeN) {
									emptyCellRow = row;
								}
								continue;
							}
						}

						// D. set pivot
						pivotVal = val;
						if (emptyCellRow < m_mapSizeN) {
							pivotRow = emptyCellRow;

							// E. move pivot value into empty cell
							mapOut[emptyCellRow][col] = pivotVal;
							mapOut[row][col] = 0;
#ifdef TEST
							cout << "\n" << row << "," << col << ":" << pivotVal << " is moved to " << emptyCellRow << "," << col;
#endif // TEST
							// F. set next empty cell
							if (emptyCellRow < row) {
								++emptyCellRow;
							}
						}
						else {
							pivotRow = row;
						}
					}
					else {
						// B. set empty cell
						if (emptyCellRow == m_mapSizeN) {
							emptyCellRow = row;
						}
					}
				}
			}
			break;
		default:
			P_IFNOT(dir < eDIR_LEN, dir);
			break;
		}

		return numMerges;
	}

	int GetBiggest(const vvi map) {
		int biggest = 0;
		FOR(row, m_mapSizeN) {
			FOR(col, m_mapSizeN) {
				const int val = map[row][col];
				if (val > biggest) {
					biggest = val;
				}
			}
		}
		return biggest;
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int N = 0;
	cin >> N;
	CProbSolve ps(N);
	return 0;
}

