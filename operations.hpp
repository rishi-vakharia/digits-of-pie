#ifndef OPERATIONS
#define OPERATIONS

#include <bits/stdc++.h>

using namespace std;

void removeLeadingZeroes(vector<int> &a, int p);
pair<vector<int>,int> addition(vector<int> &a, int p1, vector<int> &b, int p2, int m);
pair<vector<int>,int> subtraction(vector<int> &a, int p1, vector<int> &b, int p2, int m);
pair<vector<int>,int> multiplication(vector<int> &a, int p1, vector<int> &b, int p2, int m);
pair<vector<int>,int> karatsuba(vector<int> &a, int p1, vector<int> &b, int p2, int m);
pair<vector<int>,int> division(vector<int> &a, int p1, vector<int> &b, int p2, int m, int p);

#endif