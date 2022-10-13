#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#define MAX 50000

std::mutex g_lock;

std::vector<std::vector<int>> multiplyMatrixes(const std::vector<std::vector<int>>& firstMatrix, const std::vector<std::vector<int>>& secondMatrix) {
	std::vector<std::vector<int>> answer;
	// Create Null Matrix
	std::vector<int> nullString;
	for (int i = 0; i < firstMatrix.size(); i++) {
		nullString.push_back(0);
	}
	for (int i = 0; i < secondMatrix[0].size(); i++) {
		answer.push_back(nullString);
	}
	// Multiply
	for (int i = 0; i < firstMatrix.size(); i++)
	{
		for (int j = 0; j < secondMatrix[0].size(); j++)
		{
			for (int k = 0; k < firstMatrix[0].size(); k++)
				answer[j][i] += firstMatrix[i][k] * secondMatrix[k][j];
		}
	}
	for (int i = 0; i < answer.size(); i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			std::cout << answer[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "gfgggggggggg\n";
	return answer;
}

std::vector<std::vector<int>> sumOfMatrixes(const std::vector<std::vector<int>>& firstMatrix, const std::vector<std::vector<int>>& secondMatrix) {
	std::vector<std::vector<int>> answer;
	// Create Null Matrix
	std::vector<int> nullString;
	for (int i = 0; i < firstMatrix.size(); i++) {
		nullString.push_back(0);
	}
	for (int i = 0; i < firstMatrix[0].size(); i++) {
		answer.push_back(nullString);
	}
	for (int i = 0; i < firstMatrix.size(); i++) {
		for (int j = 0; j < firstMatrix[0].size(); j++) {
			answer[i][j] += firstMatrix[i][j] + secondMatrix[i][j];
		}
	}
	std:: cout << "sum!!!";
	for (int i = 0; i < answer.size(); i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			std::cout << answer[i][j] << " ";
		}
		std::cout << "\n";
	}
	return answer;
}

std::vector<std::vector<int>> sumOfMatrixes(const std::vector<std::vector<std::vector<int>>>& masMatrix) {
	std::vector<std::vector<int>> answer;
	int size = masMatrix[0].size();
	std::vector<int> nullString;
	for (int i = 0; i < size; i++) {
		nullString.push_back(0);
	}
	for (int i = 0; i < size; i++) {
		answer.push_back(nullString);
	}
	for (int i = 0; i < masMatrix.size(); i++) {
		answer = sumOfMatrixes(answer, masMatrix[i]);
	}
	return answer;
}

std::vector<std::vector<int>> creationOfBlock(const std::vector<std::vector<int>>& matrix, std::pair<int, int> firstP, std::pair<int, int> secondP) {
	std::vector<std::vector<int>> block;
	for (int i = firstP.first; i <= secondP.first; i++) {
		std::vector<int> tmp;
		for (int j = firstP.second; j <= secondP.second; j++) {
			tmp.push_back(matrix[i][j]);
		}
		block.push_back(tmp);
	}
	return block;
}

std::vector<std::vector<std::vector<std::vector<int>>>> divisionIntoBlocks(const int a, const std::vector<std::vector<int>>& matrix) {
	int amountOfBlocks = (int)(matrix.size() / a);
	std::vector<std::vector<std::vector<std::vector<int>>>> division;
	bool remainder = false;
	if (matrix.size() != a * amountOfBlocks) {
		remainder = true;
	}
	for (int i = 0; i < matrix.size() - a + 1; i += a) {
		std::vector < std::vector < std::vector<int>>> tmp;
		for(int j = 0; j < matrix.size() - a + 1; j += a) {
			tmp.push_back(creationOfBlock(matrix, std::make_pair(i, j), std::make_pair(i + a - 1, j + a - 1)));
		}
		if (remainder && (i + a) < matrix.size()) {
			tmp.push_back(creationOfBlock(matrix, std::make_pair(i, a * amountOfBlocks), std::make_pair(i + a - 1, matrix.size() - 1)));
		}
		division.push_back(tmp);
	}
	if (remainder) {
		std::vector < std::vector < std::vector<int>>> tmp;
		for (int i = 0; i < matrix.size() - a + 1; i += a) {
			if ((i + a) < matrix.size()) {
				tmp.push_back(creationOfBlock(matrix, std::make_pair(a * amountOfBlocks, i), std::make_pair(matrix.size() - 1, i + a - 1)));
			}
		}
		tmp.push_back(creationOfBlock(matrix, std::make_pair(a * amountOfBlocks, a * amountOfBlocks), std::make_pair(matrix.size() - 1, matrix.size() - 1)));
		division.push_back(tmp);
	}
	return division;
}

std::vector<std::vector<int>> linkingMatrixOfMatrixes(const std::vector<std::vector<std::vector<std::vector<int>>>> &bigMatrix) {
	std::vector<std::vector<int>> answer;
	int size = 0;
	for (int i = 0; i < bigMatrix.size(); i++) {
		size += bigMatrix[0][i][0].size();
	}
	std::vector<int> nullString;
	for (int i = 0; i < size; i++) {
		nullString.push_back(0);
	}
	for (int i = 0; i < size; i++) {
		answer.push_back(nullString);
	}
	int a = bigMatrix[0][0].size();
	for (int i = 0; i < bigMatrix.size(); i++) {
		for (int j = 0; j < bigMatrix[i].size(); j++) {
			for (int k = 0; k < bigMatrix[i][j].size(); k++) {
				for (int h = 0; h < bigMatrix[i][j][k].size(); h++) {
					answer[i * a + k][j * a + h] = bigMatrix[i][j][k][h];
				}
			}
		}
	}
	return answer;
}

void threadSecondSortFunction(const int i,const int j, const std::vector<std::vector<std::vector<std::vector<int>>>>& A, const std::vector<std::vector<std::vector<std::vector<int>>>>& B, std::vector<std::vector<std::vector<std::vector<int>>>>& C) {
	std::vector<std::vector<std::vector<int>>> tmp;
	for (int k = 0; k < A.size(); k++) {
		tmp.push_back(multiplyMatrixes(A[i][k], B[k][j]));
	}
	C[i][j] = sumOfMatrixes(tmp);
}

void threadFirstSortFunction(const int a, const std::vector<std::vector<int>>& firstMatrix, const std::vector<std::vector<int>>& secondMatrix, std::vector<std::vector<int>>& ans) {
	std::vector<std::vector<std::vector<std::vector<int>>>> A = divisionIntoBlocks(a, firstMatrix);
	std::vector<std::vector<std::vector<std::vector<int>>>> B = divisionIntoBlocks(a, secondMatrix);
	std::vector<std::vector<std::vector<std::vector<int>>>> C = A;
	int amountOfthreads = 1;
			std::vector<std::thread> threads;
			for (int i = 0; i < A[0].size(); i++) {
				for (int j = 0; j < B.size(); j++) {
					std::vector<std::vector<std::vector<int>>> tmp;
					for (int k = 0; k < A.size(); k++) {
						tmp.push_back(multiplyMatrixes(A[i][k], B[k][j]));
					}
					C[j][i] = sumOfMatrixes(tmp);
				}
			}
			for (int i = 0; i < threads.size(); i++) {
				threads[i].join();
			}
	ans = linkingMatrixOfMatrixes(C);

	std::cout << amountOfthreads << "\n";
}


int main()
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> tmp;
	for (int i = 0; i < 5; i++) {
		tmp.push_back(0);
	}
	for (int i = 0; i < 5; i++) {
		matrix.push_back(tmp);
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i][i] = 1;
	}
	std::vector<std::vector<int>> answer = matrix;
	std::vector<std::thread> threads;
	threadFirstSortFunction(2, std::ref(matrix), std::ref(matrix), std::ref(answer));
	return 0;
}