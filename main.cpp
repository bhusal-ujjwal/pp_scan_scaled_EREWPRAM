#include <iostream>
#include <vector>
#include <../omp.h>

void prefixScan(std::vector<int>& input, int numThreads) {
    int numElements = input.size();

    // Perform the scaled EREW PRAM prefix scan algorithm
    #pragma omp parallel num_threads(numThreads)
    {
        for (int p = 1; p < numElements / 2; p *= 2) {
            #pragma omp for schedule(static, numElements / (2 * p))
            for (int i = p; i < numElements; i++) {
                input[i] += input[i - p];
            }
            #pragma omp barrier
        }
    }
}

int main() {
    int N; // Number of elements
    int numThreads; // Number of threads

    // Read input from the user
    std::cout << "Enter the number of elements: ";
    std::cin >> N;

    std::cout << "Enter the number of threads: ";
    std::cin >> numThreads;

    // Set the number of threads for OpenMP
    omp_set_num_threads(numThreads);

    // Generate the input array
    std::vector<int> input(N);
    for (int i = 0; i < N; i++) {
        input[i] = i + 1;
    }

    // Perform the prefix scan
    prefixScan(input, numThreads);

    // Print the result
    std::cout << "Prefix scan result:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
