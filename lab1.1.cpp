#include <iostream>
#include <fstream>
using namespace std;
long int f_one(int x, int n){
    long long y = 0;
    for(int i = -6; i<=n; ++i){
        y += i + x;
    }
    return 4*x*y -9;
}
double f_two(double x, int n){
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
/*
bool monkeyCheck(){
    return true;
}
*/
bool ask(string question){
    char answ;
    ask:
    cout << question << " y/n\n";
    cin >> answ;
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
void out(double y, bool first){ 
    static bool answ = false;
    ofstream res;
    if(first){
        answ = ask("would you like to save the result to the file?");
    }
    if(answ){
        res.open("results.txt", ios::app);
        res << y << endl;
        res.close();
    }
    cout << y << endl;
}
int main(){
    int x, n;
    int b, step, a = 1;
    bool is_first;
    string file;
    ifstream finp;
    start:
    is_first = true;
    cout << "write the name of input file/numbers x and n/ the word \"range\" followed by n, a, b and step \n";
    cin.ignore(4, '\n' );
    cin >> x >> n;
    if (cin.fail()){
        cin.clear(); 
        cin >> file;
        if(file == "range"){
            cin.ignore(5, '\n' );
            cin >> n >> a >> b >> step;
            goto cycle;
        }else if(file == "help"){
            cout << "help the monkey";
        }
        finp.open(file, ios::in);
        if(finp.fail()){
            cout << "file does not exist try one more time\n";
            goto start;
        }
    }
    cycle:
    while(true){
        if(finp.is_open()){
            finp >> x >> n;
        }else if(file == "range" && a <= b){
            x = a;
            a += step;
        }
        if ((n > 3 || (n > -6 && x < -5))&& !cin.fail()){
            if(x < -5){
                out(f_one(x, n), is_first);
            }else if(x >= -5){
                out(f_two(x, n), is_first);
            }
            is_first = false;
        }else{
            cout << "false input data try one more time\n";
            goto start;
        }
        if (!finp.is_open() && a > b){
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
}