#include<iostream>
#include<unistd.h>
#include<vector>
#include<GL/glut.h>

#include"color.h" //predefine custom colors library in same directory
#include"plotfunc.h"
#include"getfunc.h"
#include"transformation.h"
#include"textrender.h"
#include"fillcolor.h"

#define Debug
#ifdef Debug
#define print(x) std::cout<<x<<std::endl
#else
#define print(x)
#endif

int window_size[]={720,1024};//Size of Window {height,width}
// int viewport_size[]={650,650};//Size of Viewport {height,width}

void init(std::vector<double> color,int alpha=1.0){
    // gluOrtho2D(0,window_size[1],0,window_size[0]);//origin center [left,right,bottom,top]
    gluOrtho2D(0,window_size[1],0,window_size[0]);//origin left bottom

    glClearColor(color[0], color[1], color[2], alpha); //Window Background Colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}
void reshape_callback(int w, int h){
    // glViewport(0,0,(GLsizei) viewport_size[1],(GLsizei) viewport_size[0]);//[x,y,width,height] for fix vieewport
    glViewport(0,0,(GLsizei) w,(GLsizei) h);//[x,y,width,height] for variable viewport
    print("Viewport - ("<<w<<","<<h<<")");
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void mouse_callback(int button, int state, int x, int y){
    y = window_size[0]-y;//origin left bottom
    print("Mouse Button "<<button<<" ["<<x<<","<<y<<"] "<<state);
    // if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){y = window_size[0]-y;print("Pointer - ("<<x<<","<<y<<")");}
    // else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){}
    // else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){}
    // else if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP){}
}
void keyboard_callback(unsigned char key,int x, int y){//x,y mouse location when Key is pressed
    print("Keyboard - "<<key<<", ["<<x<<","<<y<<"]");
}

void display(void){
    print("Helloworld");
    plotPolygon(green,{ {0,0},{100,0},{100,100},{0,100} });
    plotPolygon(green,translate({ {0,0},{100,0},{100,100},{0,100} },{150,150}));
    for(int i=32;i<128;i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,i);
    // for(int i=32;i<128;i++) glutStrokeCharacter(GLUT_STROKE_ROMAN,i);
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(window_size[1],window_size[0]);
    // glutInitWindowPosition(100, 100);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)-window_size[1]-100, -100);
    // glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_size[1])/2,(glutGet(GLUT_SCREEN_HEIGHT)-window_size[0])/2);
    glutCreateWindow("Experimental Tab1");
    glutDisplayFunc(display);
    init(steelblue);
    glutReshapeFunc(reshape_callback);
    glutMouseFunc(mouse_callback);
    glutKeyboardFunc(keyboard_callback);
    glutMainLoop();
    return 0;
}