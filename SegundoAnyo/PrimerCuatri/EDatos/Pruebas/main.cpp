#include <iostream>
#include <vector>
using namespace std;

int main() {
    int ***v = new int**[3];
    v[1]=new int*[4];
    v[1][2]=new int(8);

    delete v[1][2];
    delete[] v[1];
    delete[] v;

    //ejer 2

    int **p;
    p=new int*[4];
    for(int i=0;i<4;i++){
        p[i]=new int(i+1);
    }

    //ejer 3
    int **p = new int*[3];
    p[2]=new int;
    //*(*p)[2]=7; <==> *p[2]=7;

    vector<int*> p(3,nullptr);
    p[2]=new int;
    *p[2]=7;

    //ejer 4
    char v4[4]={'a','b','c','d'};
    char **nuevo=new char*[4];
    for(int i=0;i<4;i++){
        nuevo[i]=&v4[i];
    }
}