#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH  500
#define HEIGHT 500
#define OFFSET 15

int R;//设置全局变量为圆的半径

void Init()    //其它初始化
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);    //设置背景颜色，完全不透明
    glColor3f(1.0f,0.0f,0.0f);        //设置画笔颜色

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 30.0, 0.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void CirclePoint(int x,int y)
{
    glPointSize(5);    //设置点的粗细
    glBegin(GL_POINTS);

    glVertex2i(OFFSET+x,OFFSET+y);
    glVertex2i(OFFSET+y,OFFSET+x);
    glVertex2i(OFFSET-y,OFFSET+x);
    glVertex2i(OFFSET-x,OFFSET+y);
    glVertex2i(OFFSET-x,OFFSET-y);
    glVertex2i(OFFSET-y,OFFSET-x);
    glVertex2i(OFFSET+y,OFFSET-x);
    glVertex2i(OFFSET+x,OFFSET-y);

    glEnd();
}

void MidBresenhamCircle(int r)
{
    int x,y,d;
    x=0,y=r,d=1-r;
    while(x<=y)
    {
        CirclePoint(x,y);    //画圆
        if(d<0)
            d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
    }
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);    //清空颜色堆栈

    MidBresenhamCircle(R);    //画圆

    glFlush();    //清空缓冲区指令
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);    //初始化显示模式
    glutInitWindowSize(WIDTH,HEIGHT);    //初始化窗口大小
    glutInitWindowPosition(200,100);    //初始化窗口出现位置
    glutCreateWindow("中点Bresenham画圆");    //初始化窗口标题

    printf("\n输入圆的半径（正整数）：");
    scanf("%d",&R);

    glutDisplayFunc(Display);    //注册显示函数
    Init();        //其它初始化
    glutMainLoop();    //进入程序循环

    return 0;
}
