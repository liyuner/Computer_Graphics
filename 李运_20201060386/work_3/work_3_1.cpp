#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x1, y1, x2, y2;//设置全局变量，分别代表第一个点和第二个点的坐标

void setPixel(GLint x, GLint y)
{
    glPointSize(5.0f);
    glBegin(GL_POINTS);
         glVertex2i(x,y);
    glEnd();
    glFlush();
}

void ChangeSize(GLsizei w, GLsizei h)//窗口改变时调用的登记函数
{
    if(h==0)
        h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(0.0f,250.0f,0.0f,250.0f*h/w,1.0,-1.0);
    else
        glOrtho(0.0f,250.0f*w/h,0.0f,250.0f,1.0,-1.0);
}

/*|k|<=1*/
void lineBres(int x0, int y0, int xEnd, int yEnd)
{
    int dx=fabs(xEnd-x0),dy=fabs(yEnd-y0);
    int p=2*dy-dx;
    int twoDy=2*dy,twoDyminusDx=2*(dy-dx);
    int x,y;

    if(x0>xEnd)
    {
        x=xEnd;
        y=yEnd;
        xEnd=yEnd;
    }

    else
    {
        x=x0;
        y=y0;
    }
    setPixel(x,y);

    while(x<xEnd)
    {
        x++;
        if(p<0)
            p+=twoDy;
        else
        {
            y++;
            p+=twoDyminusDx;
        }
        setPixel(x,y);
    }
}

void myDisplay(void)
{
      lineBres(x1,y1,x2,y2);
}

void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

int main(int argc, char** argv)
{
    printf("请输入第一个点的坐标（整数）：\n");
    scanf("%d%d",&x1,&y1);
    printf("\n请输入第二个点的坐标（整数）：\n");
    scanf("%d%d",&x2,&y2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowPosition(400, 300);
    glutCreateWindow("A Program of Bresenham");

    init();
    glutDisplayFunc(&myDisplay);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}
