#include <iostream>
#include <stdio.h>


using namespace std;

//inputs

#define filename "d:/projects/clion/chess/desks.txt" //path of data file

#define w 8 //width of board
#define h 8 //height of board

char desk[w][h];
bool endFlag;
struct king
{
    int x=-1;
    int y=-1;
    char color='0';
};

king black;
king white;


void readBoard()
{
    static FILE *task = fopen(filename,"r");

    char tmp;

    endFlag=true;

    for (int i=0;i<h;++i)
    {
        for (int j=0;j<w;++j)
        {
            fscanf(task,"%c",&tmp);


            if (tmp!='.') endFlag=false;
            desk[j][i]=tmp;
        }
        fscanf(task,"%c",&tmp);
    }
    fscanf(task,"%c",&tmp);

}


void findTheKing()
{
    for (int i=0;i<h;++i)
    {
        for (int j=0;j<w;++j)
        {
            if (desk[j][i]=='K')
            {
                white.x=j;
                white.y=i;
                white.color='w';
            };
            if (desk[j][i]=='k')
            {
                black.x=j;
                black.y=i;
                black.color='b';
            };

        }

    }
}

int analyze(king k)
{
    int flag=0;

    char    queen='q'
            ,rook='r'
            ,bishop='b'
            ,horse='n'
            ,pawn='p';

    if (k.color=='b')
    {
        queen='Q';
        rook='R';
        bishop='B';
        horse='N';
        pawn='P';
    };

    //---horse---
    int pos[8][2]={ {-2,1}
                    ,{-2,-1}
                    ,{2,1}
                    ,{2,-1}
                    ,{-1,2}
                    ,{-1,-2}
                    ,{1,2}
                    ,{1,-2}
                };
    for (int i=0;i<8;++i)
    {
        if(k.x+pos[i][1]>=0 && k.y+pos[i][2]>=0 && k.x+pos[i][1]<w && k.y+pos[i][2]<h)
        {
            if (desk[k.x+pos[i][1]][k.y+pos[i][2]]==horse)
            {
                flag=1;
                break;
            }
        }

    };


    //---rook&queen

    for (int i=0;i<8;++i)
    {
        if (desk[k.x][i]==rook)
        {
            flag=1;
            break;
        }
        if (desk[k.x][i]==queen)
        {
            flag=1;
            break;
        }
        if (desk[i][k.y]==rook)
        {
            flag=1;
            break;
        }
        if (desk[i][k.y]==queen)
        {
            flag=1;
            break;
        }
    }

   // ---bishop&queen

   for (int i=-7;i<7;++i)
    {
        if (k.x+i>=0 && k.x+i<8 && k.y+i>=0 && k.y+1<8)
        {
            if(desk[k.x+i][k.y+i]==bishop || desk[k.x+i][k.y+i]==queen)
            {
                flag=1;
                break;
            }
        }
        if (k.x-i>=0 && k.x-i<8 && k.y-i>=0 && k.y-1<8)
        {
            if(desk[k.x-i][k.y-i]==bishop || desk[k.x-i][k.y-i]==queen)
            {
                flag=1;
                break;
            }
        }
    }

   // ---pawn
    int dir = 1,
        b=7;

    if (k.color=='w')
    {
        b=0;
        dir= -1;
    }

    if(k.x+1<8 && k.x-1>=0 && k.y!=b)
    {
        if (desk[k.x + 1][k.y + dir] == pawn || desk[k.x - 1][k.y + dir] == pawn) flag = 1;
    }

    return  flag;

}

int main()
{
    int i=1;

    while (1)
    {
        readBoard();
        if (endFlag) break;
        findTheKing();
        if (white.x<0||white.y<0||black.x<0||black.y<0)
        {
            printf("\nGame #%i: wrong etude!\n",i);
            ++i;
            continue;
        };
        if(analyze(white))
        {
            printf("Game #%i: white king is in check.\n",i);
        }
        else if(analyze(black))
        {
            printf("Game #%i: black king is in check.\n",i);
        }
        else printf("Game #%i: no king is in check.\n",i);

        ++i;
    }

    getchar();
    return 0;
}