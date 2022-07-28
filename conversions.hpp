#ifndef CONVERSIONS
#define CONVERSIONS

#include "operations.hpp"

using namespace std;

pair<vector<int>,vector<int>> divide(vector<int> a, vector<int> b, int m);
bool checkZero(vector<int> v);
int checkOdd(string s);
string divideByTwo(string s);
vector<int> decimalToBinary(string s);
vector<int> binaryToBaseM(vector<int> v, int m);
vector<int> stringToBaseM(string s, int m);
string IntegerBaseMtoString(vector<int> v, int m);
string BaseMtoString(vector<int> v, int p1, int m, int precision);

#endif