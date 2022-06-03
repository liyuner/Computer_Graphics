#include <windows.h>
#include <GL/glut.h>
#include <cstdio>

#define LEFT 1//代表0001
#define RIGHT 2//代表0010
#define BOTTOM 4//代表0100
#define TOP 8//代表1000

struct Point{
	int x, y;
}point[2],initp[2];
struct Rectangle {
	int xmin,ymin,xmax,ymax;
}rec;

void mydisplay();
void init();
void myReshape(int w,int h);
int enCode(Point p);
void func();

void mydisplay();

void init(){
	printf("请输入直线段端点坐标\n");
	scanf("%d%d%d%d",&point[0].x,&point[0].y,&point[1].x,&point[1].y);
	printf("请输入矩形框对角线坐标(矩形框大小不超过500x400)\n");
	scanf("%d%d%d%d",&rec.xmin,&rec.ymin,&rec.xmax,&rec.ymax);
	return;
}

void myReshape (GLsizei w, GLsizei h)
{
	if(h == 0)
		h = 1;
	// 设置视区尺寸
	glViewport(0, 0, w, h);

	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//建立修剪空间的范围
	if (w <= h)
		glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
	else
		glOrtho(0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);
}

int enCode(Point p){
	int ans = 0;
	if(p.x < rec.xmin) ans |= LEFT;
	else if(p.x > rec.xmax) ans |= RIGHT;
	if(p.y < rec.ymin) ans |= BOTTOM;
	else if(p.y > rec.ymax) ans |= TOP;
	return ans;
}

void func(){
	int x,y;
	int code1 = enCode(point[0]);
	int code2 = enCode(point[1]);
	int code = 0;
	while(code1 || code2) {
		if(code1 & code2) {
			break;
		}
		if(code1) code = code1;
		else code = code2;

		if(code & LEFT) {
			x = rec.xmin;
			y = point[0].y + (point[1].y - point[0].y) *
			(rec.xmin - point[0].x) / (point[1].x - point[0].x);
		}else if(code & RIGHT) {
			x = rec.xmax;
			y = point[0].y + (point[1].y - point[0].y) *
			(rec.xmax - point[0].x) / (point[1].x - point[0].x);
		}else if(code & BOTTOM) {
			y = rec.ymin;
			x = point[0].x + (point[1].x - point[0].x) *
			(rec.ymin - point[0].y) / (point[1].y - point[0].y);
		}else if(code & TOP) {
			y = rec.ymax;
			x = point[0].x + (point[1].x - point[0].x) *
			(rec.ymax - point[0].y) / (point[1].y - point[0].y);
		}
		if(code == code1) {
			point[0].x = x;
			point[0].y = y;
			code1 = enCode(point[0]);
		}else {
			point[1].x = x;
			point[1].y = y;
			code2 = enCode(point[1]);
		}
	}
}

void mydisplay(){
	initp[0] = point[0];
	initp[1] = point[1];
	func();// deal with point[0] point[1]

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glPointSize(2);
	glBegin(GL_LINE_LOOP);
	glVertex2i(rec.xmin, rec.ymin);//绘制矩形
	glVertex2i(rec.xmin, rec.ymax);
	glVertex2i(rec.xmax, rec.ymax);
	glVertex2i(rec.xmax, rec.ymin);
	glEnd();
	glColor3f(0,0,0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(initp[0].x, initp[0].y);
	glVertex2i(initp[1].x, initp[1].y);
	glEnd();

	glColor3f(0.5,0.5,0);
	glBegin(GL_LINES);
	glVertex2i(point[0].x,point[0].y);
	glVertex2i(point[1].x,point[1].y);
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(500, 400);
	glutCreateWindow("Cohen-Sutherland裁剪算法");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(&mydisplay);
	glutMainLoop();
	return 0;
}
