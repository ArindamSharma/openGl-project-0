#ifndef CUSTOM_GET
#define CUSTOM_GET

#ifndef _GLIBCXX_MATH_H
#include<math.h>
#endif

#ifndef _GLIBCXX_VECTOR
#include<vector>
#endif

#ifndef __GLUT_H__
#include<GL/glut.h>
#endif

#define PI 3.14159265 //Value of PI
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)

std::vector<double> getPixelColor(std::pair<double,double> p,double stepsize=1){
    unsigned char pixel[4];
    glReadPixels(p.first,p.second,stepsize,stepsize,GL_RGB,GL_UNSIGNED_BYTE,pixel);
    return {(double)pixel[0],(double)pixel[1],(double)pixel[2]};
}

std::vector<std::pair<double,double>> getCirclePoints(std::pair<double,double> origin,double r,std::pair<double,double> angles,double precision=0.1){
    std::vector<std::pair<double,double>> circlepoints;
    for(double i=angles.first;i<angles.second;i+=precision){
        circlepoints.push_back({(origin.first+r*cos(i deg)),(origin.second+r*sin(i deg))});
    }
    return circlepoints;
}
std::vector<std::pair<double,double>> getEllipsePoints(std::vector<double> origin, double a,double b ,double precision=0.8,double thick=5,bool see=false){
    std::vector<std::pair<double,double>> result;
    for(double i=0;i<360;i+=precision){
        result.push_back({(origin[0]+a*cos(i deg)),(origin[1]+b*sin(i deg))});
    }
    return result;
}

#endif