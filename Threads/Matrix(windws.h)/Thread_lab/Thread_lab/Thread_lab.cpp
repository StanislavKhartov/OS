#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "BufferedChannel.h"
#include <list>

#include <Windows.h>

void multiplyBlocks(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, int n, int blockSize,
    int upperLeftI, int upperLeftJ) {
    for (int i = upperLeftI; i < min(upperLeftI + blockSize, n); i++) {
        for (int j = upperLeftJ; j < min(upperLeftJ + blockSize, n); j++) {
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

std::vector<int> multiplyMatrixSequentially(const std::vector<int>& A, const std::vector<int>& B, int blockSize) {
    int matrixSize = (int)std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            multiplyBlocks(A, B, C, matrixSize, blockSize, i, j);
        }
    }
    return C;
}

std::vector<int> multiplyMatrixWithThread(const std::vector<int>& A, const std::vector<int>& B, int blockSize, int threadsCapacity) {
    int matrixSize = (int)std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);
    std::list<std::thread> threads;
    BufferedChannel<std::pair<int, int>> buffer(A.size() + 1);
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            buffer.Send(std::pair<int, int>(i, j));
        }
    }
    buffer.Close();
    int amountOfDataInChanel = 0;
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {

            if (amountOfDataInChanel < threadsCapacity) {
                std::pair<std::pair<int, int>, bool> tmpPair = buffer.Recv();
                threads.emplace_back(multiplyBlocks, std::cref(A), std::cref(B), std::ref(C), matrixSize, blockSize, std::cref(tmpPair.first.first), std::cref(tmpPair.first.second));
            }
            else {
                threads.front().join();
                threads.pop_front();
                std::pair<std::pair<int, int>, bool> tmpPair = buffer.Recv();
                threads.emplace_back(multiplyBlocks, std::cref(A), std::cref(B), std::ref(C), matrixSize, blockSize, std::cref(tmpPair.first.first), std::cref(tmpPair.first.second));
            }
        }
    }
    for (int i = 0; i < threads.size(); i++) {
        threads.front().join();
        threads.pop_front();
    }
    return C;
}

int main(){
    int matrixSize = 100;
    std::vector<int> matrix;
    for (int i = 0; i < matrixSize * matrixSize; i++) {
        matrix.push_back(0);
    }
    for (int i = 0; i < matrixSize; i++) {
        matrix[i + matrixSize]++;
    }
    int chanelCapacity = 10;
    for (int i = 0; i < matrixSize; i++) {
        auto start = std::chrono::system_clock::now();
        multiplyMatrixWithThread(matrix, matrix, i, chanelCapacity);
        auto end = std::chrono::system_clock::now();
        std::cout << i << " block size, " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " time \n";
    }
    return 0;
}
