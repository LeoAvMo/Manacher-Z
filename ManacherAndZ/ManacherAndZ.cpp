#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to find the longest palindromic substring using Manacher's Algorithm
string longestPalindromicSubstring(const string& input) {
    int n = input.length();
    if (n == 0) return "";

    // Preprocess the string to handle both even and odd length palindromes
    string s = "#";
    for (char c : input) {
        s += c;
        s += "#";
    }

    int m = s.length();
    vector<int> P(m, 0);  // Array to store the radius of the palindrome centered at each index
    int C = 0, R = 0;     // C is the center, R is the right boundary of the current longest palindrome

    int maxLen = 0;
    int centerIndex = 0;

    // Manacher's Algorithm to find the longest palindromic substring
    for (int i = 0; i < m; ++i) {
        int mirror = 2 * C - i;  // Calculate the mirrored index of i around center C

        if (i < R) {
            P[i] = min(R - i, P[mirror]);
        }

        // Expand the palindrome around the center i
        while (i + 1 + P[i] < m && i - 1 - P[i] >= 0 && s[i + 1 + P[i]] == s[i - 1 - P[i]]) {
            P[i]++;
        }

        // If palindrome centered at i expands past R, adjust center and right boundary
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }

        // Keep track of the longest palindrome found
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    // Extract the longest palindromic substring
    int start = (centerIndex - maxLen) / 2;  // Convert back to the original string index
    return input.substr(start, maxLen);
}

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
vector<int> Z_algorithm(const string &T, const string &P) {
    // Concatenate pattern, special character, and text
    vector<int> indexes; 
    string S = P + "$" + T;
    int P_length = P.length();
    vector<int> Z = ArrayZ(S);

    // Check if any Z[i] matches the pattern's length
    for (int i = 0; i < Z.size(); ++i) {
        if (Z[i] == P_length) {
            // Pattern found at index (i - P_length - 1)
            indexes.push_back(i - P_length - 1);
        }
    }
    return indexes;
}

int main() {
    // Open the text file
    ifstream file("Bible.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Read the contents of the file into a string
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Remove newlines or carriage returns
    text.erase(remove(text.begin(), text.end(), '\n'), text.end());
    text.erase(remove(text.begin(), text.end(), '\r'), text.end());

    // Find the longest palindromic substring using Manacher's algorithm
    string longestPalindrome = longestPalindromicSubstring(text);
    cout << "Longest Palindromic Substring: " << longestPalindrome << endl;

    // Use the Z algorithm to find the occurrences of the longest palindromic substring in the text
    vector<int> occurrences = Z_algorithm(text, longestPalindrome);

    // Print the indexes where the pattern is found
    cout << "Pattern found at indexes: ";
    for (int index : occurrences) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}