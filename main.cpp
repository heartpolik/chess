#include <iostream>
#include <stdio.h>

using namespace std;

//inputs
#define filename "d:/projects/clion/chess/desks.txt" //path of data file
#define w 10 //width of board
#define h 10 //height of board

char desk[w][h]={   {'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}
                    ,{'!','!','!','!','!','!','!','!','!','!'}};
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

    for (int i=1;i<h-1;++i)
    {
        for (int j=1;j<w-1;++j)
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
    for (int i=1;i<h-1;++i)
    {
        for (int j=1;j<w-1;++j)
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
    int pos[8][2]={{-2,1},{-2,-1},{2,1},{2,-1},{-1,2},{-1,-2},{1,2},{1,-2}};

    for (int i=0;i<8;++i)
    {
        if( k.x + pos[ i ][ 1 ] > 0 && k.y + pos[ i ][ 2 ] > 0 && k.x + pos[ i ][ 1 ] < w - 1 && k.y + pos[ i ][ 2 ] < h - 1)
        {
            if (desk[ k.x + pos[ i ][ 1 ] ] [ k.y + pos[ i ][ 2 ] ] == horse)
            {
                flag=1;
            };
        };
        if(flag) break;
    };

//---rook&queen
    int diagonalPattern [4][2]={{-1,-1},{1,-1},{-1,1},{1,1}};

    for (int i=0;i<4;++i)
    {
        int j=1;
        while(1)
        {
            char cell = desk[ k.x + j * diagonalPattern[ i ][ 0 ] ] [ k.y + j * diagonalPattern[ i ][ 1 ] ];
            if (cell == '!')
            {
                break;
            };
            if (cell == '.')
            {
                ++j;
                continue;
            };
            if (cell == queen)
            {
                flag = 1;
                break;
            };
            if (cell == bishop)
            {
                flag = 1;
                break;
            };
            break;
        };
        if (flag) break;
    };

// ---bishop&queen
    int linePattern [4][2]={{-1,0},{0,-1},{0,1},{1,0}};

    for (int i = 0 ; i < 4 ; ++i )
    {
            int j=1;
            while(1)
            {
                char cell = desk[ k.x + j * linePattern[ i ][ 0 ] ] [ k.y + j * linePattern[ i ][ 1 ] ];

                if (cell == '!') {
                    break;
                };
                if (cell == '.') {
                    ++j;
                    continue;
                };
                if (cell == queen) {
                    flag = 1;
                    break;
                };
                if (cell == rook) {
                    flag = 1;
                    break;
                };
                break;
            };
            if (flag) break;
    };

// ---pawn
    int dir = 1,
        b = 8;

    if ( k.color == 'w')
    {
        b = 1;
        dir = -1;
    };

    if( k.x + 1 < 8 && k.x - 1 > 0 && k.y != b)
    {
        if (desk[k.x + 1][k.y + dir] == pawn || desk[k.x - 1][k.y + dir] == pawn) flag = 1;
    };

    return  flag;
}

int main()
{
    int i=1;

    printf("%c",desk[0][5]);
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