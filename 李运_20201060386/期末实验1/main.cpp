#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define stripeImageWidth 10//设置贴图的宽度为10

//定义全局变量
GLubyte stripeImage[4*stripeImageWidth];
static GLuint texName;
static GLfloat xequalzero[] = {1.5, 1.5, 1.5, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

//贴图纹理
void makeStripeImage(void)
{
    int j;

    for (j = 0; j < stripeImageWidth; j++) {
        stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
        stripeImage[4*j+2] = (GLubyte) ((j>4) ? 255 : 0);
        stripeImage[4*j+4] = (GLubyte) 0;
        stripeImage[4*j+5] = (GLubyte) 255;
    }
}

//初始化函数
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    // 定义光源
    GLfloat light_position[] = { -200.0,250.0,400.0,0.0 };  // （点）光源的位置
    GLfloat light_ambient[] = { 0.1f,0.1f,0.1f,1.0f };  // 环境光
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 漫反射光，白色
    GLfloat light_specular[] = { 0.9f,0.4f,0.6f,1.0f };  // 镜面反射光，稍浅的棕色
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//指定光源的位置
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);//光源中的环境光强度
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//光源中的散射光强度
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//材质属性中的镜面反射光

    // 开启光源
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    makeStripeImage();//纹理映射函数
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_1D, texName);

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);

    /*设置纹理和物体表面颜色处理方式*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//和物体表面颜色做与运算

    /*设置自动生成纹理坐标的计算方式*/
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;

    //一维纹理，只有S坐标
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//整形形式
    glTexGenfv(GL_S, currentPlane, currentCoeff);//向量形式

    glEnable(GL_TEXTURE_GEN_S);//激活s坐标的纹理坐标生成
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
}

//绘制图形函数
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix ();
    glRotatef(-70.0, 0.0, 0.0, 1.0);//设置茶壶的角度
    glBindTexture(GL_TEXTURE_1D, texName);
    glutSolidTeapot(2.0);//绘制茶壶
    glPopMatrix ();

    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    glFlush();
}

//修正窗内的图形显示函数
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-3.5, 3.5, -3.5*(GLfloat)h/(GLfloat)w,
                 3.5*(GLfloat)h/(GLfloat)w, -3.5, 3.5);
    else
        glOrtho (-3.5*(GLfloat)w/(GLfloat)h,
                 3.5*(GLfloat)w/(GLfloat)h, -3.5, 3.5, -3.5, 3.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//主函数，实现功能函数的调用与图形的显示
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);//设置窗口大小为400x400
    glutInitWindowPosition(100, 100);//设置窗口的位置
    glutCreateWindow (argv[0]);//创建窗口
    init ();//初始化操作
    glutDisplayFunc(display);//绘制图形
    glutReshapeFunc(reshape);//修正窗内的图形显示
    glutMainLoop();//事件处理循环

    return 0;
}
