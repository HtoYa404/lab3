#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include<ios>
#include<limits>
#include <fstream>
using namespace std;
extern bool isTesting;

long int f_one(int x, int n){
    if(n <= -6 || x >= -5){ throw "invalid input data";}
    long long y = 0;
    for(int i = -6; i<=n; ++i){
        y += i + x;
    }
    return 4*x*y -9;
}
double f_two(double x, int n){
    if(n<=3){ throw "invalid input data";}
    double y = 0;
    double z = 1;
    for(int i = 1; i <= n+1; ++i){
        for(int j = 0; j<=n-3; ++j){
            z *= (i-2*j)/(4+x*x);
        }
        y += z;
        z = 1;
    }
    return y;
}

double monkeyInput(const string& q = "") {
    double res = 0.0;
    string input;
    while (true) {
        if (!q.empty()) {
            cout << q;
        }
        for (char& c : input) {
            if (c == ',') c = '.';
        }
        try {
            res = stod(input);
            break;
        } catch (const invalid_argument&) {
            if (!isTesting) cout << "Invalid input, try again.\n";
        }
        if (isTesting) break;
    }
    return res;
}

bool ask(string question){
    char answ;
    ask:
    if(!isTesting) cout << question << " y/n: ";
    cin >> answ;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(answ){
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            if(isTesting) throw "invalid user input";
            cout << "enter y/n\n";
            goto ask;
    }
}

void out(double x, double n, bool first){
    static bool answ = false;
    double y;
    ofstream res;
    if(x < -5){
        y = f_one(x, n);
    }else if(x >= -5){
        y = f_two(x, n);

    }
    if(first){
        answ = ask("would you like to also save the result to the file?");
    }
    if(answ){
        try{
            res.open("results.txt", ios::app);
            res << y << endl;
            res.close();
        }catch(...){
            throw "incorrect input file";
        }
    }
    cout << "in: x: " << x << " n: " << n << "| out: " << y << endl;
}
#endif