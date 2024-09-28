#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to create the Z array
vector<int> ArrayZ(const string &S) {
    int n = S.length();
    vector<int> Z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && S[r] == S[r - l]) {
                ++r;
            }
            Z[i] = r - l;
            --r;
        } else {
            int k = i - l;
            if (Z[k] < r - i + 1) {
                Z[i] = Z[k];
            } else {
                l = i;
                while (r < n && S[r] == S[r - l]) {
                    ++r;
                }
                Z[i] = r - l;
                --r;
            }
        }
    }
    return Z;
}

// Function to perform Z algorithm for pattern matching
void Z_algorithm(const string &T, const string &P) {
    // Concatenate pattern, special character, and text
    string S = P + "$" + T;
    int P_length = P.length();
    vector<int> Z = ArrayZ(S);

    // Check if any Z[i] matches the pattern's length
    for (int i = 0; i < Z.size(); ++i) {
        if (Z[i] == P_length) {
            // Pattern found at index (i - P_length - 1)
            cout << "Pattern found at index: " << (i - P_length - 1) << endl;
        }
    }
}

int main() {
    string T = "ababcababcababc";
    string P = "ababc";

    Z_algorithm(T, P);

    return 0;
}