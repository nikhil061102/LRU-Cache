#include <iostream>
#include <string>
using namespace std;

string url_generator(int size){
    string url;
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < size; i++){
        url += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return url;
}

int main(){
    cout<<"Enter Length of cache: ";
    int n;
    cin>>n;
    cout<<"Enter No. of websites: ";
    int t;
    cin>>t;
    freopen("input.txt", "w", stdout);
    cout << n;
    cout << endl;
    while (t){
        int x = rand();
        x = x % 80;
        string url = url_generator(x);
        cout << "https://" << url;
        cout << endl;
        t--;
    }
    cout << "-1";
    return 0;
}