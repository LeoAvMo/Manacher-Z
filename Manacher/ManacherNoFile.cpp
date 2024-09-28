#include <iostream>
#include <string>
#include <vector>
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

int main() {
    string input;
    cout << "Enter the string: ";
    cin >> input;

    string result = longestPalindromicSubstring(input);

    cout << "The longest palindromic substring is: " << result << endl;

    return 0;
}