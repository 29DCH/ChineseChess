#include <bits/stdc++.h>
#include "time.h"
#include "cmath"
#include <winsock2.h>
#include <graphics.h>
#include <conio.h>
#include <ctype.h>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#pragma  comment(lib,"WinMM.LIB")//音频头文件
using namespace std;

PIMAGE imgstart;
PIMAGE imgmark;
PIMAGE imgmark1;
PIMAGE imgbk;
PIMAGE imgdescription1;
PIMAGE imgdescription2;
PIMAGE imgdescription3;
PIMAGE imgqp1;
PIMAGE imgqp2;
PIMAGE imgqp3;
PIMAGE imgqp4;
PIMAGE imgqp5;
PIMAGE imgqp6;
PIMAGE imgloading;
PIMAGE imgmusicopen;
PIMAGE imgmusicclose;
PIMAGE imgcheckerboard;
PIMAGE imgcheckerboard1;
PIMAGE imgcheckerboard2;
PIMAGE imgcheckerboard3;
PIMAGE imgranking;
PIMAGE imgredche;
PIMAGE imgredma;
PIMAGE imgredpao;
PIMAGE imgredshi;
PIMAGE imgredxiang;
PIMAGE imgredshuai;
PIMAGE imgredbing;
PIMAGE imgblackche;
PIMAGE imgblackma;
PIMAGE imgblackpao;
PIMAGE imgblackshi;
PIMAGE imgblackxiang;
PIMAGE imgblackjiang;
PIMAGE imgblackzu;
PIMAGE imgfredche;
PIMAGE imgfredma;
PIMAGE imgfredpao;
PIMAGE imgfredshi;
PIMAGE imgfredxiang;
PIMAGE imgfredshuai;
PIMAGE imgfredbing;
PIMAGE imgfblackche;
PIMAGE imgfblackma;
PIMAGE imgfblackpao;
PIMAGE imgfblackshi;
PIMAGE imgfblackxiang;
PIMAGE imgfblackjiang;
PIMAGE imgfblackzu;
PIMAGE imgfbk;

int i;
int j=0;
int row,col;
int posx,posy;
MUSIC mus,mus1; //定义音乐对象
struct fd_set rfds;
struct timeval timeout = {1,0};
SOCKET sockSrv, sockConn;
int ret;
int Bangchess[4][8]= {0};
int cnt = 1;
int tot = 0;
int w=1;
int counter = 1;

typedef struct chess1
{
    int vis;
} Chess1;

typedef struct node//显示排行榜信息的结构体
{
    char name[20];
    char color[10];
    int Wins;
    double winning_percentage;
}Node;

Node game_player[100];

int cmp(Node a,Node b)//结构体排序
{
    return a.name>b.name;
}

int chart[10][9]=
{
    {1,2,3,4,5,6,7,8,9},
    {0,0,0,0,0,0,0,0,0},
    {0,10,0,0,0,0,0,11,0},
    {12,0,13,0,14,0,15,0,16},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {17,0,18,0,19,0,20,0,21},
    {0,22,0,0,0,0,0,23,0},
    {0,0,0,0,0,0,0,0,0},
    {24,25,26,27,28,29,30,31,32}
};//初始的二维数组

//标准二维数组
int chart1[10][9]=
{
    {1,2,3,4,5,6,7,8,9},
    {0,0,0,0,0,0,0,0,0},
    {0,10,0,0,0,0,0,11,0},
    {12,0,13,0,14,0,15,0,16},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {17,0,18,0,19,0,20,0,21},
    {0,22,0,0,0,0,0,23,0},
    {0,0,0,0,0,0,0,0,0},
    {24,25,26,27,28,29,30,31,32}
};

//一些棋子的走棋数组
int redxiang[10][9]=
{
    {0,0,1,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,0,0,1},
    {0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

int blackxiang[10][9]=
{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,0,0,1},
    {0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,0}
};

int redshi[10][9]=
{
    {0,0,0,1,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0},
    {0,0,0,1,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

int blackshi[10][9]=
{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0},
    {0,0,0,1,0,1,0,0,0}
};

int redshuai[10][9]=
{
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

int blackjiang[10][9]=
{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0}
};

int redbing[10][9]=
{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {1,0,1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1}
};

int blackzu[10][9]=
{
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

void itoa(int n,char *s)//itoa函数
{
    int i,j,sign;
    if((sign=n)<0)//记录符号
        n=-n;//使n成为正数
    i=0;
    do
    {
        s[i++]=n%10+'0';//取下一个数字
    }
    while ((n/=10)>0);//删除该数字
    if(sign<0)
        s[i++]='-';
    s[i]='\0';
    for(j=i; j>=0; j--) //生成的数字是逆序的，所以要逆序输出
        printf("%c",s[j]);
}

int atoi(char *s)//atoi函数
{
    int i,n,sign;
    for(i=0; isspace(s[i]); i++) //跳过空白符;
        sign=(s[i]=='-')?-1:1;
    if(s[i]=='+'||s[i]==' -')//跳过符号
        i++;
    for(n=0; isdigit(s[i]); i++)
        n=10*n+(s[i]-'0');//将数字字符转换成整型数字
    return sign *n;
}

void randomBangchess()//随机翻棋数组值
{
    randomize();
    int num;
    int a[40];
    for(int i = 0; i < 32; i++)
        a[i] = 0;
    for(int row=0; row<4; row++)
    {
        for(int col=0; col<8; col++)
        {
            num=random(32)+1;
            while(!a[num])
            {
                Bangchess[row][col]= num;
                a[num] = 1;
            }
        }
    }
}

void go_chess(int x,int y)//走棋
{
    switch(Bangchess[x][y])
    {
    case 1:
    case 2:
        putimage_withalpha(NULL,imgfredche,52.75*x+83,53*y+148);
        break;
    case 3:
    case 4:
        putimage_withalpha(NULL,imgfredma,52.75*x+83,53*y+148);
        break;
    case 5:
    case 6:
        putimage_withalpha(NULL,imgfredxiang,52.75*x+83,53*y+148);
        break;
    case 7:
    case 8:
        putimage_withalpha(NULL,imgfredshi,52.75*x+83,53*y+148);
        break;
    case 9:
        putimage_withalpha(NULL,imgfredshuai,52.75*x+83,53*y+148);
        break;
    case 10:
    case 11:
        putimage_withalpha(NULL,imgfredpao,52.75*x+83,53*y+148);
        break;
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        putimage_withalpha(NULL,imgfredbing,52.75*x+83,53*y+148);
        break;
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        putimage_withalpha(NULL,imgfblackzu,52.75*x+83,53*y+148);
        break;
    case 22:
    case 23:
        putimage_withalpha(NULL,imgfblackpao,52.75*x+83,53*y+148);
        break;
    case 24:
    case 25:
        putimage_withalpha(NULL,imgfblackche,52.75*x+83,53*y+148);
        break;
    case 26:
    case 27:
        putimage_withalpha(NULL,imgfblackma,52.75*x+83,53*y+148);
        break;
    case 28:
    case 29:
        putimage_withalpha(NULL,imgfblackxiang,52.75*x+83,53*y+148);
        break;
    case 30:
    case 31:
        putimage_withalpha(NULL,imgfblackshi,52.75*x+83,53*y+148);
        break;
    case 32:
        putimage_withalpha(NULL,imgfblackjiang,52.75*x+83,53*y+148);
        break;
    }
}

void init_Bangchess()//初始化翻棋数组
{
    for(int row=0; row<4; row++)
    {
        for(int col=0; col<8; col++)
        {
            Sleep(200);
            putimage_withalpha(NULL,imgfbk,52.75*col+83,53*row+148);
        }
    }
}

void init_Bangchess1()
{
    for(int row=0; row<4; row++)
    {
        for(int col=0; col<8; col++)
        {
            putimage_withalpha(NULL,imgfbk,52.75*col+83,53*row+148);
        }
    }
}

void init_chart()//初始化象棋数组
{
    for(int row=0; row<10; row++)
    {
        for(int col=0; col<9; col++)
        {
       chart[row][col]=chart1[row][col];
        }
    }
}

void musicopen()
{
    mus.OpenFile("E:\\CloudMusic\\高山流水.mp3"); // 打开音乐文件
    mus.SetVolume(0.7f); // 设置音量，参数范围从 0.0f 到 1.0f
    if (mus.GetPlayStatus() == MUSIC_MODE_STOP)
    {
        mus.Play(0);
    }

}

void musicopen1()
{
    mus1.OpenFile("E:\\CloudMusic\\吃棋子音效.wav"); //打开音乐文件
    mus1.SetVolume(0.7f); //设置音量，参数范围从 0.0f 到 1.0f
    if(mus1.GetPlayStatus() == MUSIC_MODE_STOP)
    {
        mus1.Play(0);
    }
}

void limit_time()
{
    int time_start = fclock();
    int temp;
    int cnt;
    for(; is_run(); delay_fps(60))
    {
        mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
        temp = fclock();
        if(temp != time_start&&(30-time_start)>0)
        {
            time_start = temp;
            setbkmode(OPAQUE);
            setbkcolor(RGB(0,255,0));
            //xyprintf(120, 160, "%2d:%2d:%2d",time_start/3600,(time_start-time_start/3600*3600)/60,time_start-(time_start-time_start/3600*3600)/60*60);
            xyprintf(140, 210, "%d sec",30-time_start);
        }
        if(!(30-time_start))
        {
            setfont(50,0, "宋体");
            setbkmode(TRANSPARENT);
            setcolor(RED);
            outtextxy(222,149,"时间到,你输了!");
            return ;
        }
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<640&&300<msg.y&&msg.y<320)
        {
            cnt++;
            if(cnt%2)
            {
                putimage_withalpha(NULL,imgmusicopen,80,101);
                musicopen();
            }
            else
            {
                putimage_withalpha(NULL,imgmusicclose,80,101);
                mus.Close();//关闭音乐文件
            }
            system("pause");
        }
    }
}

void init_chess()
{
    for(int row=0; row<10; row++)
    {
        for(int col=0; col<9; col++)
        {
            switch(chart1[row][col])
            {
            case 1:
            case 9:
                Sleep(200);
                putimage_withalpha(NULL,imgredche,34.67*col+230,35.7*row);
                break;
            case 2:
            case 8:
                Sleep(200);
                putimage_withalpha(NULL,imgredma,34.67*col+230,35.7*row);
                break;
            case 3:
            case 7:
                Sleep(200);
                putimage_withalpha(NULL,imgredxiang,34.67*col+230,35.7*row);
                break;
            case 4:
            case 6:
                Sleep(200);
                putimage_withalpha(NULL,imgredshi,34.67*col+230,35.7*row);
                break;
            case 5:
                Sleep(200);
                putimage_withalpha(NULL,imgredshuai,34.67*col+230,35.7*row);
                break;
            case 10:
            case 11:
                Sleep(200);
                putimage_withalpha(NULL,imgredpao,34.67*col+230,35.7*row);
                break;
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                Sleep(200);
                putimage_withalpha(NULL,imgredbing,34.67*col+230,35.7*row);
                break;
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
                Sleep(200);
                putimage_withalpha(NULL,imgblackzu,34.67*col+230,35.7*row);
                break;
            case 22:
            case 23:
                Sleep(200);
                putimage_withalpha(NULL,imgblackpao,34.67*col+230,35.7*row);
                break;
            case 24:
            case 32:
                Sleep(200);
                putimage_withalpha(NULL,imgblackche,34.67*col+230,35.7*row);
                break;
            case 25:
            case 31:
                Sleep(200);
                putimage_withalpha(NULL,imgblackma,34.67*col+230,35.7*row);
                break;
            case 26:
            case 30:
                Sleep(200);
                putimage_withalpha(NULL,imgblackxiang,34.67*col+230,35.7*row);
                break;
            case 27:
            case 29:
                Sleep(200);
                putimage_withalpha(NULL,imgblackshi,34.67*col+230,35.7*row);
                break;
            case 28:
                Sleep(200);
                putimage_withalpha(NULL,imgblackjiang,34.67*col+230,35.7*row);
                break;
            }
        }
    }
}

void init_chess1()
{
    for(int row=0; row<10; row++)
    {
        for(int col=0; col<9; col++)
        {
            switch(chart[row][col])
            {
            case 1:
            case 9:
                putimage_withalpha(NULL,imgredche,34.67*col+230,35.7*row);
                break;
            case 2:
            case 8:
                putimage_withalpha(NULL,imgredma,34.67*col+230,35.7*row);
                break;
            case 3:
            case 7:
                putimage_withalpha(NULL,imgredxiang,34.67*col+230,35.7*row);
                break;
            case 4:
            case 6:
                putimage_withalpha(NULL,imgredshi,34.67*col+230,35.7*row);
                break;
            case 5:
                putimage_withalpha(NULL,imgredshuai,34.67*col+230,35.7*row);
                break;
            case 10:
            case 11:
                putimage_withalpha(NULL,imgredpao,34.67*col+230,35.7*row);
                break;
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                putimage_withalpha(NULL,imgredbing,34.67*col+230,35.7*row);
                break;
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
                putimage_withalpha(NULL,imgblackzu,34.67*col+230,35.7*row);
                break;
            case 22:
            case 23:
                putimage_withalpha(NULL,imgblackpao,34.67*col+230,35.7*row);
                break;
            case 24:
            case 32:
                putimage_withalpha(NULL,imgblackche,34.67*col+230,35.7*row);
                break;
            case 25:
            case 31:
                putimage_withalpha(NULL,imgblackma,34.67*col+230,35.7*row);
                break;
            case 26:
            case 30:
                putimage_withalpha(NULL,imgblackxiang,34.67*col+230,35.7*row);
                break;
            case 27:
            case 29:
                putimage_withalpha(NULL,imgblackshi,34.67*col+230,35.7*row);
                break;
            case 28:
                putimage_withalpha(NULL,imgblackjiang,34.67*col+230,35.7*row);
                break;
            }
        }
    }
}

void init_chess2()
{
    for(int row=0; row<10; row++)
    {
        for(int col=0; col<9; col++)
        {
            switch(chart1[row][col])
            {
            case 1:
            case 9:
                putimage_withalpha(NULL,imgredche,34.67*col+230,35.7*row);
                break;
            case 2:
            case 8:
                putimage_withalpha(NULL,imgredma,34.67*col+230,35.7*row);
                break;
            case 3:
            case 7:
                putimage_withalpha(NULL,imgredxiang,34.67*col+230,35.7*row);
                break;
            case 4:
            case 6:
                putimage_withalpha(NULL,imgredshi,34.67*col+230,35.7*row);
                break;
            case 5:
                putimage_withalpha(NULL,imgredshuai,34.67*col+230,35.7*row);
                break;
            case 10:
            case 11:
                putimage_withalpha(NULL,imgredpao,34.67*col+230,35.7*row);
                break;
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                putimage_withalpha(NULL,imgredbing,34.67*col+230,35.7*row);
                break;
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
                putimage_withalpha(NULL,imgblackzu,34.67*col+230,35.7*row);
                break;
            case 22:
            case 23:
                putimage_withalpha(NULL,imgblackpao,34.67*col+230,35.7*row);
                break;
            case 24:
            case 32:
                putimage_withalpha(NULL,imgblackche,34.67*col+230,35.7*row);
                break;
            case 25:
            case 31:
                putimage_withalpha(NULL,imgblackma,34.67*col+230,35.7*row);
                break;
            case 26:
            case 30:
                putimage_withalpha(NULL,imgblackxiang,34.67*col+230,35.7*row);
                break;
            case 27:
            case 29:
                putimage_withalpha(NULL,imgblackshi,34.67*col+230,35.7*row);
                break;
            case 28:
                putimage_withalpha(NULL,imgblackjiang,34.67*col+230,35.7*row);
                break;
            }
        }
    }
}

void init_interface()
{
    initgraph(762,357);
    setfont(30,0, "宋体");
    putimage(0,0,imgstart);
    putimage(381,0,imgbk);
    setbkmode(TRANSPARENT);
    setfontbkcolor(WHITE);
    setcolor(WHITE);
    outtextxy(260,10, "残局练习");
    outtextxy(260,50, "人机对战");
    outtextxy(260,100, "双人对战");
    outtextxy(260,150, "游戏说明");
    outtextxy(260,200, "排行榜");
    outtextxy(260,250, "退出游戏");
    outtextxy(260,300, "棋谱欣赏");
    outtextxy(50,245, "翻棋挑战");
    outtextxy(50,84, "揭棋挑战");
    setfont(45,0,"宋体");
    outtextxy(180,10, "中");
    outtextxy(180,110, "国");
    outtextxy(180,210, "象");
    outtextxy(180,310, "棋");
    setfont(20,0,"宋体");
    outtextxy(25,300, "16级2班刘继强");
    mus.Close();
}

void functional_tips1()
{
    initgraph(769,599);
    putimage(0,0,imgcheckerboard);
    putimage_withalpha(NULL,imgmusicopen,80,100);
    musicopen();
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
    setfontbkcolor(BLACK);
    setfont(19,0,"宋体");
    outtextxy(30,110,"音效:");
    outtextxy(30,160,"对局时间:");
    outtextxy(30,210,"步时:");
    outtextxy(600,50,"新局");
    outtextxy(600,100,"悔棋");
    outtextxy(600,150,"求和");
    outtextxy(600,200,"认输");
    outtextxy(600,250,"返回");
    outtextxy(600,300,"暂停");
    init_chart();
    init_chess1();
}

void functional_tips2()
{
    initgraph(612,504);
    setfont(30,0, "宋体");
    putimage(0,0,imgcheckerboard3);
    putimage(61,124,imgcheckerboard2);
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
    setfontbkcolor(BLACK);
    outtextxy(140,400,"返回");
    outtextxy(260,400,"新局");
    outtextxy(380,400,"悔棋");
}

void restart()
{
    //system("cls");
    cleardevice();
    functional_tips1();
    mus.Close();
}

int move_chess1(int x,int y)
{
    //coordinate(x,y);
    posx=(int)(x-230.0)/34.67;
    posy=(int)y/35.7;
    for(i=1; i<=32; i++)
    {
        if(i==chart[posy][posx])
            break;
    }
    return posy;
    //cout<<posy<<" "<<posx<<endl;
    //cout<<chart[posy][posx]<<endl;
}

int move_chess2(int x,int y)
{
    //coordinate(x,y);
    posx=(int)(x-230.0)/34.67;
    posy=(int)y/35.7;
    for(i=1; i<=32; i++)
    {
        if(i==chart[posy][posx])
            break;
    }
    return posx;
    //cout<<posy<<" "<<posx<<endl;
    //cout<<chart[posy][posx]<<endl;
}

int move_chess3(int x,int y)
{
    //coordinate(x,y);
    posx=(int)(x-230.0)/34.67;
    posy=(int)y/35.7;
    for(i=1; i<=32; i++)
    {
        if(i==chart[posy][posx])
            break;
    }
    return chart[posy][posx];
    //cout<<posy<<" "<<posx<<endl;
    //cout<<chart[posy][posx]<<endl;
}

int move_chess4(int x,int y)
{
    //coordinate(x,y);
    posx=(int)(x-83.0)/52.75;
    posy=(int)(y-148.0)/53.0;
    for(i=1; i<=32; i++)
    {
        if(i==Bangchess[posy][posx])
            break;
    }
    return posy;
    //cout<<posy<<" "<<posx<<endl;
    //cout<<Bangchess[posy][posx]<<endl;
}

int move_chess5(int x,int y)
{
    //coordinate(x,y);
    posx=(int)(x-83.0)/52.75;
    posy=(int)(y-148.0)/53.0;
    for(i=1; i<=32; i++)
    {
        if(i==Bangchess[posy][posx])
            break;
    }
    return posx;
    //cout<<posy<<" "<<posx<<endl;
    //cout<<Bangchess[posy][posx]<<endl;
}

int move_chess6(int x,int y)
{
    //coordinate(x,y);
    posx=(int)(x-83.0)/52.75;
    posy=(int)(y-148.0)/53.0;
    for(i=1; i<=32; i++)
    {
        if(i==Bangchess[posy][posx])
            break;
    }
    return Bangchess[posy][posx];
    //cout<<posy<<" "<<posx<<endl;
    //cout<<Bangchess[posy][posx]<<endl;
}

int start_winsock()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 1, 1 );
    err = WSAStartup(wVersionRequested, &wsaData );
    if ( err != 0 )
    {
        return -1;
    }
    if (LOBYTE( wsaData.wVersion ) != 1
            || HIBYTE(wsaData.wVersion) != 1 )
    {
        WSACleanup( );
        return -1;
    }
}

void set_socket(SOCKET *sock)
{
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    //设置通信地址
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 将INADDR_ANY转换为网络字节序，调用 htonl(long型)或htons(整型)
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    //把socket与地址绑定在一起
    bind(*sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    listen(*sock, 10);
}

void wait_conn(SOCKET *sockser, SOCKET *sockcli)
{
    SOCKADDR_IN  addrClient;
    int len = sizeof(SOCKADDR);
    printf("正在等待客户连接！！\n");
    *sockcli = accept(*sockser, (SOCKADDR*)&addrClient, &len);
    printf("连接成功，开始通信：\n");
}

void transmit(int x,int y)
{
     char sendBuf[100]= {0};
    itoa(chart[x][y],sendBuf,10);
    send(sockConn, sendBuf, strlen(sendBuf)+1, 0);
    printf("send success\n");
}

void receive(int x,int y)
{
    char recvBuf[100]= {0};
    FD_ZERO(&rfds);  /* 清空集合 */
    FD_SET(sockConn, &rfds);  /* 这里是添加检测 */
    ret=select(0, &rfds, NULL, NULL, &timeout);
    if(ret > 0)
    {
        if(FD_ISSET(sockConn,&rfds))  //这里检测的是fp在集合中是否状态变化，即可以操作。
        {
            ret = recv(sockConn, recvBuf, 100, 0);
            if (ret > 0) //大于0才是有意义的数据，防止对方掉线打印无用信息
            {
                chart[x][y]=atoi(recvBuf);
                printf("Says: %d\n", atoi(recvBuf));     // 接收信息
            }
        }
    }
}

char *time()
{
    struct tm *ptr;
    time_t lt;
    lt =time(NULL);
    ptr=gmtime(&lt);
    return ctime(&lt);
}

void write()
{
    FILE *fp1;
     if((fp1=fopen("D://write.txt","w"))==NULL)
    {
        cout<<"The file can not be found!"<<endl;
        exit(1);
    }
     fprintf(fp1,"%7s%7s%7d\n",game_player[j].name,game_player[j].color,j);
     fclose(fp1);
}

void game_instructions()
{
    putimage(0,0,imgdescription1);
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
    outtextxy(700,257,"下一步");
     for(; is_run(); delay_fps(2000))
    {
        mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&700<msg.x&&msg.x<762&&257<msg.y&&msg.y<277)
    {
        putimage(0,0,imgdescription2);
        setbkmode(TRANSPARENT);
        setcolor(BLACK);
        outtextxy(700,297,"下一步");
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&700<msg.x&&msg.x<762&&297<msg.y&&msg.y<317)
    {
        putimage(0,0,imgdescription3);
        setbkmode(TRANSPARENT);
        setcolor(BLACK);
        outtextxy(720,337,"返回");
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&722<msg.x&&msg.x<762&&337<msg.y&&msg.y<357)
    {
        init_interface();
        return ;
    }
}
}

void Ranking()
{
    setfont(20,0,"宋体");
    inputbox_getline("排行榜","\n请输入您的名字，输入完请回车",game_player[j].name,sizeof(game_player[j].name)/sizeof(*(game_player[j].name)));
    write();
    inputbox_getline("排行榜","\n请输入您的所属颜色方，输入完请回车",game_player[j].color,sizeof(game_player[j].color)/sizeof(*(game_player[j].color)));
    write();
    //fprintf(fp1,"%7s",*time());
    //xyprintf(300,100,"%8s",*time());
    j++;
}

void judge()
{
    setfont(50,0, "宋体");
    setbkmode(TRANSPARENT);
    setfontbkcolor(RED);
    int flag1=0,flag2=0;
    for(int row=0;row<10;row++)
    {
        for(int col=0;col<9;col++)
        {
            if(chart[row][col]==5)
                    flag1=1;
            if(chart[row][col]==28)
                    flag2=1;
        }
    }
    if(!flag1&&flag2)
    {
            outtextxy(210,480,"恭喜您，获胜!");
            Ranking();
    }
    if(flag1&&!flag2)
    {
        outtextxy(210,480,"很遗憾，失败!");
        Ranking();
    }
}

void game_over()
{
    exit(0);
}

void Chess_map()
{
    putimage(0,44,imgqp1);
    putimage(254,50,imgqp2);
    putimage(508,59,imgqp3);
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
    outtextxy(0,317,"下一步");
     for(; is_run(); delay_fps(2000))
    {
        mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&0<msg.x&&msg.x<60&&317<msg.y&&msg.y<337)
    {
        putimage(0,48,imgqp4);
        putimage(254,60,imgqp5);
        putimage(508,59,imgqp6);
        setbkmode(TRANSPARENT);
        setcolor(BLACK);
        outtextxy(20,337,"返回");
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&20<msg.x&&msg.x<60&&337<msg.y&&msg.y<357)
    {
        init_interface();
        return ;
    }
}
}

/*void mode_Bchess()
{
    functional_tips2();
    randomBangchess();
    init_Bangchess();
     for(; is_run(); delay_fps(2000))
    {
        mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
    if((int)msg.is_left()&&(int)msg.is_down()&&!(int)msg.is_up()&&85<msg.x&&msg.x<505&&148<msg.y&&msg.y<360)
    {
        int x2,y2;
        int x3,y3;
        int z2,z3;
        w++;
        if(!(w%2))
        {
            x2=msg.x;
            y2=msg.y;
           z2=Bangchess[move_chess4(x2,y2)][move_chess5(x2,y2)];
            //cout<<x2<<" "<<y2<<endl;
            putimage_withalpha(NULL,imgmark1,move_chess5(x2,y2)*52.75+83,move_chess4(x2,y2)*53.0+148);
        }
        else
        {
            x3=msg.x;
            y3=msg.y;
            z3=Bangchess[move_chess4(x3,y3)][move_chess5(x3,y3)];
            //cout<<z<<endl;
            Bangchess[move_chess4(x2,y2)][move_chess5(x2,y2)]=0;
            //transmit(p->move_chess1(x2,y2),p->move_chess2(x2,y2));
            //receive(p->move_chess1(x2,y2),p->move_chess2(x2,y2));
            Bangchess[move_chess4(x3,y3)][move_chess5(x3,y3)]=z2;
            //transmit(p->move_chess1(x3,y3),p->move_chess2(x3,y3));
            //receive(p->move_chess1(x3,y3),p->move_chess2(x3,y3));
            putimage(61,124,imgcheckerboard2);
            init_Bangchess1();
            go_chess(move_chess4(x2,y2),move_chess5(x2,y2));
            go_chess(move_chess4(x3,y3),move_chess5(x3,y3));
            musicopen1();
            //mus1.Close();
        }
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&140<msg.x&&msg.x<200&&400<msg.y&&msg.y<430)
    {
        initgraph(762,357);
        init_interface();
        return ;
    }
}
}
*/
void functional_tips()
{
    int x=0,y=0;
    int x1=0,y1=0;
    int z=0,z1=0,z2=0;
    int a=0,b=0;
    int c=0,d=0;
    int ans = 1;
    int time_start = fclock();
    int temp;
    int cnt;
    initgraph(769,599);
    putimage(0,0,imgcheckerboard);
    putimage_withalpha(NULL,imgmusicopen,80,100);
    musicopen();
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
    setfontbkcolor(BLACK);
    outtextxy(30,110,"音效:");
    outtextxy(30,160,"对局时间:");
    outtextxy(30,210,"步时:");
    outtextxy(600,50,"新局");
    outtextxy(600,100,"悔棋");
    outtextxy(600,150,"求和");
    outtextxy(600,200,"认输");
    outtextxy(600,250,"返回");
    outtextxy(600,300,"暂停");
    init_chart();
    init_chess();
    for ( ; is_run() ; delay_fps(60))
	{
        mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
        temp = fclock();
        if(temp != time_start)
        {
            setfont(19,0, "宋体");
            time_start = temp;
            setbkmode(OPAQUE);
            setfontbkcolor(RGB(255,255,0));
            xyprintf(120, 160, "%2d:%2d:%2d",time_start/3600,(time_start-time_start/3600*3600)/60,time_start-(time_start-time_start/3600*3600)/60*60);
            //xyprintf(120, 210, "%d sec",36-time_start);
        }
        /*
        if(!(40-time_start))
        {
            setfont(45,0, "宋体");
            setbkmode(TRANSPARENT);
            setfontbkcolor(RED);
            outtextxy(227,149,"时间到,你输了!");
            return ;
        }
        */
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<640&&300<msg.y&&msg.y<320)
        {
            cnt++;
            if(cnt%2)
            {
                putimage_withalpha(NULL,imgmusicopen,80,101);
                musicopen();
            }
            else
            {
                putimage_withalpha(NULL,imgmusicclose,80,101);
                mus.Close();//关闭音乐文件
            }
            system("pause");
        }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<638&&50<msg.y&&msg.y<69)
    {
        restart();
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<640&&300<msg.y&&msg.y<320)
    {
        cnt++;
        if(cnt%2)
        {
            putimage_withalpha(NULL,imgmusicopen,80,101);
            musicopen();
        }
        else
        {
            putimage_withalpha(NULL,imgmusicclose,80,101);
            mus.Close();//关闭音乐文件
        }
        system("pause");
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<638&&200<msg.y&&msg.y<219)
    {
        setfont(45,0, "宋体");
        setbkmode(TRANSPARENT);
        setcolor(RED);
        outtextxy(227,149,"很遗憾,您输了!");
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<638&&250<msg.y&&msg.y<269)
    {
        init_interface();
        return ;
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&81<msg.x&&msg.x<121&&102<msg.y&&msg.y<142)
    {
        counter++;
        if(counter%2)
        {
            putimage_withalpha(NULL,imgmusicopen,80,100);
            musicopen();
        }
        else
        {
            putimage_withalpha(NULL,imgmusicclose,80,100);
            mus.Close();//关闭音乐文件
        }
    }
    if((int)msg.is_right()&&(int)msg.is_up()&&!(int)msg.is_down()&&230<msg.x&&msg.x<541&&0<msg.y&&msg.y<357)
    {
        ans++;
        if(!(ans%2))
        {
            x=msg.x;
            y=msg.y;
            z=move_chess3(x,y);
            a=move_chess1(x,y);
            b=move_chess2(x,y);
            putimage(203,0,imgcheckerboard1);
            init_chess1();
           putimage_withalpha(NULL,imgmark,move_chess2(x,y)*34.67+230,move_chess1(x,y)*35.7);
        }
        else
        {
            x1=msg.x;
            y1=msg.y;
            z1=move_chess3(x1,y1);
            c=move_chess1(x1,y1);
            d=move_chess2(x1,y1);
            if(17<=z&&z<=21&&((1<=z1&&z1<=16)||z1==0))
            {
                 /*if(blackzu[c][d]&&d==5&&(a==c)&&(b-d==1))
                    {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                    }
                    if(blackzu[c][d]&&d<=4&&((b-d==1&&a==c)||(abs(a-c)==1)))
                    {
                    */
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                   // }
            }//卒的走法
             if(12<=z&&z<=16&&((17<=z1&&z1<=32)||z1==0))
            {
                /*if(redbing[c][d]&&d==4&&(a==c)&&(d-b==1))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if(redbing[c][d]&&d>=5&&(((a==c)&&d-b==1)||abs(a-c)==1))
                {*/
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//兵的走法
            if((z==27||z==29)&&((1<=z1&&z1<=16)||z1==0))
            {
                if(blackshi[c][d]&&(abs(b-d)==1&&abs(a-c)==1))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//士的走法
            if((z==4||z==6)&&((17<=z1&&z1<=32)||z1==0))
            {
                if(redshi[c][d]&&(abs(b-d)==1&&abs(a-c)==1))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//仕的走法
            if((z==28)&&((1<=z1&&z1<=11)||z1==0))
            {
                int flag=0;
                if(z1==5)
                {
                    if(a==c)
                     {
                     for(int i=d+1;i<b;i++)
                     {
                         if(chart[a][i]>0)
                         {
                             flag=1;
                             break;
                         }
                     }
                     if(!flag)
                    {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                     }
                     }
                }
                if(blackjiang[c][d]&&(abs(b-d)==1||abs(a-c)==1))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//将的走法
              if((z==5)&&((22<=z1&&z1<=32)||z1==0))
            {
                int flag=0;
                if(z1==28)
                {
                    if(a==c)
                     {
                     for(int i=b+1;i<d;i++)
                     {
                         if(chart[a][i]>0)
                         {
                             flag=1;
                             break;
                         }
                     }
                     if(!flag)
                    {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                     }
                     }
                }
                if(redshuai[c][d]&&(abs(b-d)==1||abs(a-c)==1))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//帥的走法
              if(((z==3)||(z==7))&&((17<=z1&&z1<=32)||z1==0))
            {
                if(redxiang[c][d]&&(abs(b-d)==2&&abs(a-c)==2)&&(!chart[(a+c)/2][(b+d)/2]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//相的走法
              if((z==26||z==30)&&((1<=z1&&z1<=16)||z1==0))
            {
                if(blackxiang[c][d]&&(abs(b-d)==2&&abs(a-c)==2)&&(!chart[(a+c)/2][(b+d)/2]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//象的走法
            if((z==25||z==31)&&((1<=z1&&z1<=16)||z1==0))
            {
                if((b-d)==2&&abs(a-c)==1&&(!chart[a][b-1]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if(abs(b-d)==1&&(a-c)==2&&(!chart[a-1][b]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if((d-b)==2&&abs(a-c)==1&&(!chart[a][b+1]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if(abs(d-b)==1&&(c-a)==2&&(!chart[a+1][b]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }//黑马的走法
             if((z==2||z==8)&&((17<=z1&&z1<=32)||z1==0))
            {
                if((b-d)==2&&abs(a-c)==1&&(!chart[a][b-1]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if(abs(b-d)==1&&(a-c)==2&&(!chart[a-1][b]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if((d-b)==2&&abs(a-c)==1&&(!chart[a][b+1]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
                if(abs(d-b)==1&&(c-a)==2&&(!chart[a+1][b]))
                {
                    chart[a][b]=0;
                    chart[c][d]=z;
                    putimage(203,0,imgcheckerboard1);
                    init_chess1();
                }
            }
            //红马的走法
            if((z==1||z==9)&&((17<=z1&&z1<=32)||z1==0))
            {
               int flag1=0,flag2=0;
                    if(a==c)
                    {
                        if(b>d)
                        {
                            for(int i=d+1;i<b;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(b<d)
                        {
                            for(int i=b+1;i<d;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(!flag1)
                        {
                            chart[a][b]=0;
                        chart[c][d]=z;
                        receive(a,b);
                         transmit(a,b);
                         receive(c,d);
                        transmit(c,d);
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                    }
                     if(b==d)
                     {
                         if(a>c)
                        {
                            for(int i=c+1;i<a;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(a<c)
                        {
                            for(int i=a+1;i<c;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(!flag2)
                        {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        receive(a,b);
                         transmit(a,b);
                         receive(c,d);
                        transmit(c,d);
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                     }
            }
        //红车的走法
            if((z==24||z==32)&&((1<=z1&&z1<=16)||z1==0))
            {
                int flag1=0,flag2=0;
                    if(a==c)
                    {
                        if(b>d)
                        {
                            for(int i=d+1;i<b;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(b<d)
                        {
                            for(int i=b+1;i<d;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(!flag1)
                        {
                            chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                    }
                     if(b==d)
                     {
                         if(a>c)
                        {
                            for(int i=c+1;i<a;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(a<c)
                        {
                            for(int i=a+1;i<c;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(!flag2)
                        {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                     }
            }
            //黑车的走法
            if((z==10||z==11)&&z1==0)
            {
                int flag1=0,flag2=0;
                    if(a==c)
                    {
                        if(b>d)
                        {
                            for(int i=d+1;i<b;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(b<d)
                        {
                            for(int i=b+1;i<d;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(!flag1)
                        {
                            chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                    }
                     if(b==d)
                     {
                         if(a>c)
                        {
                            for(int i=c+1;i<a;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(a<c)
                        {
                            for(int i=a+1;i<c;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(!flag2)
                        {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                     }
            }//红炮的走法1
            if((z==10||z==11)&&(17<=z1&&z1<=32))
               {
                   int flag1=0,flag2=0;
                   if(a==c)
                    {
                        if(b>d)
                        {
                            for(int i=d+1;i<b;i++)
                            {
                                if(chart[a][i]>0)
                                {
                                    flag1++;
                                }
                            }
                             if(flag1==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                        if(b<d)
                        {
                            for(int i=b+1;i<d;i++)
                            {
                                if(chart[a][i]>0)
                                {
                                    flag2++;
                                }
                            }
                            if(flag2==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                    }
                     if(b==d)
                     {
                         if(a>c)
                        {
                            for(int i=c+1;i<a;i++)
                            {
                                if(chart[i][b]>0)
                                {
                                    flag1++;
                                }
                            }
                            if(flag1==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                        if(a<c)
                        {
                            for(int i=a+1;i<c;i++)
                            {
                                if(chart[i][b]>0)
                                {
                                    flag2++;
                                }
                            }
                            if(flag2==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                    }
               }
            //红炮的走法2
              if((z==22||z==23)&&z1==0)
            {
                int flag1=0,flag2=0;
                    if(a==c)
                    {
                        if(b>d)
                        {
                            for(int i=d+1;i<b;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(b<d)
                        {
                            for(int i=b+1;i<d;i++)
                            {
                                if(chart[a][i])
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                        }
                        if(!flag1)
                        {
                            chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                    }
                     if(b==d)
                     {
                         if(a>c)
                        {
                            for(int i=c+1;i<a;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(a<c)
                        {
                            for(int i=a+1;i<c;i++)
                            {
                                if(chart[i][b])
                                {
                                    flag2=1;
                                    break;
                                }
                            }
                        }
                        if(!flag2)
                        {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                        }
                     }
            }//黑炮的走法1
            if((z==22||z==23)&&(1<=z1&&z1<=16))
               {
                   int flag1=0,flag2=0;
                   if(a==c)
                    {
                        if(b>d)
                        {
                            for(int i=d+1;i<b;i++)
                            {
                                if(chart[a][i]>0)
                                {
                                    flag1++;
                                }
                            }
                             if(flag1==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                        if(b<d)
                        {
                            for(int i=b+1;i<d;i++)
                            {
                                if(chart[a][i]>0)
                                {
                                    flag2++;
                                }
                            }
                            if(flag2==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                    }
                     if(b==d)
                     {
                         if(a>c)
                        {
                            for(int i=c+1;i<a;i++)
                            {
                                if(chart[i][b]>0)
                                {
                                    flag1++;
                                }
                            }
                            if(flag1==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                        if(a<c)
                        {
                            for(int i=a+1;i<c;i++)
                            {
                                if(chart[i][b]>0)
                                {
                                    flag2++;
                                }
                            }
                            if(flag2==1)
                             {
                        chart[a][b]=0;
                        chart[c][d]=z;
                        putimage(203,0,imgcheckerboard1);
                        init_chess1();
                             }
                        }
                    }
               }
            //黑炮的走法2
        musicopen1();
        judge();
    }
    if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&600<msg.x&&msg.x<640&&100<msg.y&&msg.y<120)
    {
        chart[a][b]=z;
        //receive(a,b);
        //transmit(a,b);
        putimage(203,0,imgcheckerboard1);
        init_chess1();
        if(!z1)
        {
            chart[c][d]=0;
             //receive(c,d);
            //transmit(c,d);
            putimage(203,0,imgcheckerboard1);
            init_chess1();
        }
        else
        {
            chart[c][d]=z1;
             //receive(c,d);
            //transmit(c,d);
            putimage(203,0,imgcheckerboard1);
            init_chess1();
        }
    }
}
}

void function_diagram()
{
    functional_tips();
    //limit_time();
    //game_time();
}

void read()
{
    FILE *fp2;
     if((fp2=fopen("D://write.txt","r"))==NULL)
    {
        cout<<"The file can not be opened!"<<endl;
        exit(1);
    }
    fscanf(fp2,"%d",&j);
    sort(game_player,game_player+j,cmp);
     setfont(30,0,"宋体");
     for(int k=0;k<j;k++)
    {
    fscanf(fp2,"%s%s",game_player[k].name,game_player[k].color);
    xyprintf(100,100,"%8s%8s\n",game_player[k].name,game_player[k].color);
    }
     fclose(fp2);
}

void phb()
{
    initgraph(810,518);
    putimage(0,0,imgranking);
    setfont(50,0,"宋体");
    setcolor(RED);
    outtextxy(315, 20, "排行榜");
    outtextxy(700, 450, "返回");
    read();
  for ( ; is_run(); delay_fps(2000))
	{
	     mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&700<msg.x&&msg.x<800&&450<msg.y&&msg.y<500)
        {
            init_interface();
            return ;
        }
	}
}

int main()
{
     /*
    if(start_winsock() == -1)
        return 0;
    set_socket(&sockSrv);
    wait_conn(&sockSrv,&sockConn);
    */
    setinitmode(0);
    initgraph(915, 495);
    imgstart = newimage();
    imgmark = newimage();
    imgmark1 = newimage();
    imgdescription1=newimage();
    imgdescription2=newimage();
    imgqp1=newimage();
    imgqp2=newimage();
    imgqp3=newimage();
    imgqp4=newimage();
    imgqp5=newimage();
    imgqp6=newimage();
    imgdescription3=newimage();
    imgbk = newimage();
    imgmusicopen = newimage();
    imgmusicclose = newimage();
    imgcheckerboard = newimage();
    imgcheckerboard1 = newimage();
    imgcheckerboard2 = newimage();
    imgcheckerboard3 = newimage();
    imgranking = newimage();
    imgloading = newimage();
    imgredche = newimage();
    imgredma = newimage();
    imgredpao = newimage();
    imgredshi = newimage();
    imgredxiang = newimage();
    imgredshuai = newimage();
    imgredbing = newimage();
    imgblackche = newimage();
    imgblackma = newimage();
    imgblackpao = newimage();
    imgblackshi = newimage();
    imgblackxiang = newimage();
    imgblackjiang = newimage();
    imgblackzu = newimage();
    imgfredche= newimage();
    imgfredma= newimage();
    imgfredpao= newimage();
    imgfredshi= newimage();
    imgfredxiang= newimage();
    imgfredshuai= newimage();
    imgfredbing= newimage();
    imgfblackche= newimage();
    imgfblackma= newimage();
    imgfblackpao= newimage();
    imgfblackshi= newimage();
    imgfblackxiang= newimage();
    imgfblackjiang= newimage();
    imgfblackzu= newimage();
    imgfbk= newimage();
    getimage(imgstart, "D:\\Chinese chess\\开始.png");
    getimage(imgmark, "D:\\Chinese chess\\标记.png");
    getimage(imgmark1, "D:\\Chinese chess\\标记1.png");
    getimage(imgbk, "D:\\Chinese chess\\棋悟.png");
    getimage(imgdescription1, "D:\\Chinese chess\\说明1.png");
    getimage(imgdescription2, "D:\\Chinese chess\\说明2.png");
    getimage(imgdescription3, "D:\\Chinese chess\\说明3.png");
    getimage(imgqp1, "D:\\Chinese chess\\棋谱1.png");
    getimage(imgqp2, "D:\\Chinese chess\\棋谱2.png");
    getimage(imgqp3, "D:\\Chinese chess\\棋谱3.png");
    getimage(imgqp4, "D:\\Chinese chess\\棋谱4.png");
    getimage(imgqp5, "D:\\Chinese chess\\棋谱5.png");
    getimage(imgqp6, "D:\\Chinese chess\\棋谱6.png");
    getimage(imgmusicopen, "D:\\Chinese chess\\声音图标开启.png");
    getimage(imgmusicclose, "D:\\Chinese chess\\声音图标关闭.png");
    getimage(imgcheckerboard, "D:\\Chinese chess\\棋盘图.png");
    getimage(imgcheckerboard1, "D:\\Chinese chess\\棋盘.png");
    getimage(imgranking, "D:\\Chinese chess\\排行榜.png");
    getimage(imgcheckerboard2, "D:\\Chinese chess\\翻棋界面.png");
    getimage(imgcheckerboard3, "D:\\Chinese chess\\翻棋界面1.png");
    getimage(imgloading, "D:\\Chinese chess\\加载图.png");
    getimage(imgredche, "D:\\Chinese chess\\红车.png");
    getimage(imgredma, "D:\\Chinese chess\\红马.png");
    getimage(imgredpao, "D:\\Chinese chess\\红炮.png");
    getimage(imgredshi, "D:\\Chinese chess\\红仕.png");
    getimage(imgredxiang, "D:\\Chinese chess\\红相.png");
    getimage(imgredshuai, "D:\\Chinese chess\\红帥.png");
    getimage(imgredbing, "D:\\Chinese chess\\红兵.png");
    getimage(imgblackche, "D:\\Chinese chess\\黑车.png");
    getimage(imgblackma, "D:\\Chinese chess\\黑马.png");
    getimage(imgblackpao, "D:\\Chinese chess\\黑炮.png");
    getimage(imgblackshi, "D:\\Chinese chess\\黑士.png");
    getimage(imgblackxiang, "D:\\Chinese chess\\黑象.png");
    getimage(imgblackjiang, "D:\\Chinese chess\\黑将.png");
    getimage(imgblackzu, "D:\\Chinese chess\\黑卒.png");
    getimage(imgfredche, "D:\\Chinese chess\\翻棋红车.png");
    getimage(imgfredma, "D:\\Chinese chess\\翻棋红马.png");
    getimage(imgfredpao, "D:\\Chinese chess\\翻棋红炮.png");
    getimage(imgfredshi, "D:\\Chinese chess\\翻棋红仕.png");
    getimage(imgfredxiang, "D:\\Chinese chess\\翻棋红相.png");
    getimage(imgfredshuai, "D:\\Chinese chess\\翻棋红帥.png");
    getimage(imgfredbing, "D:\\Chinese chess\\翻棋红兵.png");
    getimage(imgfblackche, "D:\\Chinese chess\\翻棋黑车.png");
    getimage(imgfblackma, "D:\\Chinese chess\\翻棋黑马.png");
    getimage(imgfblackpao, "D:\\Chinese chess\\翻棋黑炮.png");
    getimage(imgfblackshi, "D:\\Chinese chess\\翻棋黑士.png");
    getimage(imgfblackxiang, "D:\\Chinese chess\\翻棋黑象.png");
    getimage(imgfblackjiang, "D:\\Chinese chess\\翻棋黑将.png");
    getimage(imgfblackzu, "D:\\Chinese chess\\翻棋黑卒.png");
    getimage(imgfbk, "D:\\Chinese chess\\翻棋.png");
    while(1)
    {
        tot++;
        putimage(0,0,imgloading);
        setfont(30,0, "宋体");
        setbkmode(TRANSPARENT);
        setfontbkcolor(RED);
        setcolor(RED);
        xyprintf(300,250, "LOADING......  %%%d",tot);
        if(tot>100)
            break;
        Sleep(20);
    }
    initgraph(762, 357);
    init_interface();
    while(1)
    {
        setfont(19,0, "宋体");
        mouse_msg msg = {0};
        while(mousemsg())
        {
            msg = getmouse();
        }
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&260<msg.x&&msg.x<380&&150<msg.y&&msg.y<180)
        {
            game_instructions();
        }
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&260<msg.x&&msg.x<380&&250<msg.y&&msg.y<280)
        {
            game_over();
        }
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&260<msg.x&&msg.x<380&&300<msg.y&&msg.y<330)
        {
            Chess_map();
        }
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&260<msg.x&&msg.x<380&&100<msg.y&&msg.y<130)
        {
            function_diagram();
        }
        /*if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&50<msg.x&&msg.x<170&&245<msg.y&&msg.y<275)
        {
            mode_Bchess();
        }
        */
        if((int)msg.is_left()&&(int)msg.is_up()&&!(int)msg.is_down()&&260<msg.x&&msg.x<350&&200<msg.y&&msg.y<230)
        {
            phb();
        }
        Sleep(100);
    }
    //closesocket(sServer);
    //WSACleanup();
    getch();
    mus.Close();
    closegraph();
    return 0;
}
