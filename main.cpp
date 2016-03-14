#include <iostream>
#include <stdio.h>


using namespace std;

//inputs

#define name "D:/projects/qt_git/chess/desks.txt"

#define w 8
#define h 8

char desk[w][h];
bool endFlag=true;
void readBoard()
{
    static FILE *task = fopen(name,"r");
    char tmp;

    endFlag=true;
    for (int i=0;i<h;++i)
    {
        for (int j=0;j<w;++j)
        {
            fscanf(task,"%c",&tmp);


            if (tmp!='.') endFlag=false;
            desk[j][i]=tmp;
            printf("%c  ",desk[j][i]);
        }
        fscanf(task,"%c",&tmp);
        printf("\n\n");
    }
    fscanf(task,"%c",&tmp);
    printf("%c",tmp);


}

int main()
{
    cout << "Hello World!" << endl;
do {
    readBoard();
   } while(!endFlag);
    return 0;
}
