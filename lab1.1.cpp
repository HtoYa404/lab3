#include <iostream>
#include<ios>
#include<limits>
#include <fstream>
#include "header.hpp"
using namespace std;
long int f_one(int x, int n){
    if(n <= -6 || x >= -5) throw "invalid input data";
    long long y = 0;
    for(int i = -6; i<=n; ++i){
        y += i + x;
    }
    return 4*x*y -9;
}
double f_two(double x, int n){
    if(n<=3) throw "invalid input data";
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

double monkeyInput(string q){
    double res;
    string input;
    while (true) {
        cout << q;
        cin >> input;
        for (char &c : input) {
            if (c == ',') {
                c = '.';
            }
        }
        try {
            res = stod(input); 
            break;  
        } catch (const invalid_argument &) {
            cout << "Please enter a valid number.\n";
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    return res;
}

bool ask(string question){
    char answ;
    ask:
    cout << question << " y/n: ";
    cin >> answ;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(answ){
        case 'y':
            return true;
        case 'n':
            return false;
        default:
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

int main(){
    try{
    int n, mode;
    double x, b, step, a;
    bool is_first;
    string file;
    ifstream finp;
    start:
    is_first = true;
    cout << "Please select mode of input\n"
    "1 for input of a file \n"
    "2 for input of values x and n \n"
    "3 for calculation of values in the given range \n"
    "note, that all extra input after numbers will be ignored\n";
    mode = monkeyInput("Choose your option: ");
    redo:
    switch(mode){
        case 1:
            getFileName:
            cout << "write file name for input: ";
            cin >> file;
            finp.open(file, ios::in);
            if(finp.fail()){
                finp.clear();
                cout << "file does not exist try one more time\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto getFileName;
            }
            break;
        case 2:
            x = monkeyInput("Please enter the number for x: ");
            while(true){
                n = (int)monkeyInput("Please enter the number for n(it will bw automaticly converted to integer): ");
                if((n > 3 || (n > -6 && x < -5))){
                    break;
                }else{ 
                    cout << "false input data\n"
                    "n must be either greater than 3, or greater than -6(if x is less than 5\n"
                    "try one more time\n";
                }
            }
            break;
        case 3:
            n = (int)monkeyInput("Please enter the number for n(the number will be converted to an integet): ");
            while(true){
                a = monkeyInput("Please enter the number where the will cycle start: ");
                b = monkeyInput("Please enter the number where the will cycle end: ");
                if(a >= b){
                cout << "end of the range must be greater than it`s start\n";
                }else{
                    break;
                }
            }
            while(true){
                step = monkeyInput("Please enter the number for step of the cycle: ");
                if(step > 0){
                    break;
                }else{
                    cout << "step must be greater than 0\n";
                }
            }
            a -= step;
            break;
        default:
            cout << "please enter value from 1 to 3\n";
            mode = monkeyInput("Choose your option: ");
            goto redo;
    }
    while(true){
        if(mode == 1){
            finp >> x >> n;
        }else if(mode == 3 && a <= b){
            x = a;
            a += step;
        }
        if ((n > 3 || (n > -6 && x < -5)) && !cin.fail()){
            out(x, n, is_first);
            is_first = false;
        }else{
            cout << "false input data\n"
            "n must be either greater than 3, or greater than -6(if x is less than 5)\n"
            "try one more time\n";
            goto redo;
        }
        if (mode == 2 || (a > b && mode == 3)){
            if(ask("do you want to end the program?")){
                return 0;
            }
            goto start;
        }else if(finp.peek() == EOF && finp.is_open()){
            finp.close();
            if(ask("do you want to end the program?")){
                return 0;
            }
            goto start;
        }
    }
    }catch(...){
        cout << "an unknown error has ocurred";
    }
}
