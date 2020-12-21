// This is a Color Filling Algrothm Header
#ifndef CUSTOM_FILL
#define CUSTOM_FILL

#ifndef _GLIBCXX_VECTOR
#include<vector>
#endif

#ifndef CUSTOM_GET
#include"getfunc.h"//getpixelcolor
#endif

#ifndef CUSTOM_PLOT
#include"plotfunc.h"//plotpoint
#endif

// This a Boundary Fill Algrothim for 4 neighbours Only
void fillcolor_BF4(std::pair<double,double> p,std::vector<double> fillcolor,std::vector<double> boundarycolor,double stepsize=1,double thickness=5){
    std::vector<double> color=getPixelColor({p.first,p.second});
    // cout<<(color!=fillcolor && color!=boundarycolor)<<endl;
    bool condition =
    color[0]!=fillcolor[0] && 
    color[1]!=fillcolor[1] && 
    color[2]!=fillcolor[2] &&
    color[0]!=boundarycolor[0] && 
    color[1]!=boundarycolor[1] && 
    color[2]!=boundarycolor[2];
    // if((color!=fillcolor) && (color!=boundarycolor)){
    if(condition){
        plotPoint(fillcolor,{{p.first,p.second}},thickness);//filling desired color
        glFlush();
        fillcolor_BF4({p.first+stepsize,p.second},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF4({p.first-stepsize,p.second},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF4({p.first,p.second+stepsize},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF4({p.first,p.second-stepsize},fillcolor,boundarycolor,stepsize,thickness);
    }
    // cout<<"end"<<endl;
}
// This a Boundary Fill Algrothim for 8 neighbours
void fillcolor_BF8(std::pair<double,double> p,std::vector<double> fillcolor,std::vector<double> boundarycolor,double stepsize=1,double thickness=5){
    std::vector<double> color=getPixelColor({p.first,p.second});
    bool condition =
    color[0]!=fillcolor[0] && 
    color[1]!=fillcolor[1] && 
    color[2]!=fillcolor[2] &&
    color[0]!=boundarycolor[0] && 
    color[1]!=boundarycolor[1] && 
    color[2]!=boundarycolor[2];
    // if((color!=fillcolor) && (color!=boundarycolor)){
    if(condition){
        plotPoint(fillcolor,{{p.first,p.second}} ,thickness);
        glFlush();
        fillcolor_BF8({p.first+stepsize,p.second},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF8({p.first,p.second+stepsize},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF8({p.first-stepsize,p.second},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF8({p.first,p.second-stepsize},fillcolor,boundarycolor,stepsize,thickness);

        fillcolor_BF8({p.first+stepsize,p.second+stepsize},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF8({p.first+stepsize,p.second-stepsize},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF8({p.first-stepsize,p.second+stepsize},fillcolor,boundarycolor,stepsize,thickness);
        fillcolor_BF8({p.first-stepsize,p.second-stepsize},fillcolor,boundarycolor,stepsize,thickness);
    }
}
// This a Flood Fill Algrothim for 8 neighbours
void fillcolor_floodfill(std::pair<double,double> p,std::vector<double> odoublecolor,std::vector<double> newcolor,double stepsize=1,double thickness=5){
    std::vector<double> color=getPixelColor({p.first,p.second});
    bool condition =
    color[0]==odoublecolor[0] && 
    color[1]==odoublecolor[1] && 
    color[2]==odoublecolor[2];
    // if(color==odoublecolor){
    if(condition){
        plotPoint(newcolor,{{p.first,p.second}},thickness);
        glFlush();
        fillcolor_floodfill({p.first+stepsize,p.second},odoublecolor,newcolor,stepsize,thickness);
        fillcolor_floodfill({p.first-stepsize,p.second},odoublecolor,newcolor,stepsize,thickness);
        fillcolor_floodfill({p.first,p.second+stepsize},odoublecolor,newcolor,stepsize,thickness);
        fillcolor_floodfill({p.first,p.second-stepsize},odoublecolor,newcolor,stepsize,thickness);

        fillcolor_floodfill({p.first+stepsize,p.second+stepsize},odoublecolor,newcolor,stepsize,thickness);
        fillcolor_floodfill({p.first+stepsize,p.second-stepsize},odoublecolor,newcolor,stepsize,thickness);
        fillcolor_floodfill({p.first-stepsize,p.second-stepsize},odoublecolor,newcolor,stepsize,thickness);
        fillcolor_floodfill({p.first-stepsize,p.second+stepsize},odoublecolor,newcolor,stepsize,thickness);
    }
}
#endif