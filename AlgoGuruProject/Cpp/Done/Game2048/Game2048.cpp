#include "../../ProbSolvStart.h"
typedef unsigned long long uint_t;

typedef enum {
	eR = 0, eD, eL, eU, eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = { {0,1},{1,0},{0,-1},{-1,0} };
constexpr int MAX_MOVES = 5;

//#define TEST
class ProbSolve
{
	int m_mapSizeN;
	int m_maxVal;

public:
	explicit ProbSolve(const int N) {
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
	virtual ~ProbSolve() {}

	void DFS(const vvi &map, const int numMoves, const Dir_e dir) {
		vvi movedMap(map);
#if 1
		//const int numMerges = 
        MoveWithQ(dir, movedMap);
#else
		//const int numMerges = 
        Move(dir, movedMap);
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
			DFS(movedMap, numMoves + 1, (Dir_e)nextDir);
		}
	}

	int MoveWithQ(const Dir_e dir, vvi &mapOut) {
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
					FillCell(row, col,
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
					FillCell(row, col,
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
					FillCell(row, col,
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
					FillCell(row, col,
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

	void FillCell(const int row, const int col,
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

	int Move(const Dir_e dir, vvi &mapOut) {
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

private:
	void _Solve(const vvi &map) {
		FOR(dir, eDIR_LEN) {
			DFS(map, 1, (Dir_e)dir);
		}
		cout << m_maxVal;
	}

};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int N = 0;
	cin >> N;
	ProbSolve ps(N);
	return 0;
}

