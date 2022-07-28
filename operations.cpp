#include "operations.hpp"

using namespace std;

void removeLeadingZeroes(vector<int> &a, int p){
    
    int range = a.size()-p-1;
    int i=0;
    while(a.at(0)==0 && i<range){
        a.erase(a.begin());
        i++;
    }
}

pair<vector<int>,int> addition(vector<int> &a, int p1, vector<int> &b, int p2, int m){

    int og_len_a = a.size();
    int og_len_b = b.size();


    reverse(a.begin(), a.end());       
    reverse(b.begin(), b.end());        

    if(p1 < p2){
        for(int i = 0; i < p2-p1; i++){
            a.insert(a.begin(), 0);
        }
    }
    else{
        for(int i = 0; i < p1-p2; i++){
            b.insert(b.begin(), 0);
        }
    }

    //assuming that len(a)>=len(b)
    if(og_len_a<og_len_b){              
        a.swap(b);
    }

    vector<int> c;
    int carry = 0;
    
    for(unsigned int i = 0; i < b.size(); i++){
        int temp = a[i] + b[i] + carry;
        carry = temp >> m;
        c.insert(i + c.begin(), temp%(1 << m));
    }
    for(unsigned int i = b.size(); i < a.size(); i++){
        int temp = a[i] + carry;
        carry = temp >> m;
        c.insert(i + c.begin(), temp%(1 << m));
    }
    c.insert(a.size() + c.begin(), carry);

    reverse(c.begin(), c.end());        
    removeLeadingZeroes(c, max(p1, p2));  

    if(og_len_a<og_len_b){              
        a.swap(b);
    }   

    if(p1 < p2){
        for(int i = 0; i < p2-p1; i++){
            a.erase(a.begin());
        }
    }
    else{
        for(int i = 0; i < p1-p2; i++){
            b.erase(b.begin());
        }
    }

    reverse(a.begin(), a.end());       
    reverse(b.begin(), b.end());

    return {c, max(p1, p2)};
}

pair<vector<int>,int> subtraction(vector<int> &a, int p1, vector<int> &b, int p2, int m){
    
    reverse(a.begin(), a.end());        
    reverse(b.begin(), b.end());        
    
    int B = (1 << m);

    if(p1 < p2){
        for(int i = 0; i < p2-p1; i++){
            a.insert(a.begin(), 0);
        }
    }
    else{
        for(int i = 0; i < p1-p2; i++){
            b.insert(b.begin(), 0);
        }
    }

    vector<int> c;
    int carry = 0;
    
    for(unsigned int i = 0; i < b.size(); i++){
        int temp = a[i] - b[i] + carry;
        if(temp < 0) carry = -1;
        else carry = 0;
        c.insert(i + c.begin(), (temp+(B))%(B));
    }
    for(unsigned int i = b.size(); i < a.size(); i++){
        int temp = a[i] + carry;
        if(temp < 0) carry = -1;
        else carry = 0;
        c.insert(i + c.begin(), (temp+(B))%(B));
    }
    c.insert(a.size() + c.begin(), carry);

    reverse(c.begin(), c.end());       
    removeLeadingZeroes(c, max(p1, p2));      

    if(p1 < p2){
        for(int i = 0; i < p2-p1; i++){
            a.erase(a.begin());
        }
    }
    else{
        for(int i = 0; i < p1-p2; i++){
            b.erase(b.begin());
        }
    }

    reverse(a.begin(), a.end());        
    reverse(b.begin(), b.end());   

    return {c,max(p1, p2)};
}

pair<vector<int>,int> multiplication(vector<int> &a, int p1, vector<int> &b, int p2, int m){

    vector<int> c;

    if(a.size()==0 || b.size()==0){
        c.push_back(0);
        return {c,0};
    }

    int k, l, carry;
    k=a.size();
    l=b.size();

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for(int i=0; i<=k+l-1; i++)
        c.push_back(0);

    for(int i=0; i<=k-1; i++){
        carry=0;
        for(int j=0; j<=l-1; j++){
            int tmp = a.at(i)*b.at(j) + c.at(i+j) + carry;
            carry = tmp>>m;
            c.at(i+j)= tmp%(1<<m);
        }
        c.at(i+l)=carry;
    }

    reverse(c.begin(), c.end());
    removeLeadingZeroes(c, p1+p2);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    return {c, p1+p2};
}

pair<vector<int>,int> karatsuba(vector<int> &a, int p1, vector<int> &b, int p2, int m){

    vector<int> c;

    if(a.size()==0 || b.size()==0){
        c.push_back(0);
        return {c,0};
    }

    //making numbers equal length
    int og_len_a = a.size();
    int og_len_b = b.size();
    int length = max(og_len_a, og_len_b);


    int diff = og_len_a-og_len_b; 
    if(diff<0){
        diff=-1*diff;
        a.insert(a.begin(), diff, 0);
    }
    else if(diff>0)
        b.insert(b.begin(), diff, 0);


    //base case
    if(length==1){
        int res = a.at(0)*b.at(0);
        int B = (1 << m);
        if(res >= B) {
            c.push_back(res>>m);
            c.push_back(res%B);
        } 
        else {
            c.push_back(res);
        }

        diff = og_len_a-og_len_b; 
        if(diff<0){
            diff=-1*diff;
            a.erase(a.begin(), a.begin()+diff);
        }
        else if(diff>0)
            b.erase(b.begin(), b.begin()+diff);


        return {c, 0};
    }

    //splitting the numbers
    vector<int> a0, a1, b0, b1;
    int mid=length/2;

    for(int i=0; i<mid; i++){
        a1.push_back(a.at(i));
        b1.push_back(b.at(i));
    }
    for(unsigned int i=mid; i<a.size(); i++){
        a0.push_back(a.at(i));
        b0.push_back(b.at(i));
    }

    //karatsuba
    vector<int> c0, c1, c2;

    c0=karatsuba(a0, 0, b0, 0, m).first;
    c2=karatsuba(a1, 0, b1, 0, m).first;

    vector<int> t1, t2, t3;

    t1=addition(a0, 0, a1, 0, m).first;
    t2=addition(b0, 0, b1, 0, m).first;
    t3=karatsuba(t1, 0, t2, 0, m).first;

    c1=subtraction(t3, 0, c0, 0, m).first;
    c1=subtraction(c1, 0, c2, 0, m).first;


    for(int i=0; i<2*(length-mid); i++)
        c2.push_back(0);
    for(int i=0; i<length-mid; i++)
        c1.push_back(0);
      
    c=addition(c2, 0, c1, 0, m).first;
    c=addition(c, 0, c0, 0, m).first;

    removeLeadingZeroes(c, p1+p2);


    diff = og_len_a-og_len_b; 
    if(diff<0){
        diff=-1*diff;
        a.erase(a.begin(), a.begin()+diff);
    }
    else if(diff>0)
        b.erase(b.begin(), b.begin()+diff);


    return {c, p1+p2};
}

pair<vector<int>,int> division(vector<int> &a, int p1, vector<int> &b, int p2, int m, int p){ 

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    if(p1 > p2){
        for(int i = 0; i < p-p1+p2; i++){
            a.insert(a.begin(),0);
        }
    }
    else{
        for(int i = 0; i < p+p2-p1; i++){
            a.insert(a.begin(),0);
        }
    }

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

    if(p1 > p2){
        for(int i = 0; i < p1-p2-p; i++){
            q.erase(q.begin());
        }
    }

    reverse(q.begin(), q.end());
    removeLeadingZeroes(q, p);

    if(p1 > p2){
        for(int i = 0; i < p-p1+p2; i++){
            a.erase(a.begin());
        }
    }
    else{
        for(int i = 0; i < p+p2-p1; i++){
            a.erase(a.begin());
        }
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    return {q,p};
}