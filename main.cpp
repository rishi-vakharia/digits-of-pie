// IMT2020018 - Rachit Agarwal
// IMT2020067 - Rishi Vakharia

#include "conversions.hpp"
#include "operations.hpp"

using namespace std;

pair<vector<int>,int> squareroot(vector<int> R, int p1, int m, int p){
    
    pair<vector<int>,int> x0, x1, x2;

    x2.first = stringToBaseM("2", m);
    reverse(x2.first.begin(), x2.first.end());
    x2.second=0;

    x0.first = stringToBaseM("1", m);
    reverse(x0.first.begin(), x0.first.end());
    x0.second=0;

    for(int i=0; i<4*log(p)+3; i++){

        x1 = division(R, p1, x0.first, x0.second, m, p);        
        x1 = addition(x1.first, x1.second, x0.first, x0.second, m);
        x1 = division(x1.first, x1.second, x2.first, x2.second, m, p);
        x0 = x1;
    }

    return x1;
}


pair<vector<int>, int> borwein(int prec, int m){

    //1
    pair<vector<int>, int> num1;
    num1.first = stringToBaseM("1", m);
    reverse(num1.first.begin(), num1.first.end());
    num1.second=0;

    //2
    pair<vector<int>, int> num2;
    num2.first = stringToBaseM("2", m);
    reverse(num2.first.begin(), num2.first.end());
    num2.second=0;


    //a0 = root(2)
    pair<vector<int>, int> a0;
    a0= squareroot(num2.first, num2.second, m, prec);
    
    //b0 = 0
    pair<vector<int>, int> b0;
    b0.first.push_back(0);
    b0.second=0;
    
    //p0 = 2 + root(2)
    pair<vector<int>, int> p0;
    p0=addition(num2.first, num2.second, a0.first, a0.second, m);


    pair<vector<int>, int> a1, b1, p1;
    for(int i=0; i<4*log(prec)+3; i++){

        //root(an)
        pair<vector<int>, int> numRootAn= squareroot(a0.first, a0.second, m, prec);
        //an + bn
        pair<vector<int>, int> numAnPlusBn= addition(a0.first, a0.second, b0.first, b0.second, m);


        //1 / root(an)
        a1=division(num1.first, num1.second, numRootAn.first, numRootAn.second, m, prec);      
        //root(an) + (1 / root(an))
        a1=addition(numRootAn.first, numRootAn.second, a1.first, a1.second, m);
        //(root(an) + (1 / root(an))) / 2
        a1=division(a1.first, a1.second, num2.first, num2.second, m, prec);
        

        //1 + bn
        b1=addition(num1.first, num1.second, b0.first, b0.second, m);
        //(1 + bn) * root(an)
        b1=karatsuba(b1.first, b1.second, numRootAn.first, numRootAn.second, m);
        //((1 + bn) * root(an)) / (an + bn)
        b1=division(b1.first, b1.second, numAnPlusBn.first, numAnPlusBn.second, m, prec);
        //1 + b(n+1)
        pair<vector<int>, int> num1PlusBnPlus1=addition(num1.first, num1.second, b1.first, b1.second, m);
        

        //1 + a(n+1)
        p1 = addition(num1.first, num1.second, a1.first, a1.second, m);
        //(1 + a(n+1)) * pn
        p1 = karatsuba(p1.first, p1.second, p0.first, p0.second, m);
        //((1 + a(n+1)) * pn) * b(n+1)
        p1 = karatsuba(p1.first, p1.second, b1.first, b1.second, m);
        //(((1 + a(n+1)) * pn) * b(n+1)) / (1 + b(n+1))
        p1= division(p1.first, p1.second, num1PlusBnPlus1.first, num1PlusBnPlus1.second, m, prec);

        a0=a1;
        b0=b1;
        p0=p1;
    }

    return p1;
}

int main(){
    int choice, precision, m;

    cout<<"Enter 1 to see precision of PIE"<<endl;
    cout<<"Enter 2 to see precision of ROOT 2"<<endl;
    cout<<"Your Choice: ";
    cin>>choice;

    cout<<"Till What Precision: ";
    cin>>precision;

    m=8;

    pair<vector<int>, int> p;
    string ans;

    if(choice == 1){
        p = borwein(precision, m);
        reverse(p.first.begin(),p.first.end());
        ans = BaseMtoString(p.first, p.second, m, precision);
        cout << endl << ans << endl;
    }
    else{
        vector<int> v = stringToBaseM("2",m);
        reverse(v.begin(), v.end()); 
        p = squareroot(v, 0, m, precision);
        reverse(p.first.begin(), p.first.end());
        ans = BaseMtoString(p.first, p.second, m, precision);
        cout << endl << ans << endl;
    }
}