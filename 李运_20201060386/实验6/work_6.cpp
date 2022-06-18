#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<stdlib.h>
#include <stdio.h>

using namespace std;
GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;//显示表标识

class wcPt2D
{
public:
    GLfloat x, y;
    wcPt2D(GLfloat x=0,GLfloat y=0)
    {
        this->x = x;
        this->y = y;
    }
};

wcPt2D verts[4] = { wcPt2D(10, 200.0), wcPt2D(100.0, 150.0), wcPt2D(120, 240.0), wcPt2D (30.0,220.0)};
GLfloat tx;
GLfloat ty;
//基准点
GLfloat xr;
GLfloat yr;
GLdouble theta;//旋转角度
GLfloat px,py;//比例系数

static void init(void)
{
    //初始化函数，并加入表
    glClearColor(1.0, 1.0, 1.0, 0.0);//设置为白色背景
    regHex = glGenLists(1);//获得一个标识
    glColor3f(1.0, 0.0,0.0);
    glPointSize(2);
}

void winReshapeFcn(int newWidth, int newHeight)
{
    //窗口重定形函数
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
    gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newWidth);
    glClear(GL_COLOR_BUFFER_BIT);

}

void Move(wcPt2D *verts,GLfloat tx,GLfloat ty)
{
    //平移函数，作为例子平移四边形
    GLint nverts = 4;
    GLint k;
    wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
    for (k = 0; k < nverts; ++k)
    {
        newVerts[k].x = verts[k].x + tx;
        newVerts[k].y = verts[k].y + ty;
    }

    glBegin(GL_QUADS);
    for (k = 0; k < nverts; ++k)
    {
        glVertex2f(verts[k].x, verts[k].y);
    }
    for (k = 0; k < nverts; ++k)
    {
        glVertex2f(newVerts[k].x, newVerts[k].y);
    }
    glEnd();

    glFlush();
}

void rotate(wcPt2D *verts,GLfloat xr,GLfloat yr,GLdouble theta)
{
    //旋转函数，作为例子旋转四边形
    GLint nverts = 4;
    GLint k;
    wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
    for (k = 0; k < nverts; ++k)
    {
        newVerts[k].x = xr + (verts[k].x - xr)*cos(theta) - (verts[k].y - yr)*sin(theta);
        newVerts[k].y = yr + (verts[k].x - xr)*sin(theta) + (verts[k].y - yr)*cos(theta);
    }

    glBegin(GL_QUADS);
    for (k = 0; k < nverts; ++k)
    {
        glVertex2f(verts[k].x, verts[k].y);
    }
    for (k = 0; k < nverts; ++k)
    {
        glVertex2f(newVerts[k].x, newVerts[k].y);
    }
    glEnd();

    glFlush();
}

void symmetry(wcPt2D *verts)
{
    //对称函数，作为例子对称四边形，关于y=x对称
    GLint nverts = 4;
    GLint k;
    wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
    for (k = 0; k < nverts; ++k)
    {
        newVerts[k].x = verts[k].y;
        newVerts[k].y = verts[k].x;
    }

    glBegin(GL_QUADS);
    for (k = 0; k < nverts; ++k)
    {
        glVertex2f(verts[k].x, verts[k].y);
    }
    for (k = 0; k < nverts; ++k)
    {
        glVertex2f(newVerts[k].x, newVerts[k].y);
    }
    glEnd();

    glFlush();
}

void proportion(wcPt2D *verts,GLfloat px,GLfloat py)
{
    //比例函数，作为例子将四边形进行比例缩放
	GLint nverts = 4;
	wcPt2D fixedPt = verts[0];//选择左下的点作为基准点
	GLint k;
	wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
	for (k = 0; k < nverts;++k)
	{
		newVerts[k].x = verts[k].x*px+fixedPt.x*(1-px)+200;//加200是为了水平平移200个像素，方便比较
		newVerts[k].y = verts[k].y*py + fixedPt.y*(1 - py);
	}

	glBegin(GL_QUADS);
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(verts[k].x, verts[k].y);
	}
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(newVerts[k].x, newVerts[k].y);
	}
	glEnd();

	glFlush();
}


void funcPlot1()//平移展示
{
    glClear(GL_COLOR_BUFFER_BIT);
    Move(verts,tx,ty);
}

void funcPlot2()//旋转展示
{
    glClear(GL_COLOR_BUFFER_BIT);
    rotate(verts,xr,yr,theta);
}

void funcPlot3()//对称展示
{
    glClear(GL_COLOR_BUFFER_BIT);
    symmetry(verts);
}

void funcPlot4()//比例展示
{
    glClear(GL_COLOR_BUFFER_BIT);
    proportion(verts,px,py);

}


void Translation()//平移
{
    glutCreateWindow("An example of translation");
    printf("输入x,y偏移量（范围为0-200,0-200)：");
    scanf("%f%f",&tx,&ty);
    init();
    glutDisplayFunc(funcPlot1);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();

}

void Rotation()//旋转
{
    glutCreateWindow("An example of rotation");
    printf("输入基准点坐标和旋转角度");
    scanf("%f%f%lf",&xr,&yr,&theta);
    init();
    glutDisplayFunc(funcPlot2);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}

void Symmetry()//对称
{
    glutCreateWindow("An example of symmetry");
    init();
    glutDisplayFunc(funcPlot3);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();

}

void Proportion()//比例
{
    glutCreateWindow("An example of proportion");
    printf("输入比例系数");
    scanf("%f%f",&px,&py);
    init();
    glutDisplayFunc(funcPlot4);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();

}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);

    int select;
    printf("【1】平移\n【2】比例\n【3】旋转\n【4】对称\n【0】退出");
    do
    {
        printf("\n输入选择：");
        scanf("%d",&select);
        switch(select)
        {
        case 1:
            Translation();
            break;
        case 2:
            Proportion();
            break;
        case 3:
             Rotation();
            break;
        case 4:
            Symmetry();
            break;
        default:
            printf("error!\n");
        }
    }
    while(select!=0);

    return 0;
}
