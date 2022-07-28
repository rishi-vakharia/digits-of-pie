#include "conversions.hpp"

using namespace std;

pair<vector<int>,vector<int>> divide(vector<int> a, vector<int> b, int m){
    vector<int> q,r;
    int k = a.size(), l = b.size(), B = (1 << m);

    for(int i = k-l; i >= 0; i--){
       q.push_back(0);
    }
    for(int i = 0; i < k; i++){
        r.push_back(a[i]);
    }
    r.push_back(0);
    for(int i = k-l; i >= 0; i--){
        q[i] = floor(((r[i+l] << m) + r[i+l-1])/b[l-1]);
        if(q[i] >= B) q[i] = B-1;
        int carry = 0;
        for(int j = 0; j < l; j++){
            int temp = r[i+j] - q[i]*b[j] + carry;
            carry = temp >> m;
            r[i+j] = (temp+B*B-B) % B;
        }
        r[i+l] = r[i+l] + carry;
        while (r[i+l] < 0){
            int carry = 0;
            for(int j = 0; j < l; j++){
                int temp = r[i+j] + b[j] + carry;
                carry = temp >> m;
                r[i+j] = (temp+B*B-B) % B;
            }
            r[i+l] = r[i+l] + carry;
            q[i] = q[i] - 1;
        }
    }

    return {q,r};
}

bool checkZero(vector<int> v){
    for(auto i : v){
        if (i != 0) return(false);
    }
    return true;
}

int checkOdd(string s){
    if (s[s.length() - 1] == '1' || s[s.length() - 1] == '3' || s[s.length() - 1] == '5' || s[s.length() - 1] == '7' || s[s.length() - 1] == '9') return 1;
    else return 0;
}

string divideByTwo(string s){
    string ans = "";
    int carry = 0;

    for (unsigned int i = 0; i < s.length(); i++){
        int digit = (s[i] - '0')/2 + carry;
        ans.push_back(char(digit+'0'));
        if (s[i] == '1' || s[i] == '3' || s[i] == '5' || s[i] == '7' || s[i] == '9') carry = 5;
        else carry = 0;
    }

    if (ans != "0" && ans[0] == '0'){
        ans = ans.substr(1);
    }    

    return ans;
}

vector<int> decimalToBinary(string s){
    vector<int> ans;

    if (s == "0") ans.push_back(0); 
    else{
        while (s != "0"){
            ans.push_back(checkOdd(s));
            s = divideByTwo(s);
        }
    }

    return ans;
}

vector<int> binaryToBaseM(vector<int> v, int m){
    if(m == 1) return v;

    vector<int> ans;
    int temp = 0;

    for(unsigned int i = 0; i < v.size(); i++){
        int pos = i%m;
        if(pos == 0){
            temp = v[i];
        }
        else{
            temp += (v[i] << pos);    
            if(pos == m-1){
                ans.push_back(temp);
                temp = 0;
            }
        }
    }

    if(temp != 0){
        ans.push_back(temp);
    }

    return ans;
}

vector<int> stringToBaseM(string s, int m){
    vector<int> ans;
    ans = decimalToBinary(s);
    ans = binaryToBaseM(ans, m);
    return ans;
}

string IntegerBaseMtoString(vector<int> v, int m){
    
    if(checkZero(v)) return "0";

    string ans = "";
    vector<int> ten = stringToBaseM("10", m);

    while(!checkZero(v)){
        pair<vector<int>,vector<int>> p;
        p = divide(v, ten, m);
        v = p.first;
        int temp = 0;
        for(unsigned int i = 0; i < p.second.size(); i++){
            temp += p.second[i] << m*i;
        }
        ans.insert(ans.begin(),1,temp+'0');
    }

    return ans;
}

string BaseMtoString(vector<int> v, int p1, int m, int precision){
    string ans;
    vector<int> ten = stringToBaseM("10", m);
    vector<int> fractional_part;

    for(int i = 0; i < p1; i++){
        fractional_part.push_back(v[0]);
        v.erase(v.begin());
    }

    fractional_part.push_back(0);

    ans = IntegerBaseMtoString(v, m);
    ans += ".";

    reverse(fractional_part.begin(), fractional_part.end());
    reverse(ten.begin(), ten.end());
    
    while(precision > 0){
        pair<vector<int>,int> p;
        p = multiplication(fractional_part, p1, ten, 0, m);
        v = p.first;
        vector<int> integer_part;

        fractional_part.clear();
        fractional_part.push_back(0);

        for(unsigned int i = 0; i < p.first.size(); i++){
            if(i < p.first.size() - p.second){
                integer_part.push_back(p.first[i]);
            }   
            else{
                fractional_part.push_back(p.first[i]);
            }
        }

        p1 = p.second;

        reverse(integer_part.begin(), integer_part.end());
        ans += IntegerBaseMtoString(integer_part, m);

        precision--;
    }

    while(precision > 0){
        ans += "0";
        precision--;
    }

    return ans;
}