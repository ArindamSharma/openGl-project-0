#ifndef CUSTOM_PLOT
#define CUSTOM_PLOT

#ifndef _GLIBCXX_MATH_H
#include<math.h>
#endif

#ifndef PI
#define PI 3.14159265 //Value of PI
#endif

#ifndef deg
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)
#endif

#ifndef _GLIBCXX_VECTOR
#include<vector>
#endif

#ifndef CUSTOM_COLORS
#include"color.h"
#endif

#ifndef __GLUT_H__
#include<GL/glut.h>
#endif

// The function plot uses Gl premitives Such as 
// GL_POINTS, 
// GL_LINES, GL_LINES_STRIP, GL_LINES_LOOP, 
// GL_POLYGON, 
// GL_TRINAGLES, GL_TRINAGLES_STRIP, GL_TRINAGLES_FAN, 
// GL_QUADS, GL_QUADS_STRIP .etc
void plot(GLenum mode,std::vector<std::pair<double,double>> pointsArray,std::vector<double> color=black){
    glBegin(mode);//rect outline
        glColor3d(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i].first,pointsArray[i].second);
        }
    glEnd();
}

/* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
void plotPoint(std::vector<double> color,std::vector<std::pair<double,double>> pointsArray,double point_size=5){
    glPointSize(point_size);
    glBegin(GL_POINTS);//rect outline
        glColor3d(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i].first,pointsArray[i].second);
        }
    glEnd();
}
/* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
void plotLine(std::vector<double> color,std::vector<std::pair<double,double>> pointsArray,double line_width=5){
    glLineWidth(line_width);
    glBegin(GL_LINES);//rect outline
        glColor3d(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i].first,pointsArray[i].second);
            // glVertex2fv((GLfloat *)&pointsArray[i]);
        }
    glEnd();
}
/* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
void plotLineLoop(std::vector<double> color,std::vector<std::pair<double,double>> pointsArray,double line_width=5){
    glLineWidth(line_width);
    glBegin(GL_LINE_LOOP);//rect outline
        glColor3d(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i].first,pointsArray[i].second);
            // glVertex2fv((GLfloat *)&pointsArray[i]);
        }
    glEnd();
}
/* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
void plotPolygon(std::vector<double> color,std::vector<std::pair<double,double>> pointsArray){
    glBegin(GL_POLYGON);//rect outline
        glColor3d(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i].first,pointsArray[i].second);
        }
    glEnd();
}
/* This function plots the Boundary Box for the given figure */
void plotBoundary_box(std::vector<std::pair<double,double>> myfigure,double line_width=5){
    
    double min_x=myfigure[0].first,
    min_y=myfigure[0].second,
    max_x=myfigure[0].first,
    max_y=myfigure[0].second;

    for(int i=0;i<myfigure.size();i++){//for x
        if(myfigure[i].first<min_x){min_x=myfigure[i].first;}
        if(myfigure[i].first>max_x){max_x=myfigure[i].first;}
        if(myfigure[i].second<min_y){min_y=myfigure[i].second;}
        if(myfigure[i].second>max_y){max_y=myfigure[i].second;}
    }
    // // bounding Box
    plotLineLoop(blue,{
        {max_x,max_y},
        {min_x,max_y},

        {min_x,min_y},
        {max_x,min_y}
    },line_width);
}
void plotPoint_single(std::vector<double> color,double x,double y,double stepsize){
    double half=(stepsize/2);
    plotPolygon(color,{
            {x-half,y-half},
            {x-half,y+half},
            {x+half,y+half},
            {x+half,y-half}
        });
}
void plotPoint_quad(std::vector<double> color,std::pair<double,double> origin, double x,double y, double stepsize){
    plotPoint_single(color,x+origin.first,y+origin.second,stepsize);
    plotPoint_single(color,-x+origin.first,-y+origin.second,stepsize);
    plotPoint_single(color,-x+origin.first,y+origin.second,stepsize);
    plotPoint_single(color,x+origin.first,-y+origin.second,stepsize);
}
void plotLine_DDA(std::vector<double> color,std::pair<double,double> p1,std::pair<double,double> p2,double stepsize=1){
    /*Drawing line using DDA algorithm in and only for first octate*/
    double slope=(p2.second-p1.second)/(p2.first-p1.first);
    int x=round(p1.first),y=round(p1.second);
    double xf=p1.first,yf=p1.second;
    
    plotPoint_single(color,x,y,stepsize);
    if(fabs(slope)<=1){
        while(x<p2.first){
            x=x+stepsize;//stepsize shoudouble be 1
            yf=y+slope*stepsize;//stepsize shoudouble be 1
            y=round(yf);
            plotPoint_single(color,x,y,stepsize);
        }
    }
    else{
        while(y<p2.second){
            y=y+stepsize;//stepsize shoudouble be 1
            xf=x+(1.0/slope)*stepsize;//stepsize shoudouble be 1
            x=round(xf);
            plotPoint_single(color,x,y,stepsize);
        }
    }
}
void plotLine_MLD(std::vector<double> color,std::vector<double> p1,std::vector<double> p2,double stepsize){
    /*Drawing line using MLD in and only for first octate*/
    double x=p1[0],y=p1[1];
    double dy=p2[1]-p1[1],dx=p2[0]-p1[0];
    double d=2*dy-dx;
    double dE=(2*dy)*stepsize;
    double dNE=2*(dy-dx)*stepsize;
    // plot
    plotPoint_single(color,x,y,stepsize);
    while (x<p2[0]){
        if(d<=0){
            d=d+dE;//  (/_\d)E = 2dy and stepsize shoudouble be 1
        }
        else{
            d=d+(dNE);//  (/_\d)NE = 2(dy-dx)and stepsize shoudouble be 1
            y=y+(1*stepsize);//and stepsize shoudouble be 1
        }
        x=x+(1*stepsize);//and stepsize shoudouble be 1
        // plot
        plotPoint_single(color,x,y,stepsize);
    }
}
void plotLine_MLD_modified(std::vector<double> color,std::vector<double> p1,std::vector<double> p2,double stepsize,std::vector<double> toggler){
    /*Drawing line using MLD in any one octate based on toggle variable*/
    double x=p1[0],y=p1[1];
    double dy=p2[1]-p1[1],dx=p2[0]-p1[0];
    double d=2*dy-dx;
    double dE=(2*dy)*stepsize;
    double dNE=2*(dy-dx)*stepsize;
    // plot
    plotPoint_single(color,(toggler[0]*x+toggler[1]*y),(toggler[2]*x+toggler[3]*y),stepsize);
    while (x<p2[0]){
        if(d<=0){
            d=d+dE;//  (/_\d)E = 2dy and stepsize shoudouble be 1
        }
        else{
            d=d+(dNE);//  (/_\d)NE = 2(dy-dx)and stepsize shoudouble be 1
            y=y+(1*stepsize);//and stepsize shoudouble be 1
        }
        x=x+(1*stepsize);//and stepsize shoudouble be 1
        // plot
        plotPoint_single(color,(toggler[0]*x+toggler[1]*y),(toggler[2]*x+toggler[3]*y),stepsize);
    }
}
void swap(double &a,double &b){int temp=a;a=b;b=temp;};
void plotLine_MLD_all(std::vector<double> color,std::vector<double> p1,std::vector<double> p2,double stepsize){
    /*Drawing line using MLD in any octates*/
    double m=(p2[1]-p1[1])/(p2[0]-p1[0]);
    if(m<=1 && m>=0 && p1[0]<p2[0]){
        plotLine_MLD_modified(color,p1,p2,stepsize,{1,0,0,1}); // plot x,y
    }//octate 1
    else if(m>1 && p1[1]<p2[1]){
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,1,1,0}); // plot y,x
    }//octate 2
    else if(m<-1 && p1[1]<p2[1]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,-1,1,0});// plot -y,x
    }//octate 3
    else if(m<=0 && m>=-1 && p2[0]<p1[0]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        plotLine_MLD_modified(color,p1,p2,stepsize,{-1,0,0,1});// plot -x,y
    }//octate 4
    else if(m<=1 && m>0 && p2[0]<p1[0]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        p1[1]=-p1[1];p2[1]=-p2[1];
        plotLine_MLD_modified(color,p1,p2,stepsize,{-1,0,0,-1});// plot -x,-y
    }//octate 5
    else if(m>1 && p2[1]<p1[1]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        p1[1]=-p1[1];p2[1]=-p2[1];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,-1,-1,0});// plot -y,-x
    }//octate 6
    else if(m<-1 && p2[1]<p1[1]){
        p1[1]=-p1[1];p2[1]=-p2[1];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,1,-1,0});// plot y,-x
    }//octate 7
    else if(m<0 && m>=-1 && p1[0]<p2[0]){
        p1[1]=-p1[1];p2[1]=-p2[1];
        plotLine_MLD_modified(color,p1,p2,stepsize,{1,0,0,-1});// plot x,-y
    }//octate 8
}
void plotLine_custom(std::pair<double,double> p1,std::pair<double,double> p2,std::vector<double> color,double stepsize,double precision){
    int c=0;
    double slope=(p2.second-p1.second)/(p2.first-p1.first);
    double prec=(stepsize*precision);
    if(p1.first==p2.first){
        swap(p1.first,p1.second);
        swap(p2.first,p2.second);
        c++;
    }
    for(double i=(p1.first);i<(p2.first);i+=precision/10){
        double x=i;
        double y=slope*i+( p1.second-(slope*p1.first) );
        if(c>0){swap(x,y);}
        plotPolygon(color,{
            {round(x/prec)*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
            {round(x/prec)*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
        });
    }
}
void plotCircle_MLD(std::vector<double> color,std::vector<double> center,double radius,double stepsize){
        // only for 2 octant
    double x=0,y=radius,d=1-radius;
    // draw circle
    plotPoint_single(color,x,y,stepsize);
    while (y>x){
        if(d<0){
            d=d+2*x+3;
        }
        else{
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x=x+1;
        // draw circle
        plotPoint_single(color,x,y,stepsize);
    }
}
void plotCircle_MLD_modified(std::vector<double> color,std::pair<double,double> center,double radius,double stepsize,std::vector<double> toggler){
        // only for 2 octant
    double x=0,y=radius,d=1-radius;
    // draw circle
    plotPoint_single(color,
    (toggler[0]*x+toggler[1]*y+   (abs(toggler[0])*center.first+abs(toggler[1])*center.second)  ),
    (toggler[2]*x+toggler[3]*y+   (abs(toggler[2])*center.first+abs(toggler[3])*center.second)  ),
    stepsize);
    while (y>x){
        if(d<0){
            d=d+2*x+3;
        }
        else{
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x=x+1;
        // draw circle
        plotPoint_single(color,
        (toggler[0]*x+toggler[1]*y+   (abs(toggler[0])*center.first+abs(toggler[1])*center.second)  ),
        (toggler[2]*x+toggler[3]*y+   (abs(toggler[2])*center.first+abs(toggler[3])*center.second)  ),
        stepsize);
    }
}
void plotCircle_MLD_all(std::vector<double> color,std::pair<double,double> center,double radius,double stepsize){
    
    plotCircle_MLD_modified(color,center,radius,stepsize,{0,1,1,0});//1 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{1,0,0,1});//2 octate

    plotCircle_MLD_modified(color,center,radius,stepsize,{-1,0,0,1});// 3 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{0,-1,1,0});// 4 octate

    plotCircle_MLD_modified(color,center,radius,stepsize,{0,-1,-1,0});// 5 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{-1,0,0,-1});// 6 octate

    plotCircle_MLD_modified(color,center,radius,stepsize,{1,0,0,-1});// 7 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{0,1,-1,0});// 8 octate
}
void plotEllipse_MLD(std::vector<double> color,std::pair<double,double> center,double a,double b,double stepsize){
    int x=0,y=b;
    int sa=a*a,sb=b*b;
    int d1=sb-sa*b+0.25*sa;
    //draw
    plotPoint_quad(color,center,x,y,stepsize);
    
    while(sa*(y-0.5)>sb*(x+1)){
        if(d1<0){
            d1+=sb*((x<<1)+3);
        }
        else{
            d1+=sb*((x<<1)+3)+sa*(-(y<<1)+2);
            y--;
        }
        x++;
        // draw
        plotPoint_quad(color,center,x,y,stepsize);
        
    }
    int d2=sb*(x+0.5)*(x+0.5)+sa*(y-1)*(y-1)-sa*sb;
    //draw
    plotPoint_quad(color,center,x,y,stepsize);
    
    while(y>0){
        if(d2<0){
            d2+=sb*((x<<1)+2)+sa*(-(y<<1)+3);
            x++;
        }
        else{
            d2+=sb*(-(y<<1)+3);
        }
        y--;
        // draw
        plotPoint_quad(color,center,x,y,stepsize);
    }

}
void plotEllipseCustom(std::vector<double> color,std::pair<double,double> origin, double a,double b ,double precision=0.8,double thick=5){
    for(double i=0;i<360;i+=precision){
        plotPoint(color,{
            {(origin.first+a*cos(i deg)),(origin.second+b*sin(i deg))}
        },thick);
    }
}
void plotCircleCustom(std::vector<double> color,std::pair<double,double> origin, double r ,double precision=0.8,double thick=5){
    for(double i=0;i<360;i+=precision){
        plotPoint(color,{
            {(origin.first+r*cos(i deg)),(origin.second+r*sin(i deg))}
        },thick);
    }
}
void plotSphereCustom(std::vector<double> color,std::pair<double,double> origin,double radius,int vlines=5,int hlines=5,double precision =0.8,double thickness=2.5){
    plotCircleCustom(color,origin,radius,precision,thickness);//circumfrence
    double temp;
    //vertical lines
    if((vlines%2)!=0){//odd
        vlines=(vlines-1)/2;
        plotLine(color,{
                {origin.first+0,origin.second+radius},{origin.first+0,origin.second-radius}
            },thickness/2);//vertical line
        double temp=radius/(vlines+1);
        for(int i=temp;i<radius;i+=temp){
            plotEllipseCustom(color,origin,i,radius,precision,thickness);
        }
    }
    else{
        temp=(2*radius)/(vlines+1);
        for(double i=temp/2;i<radius;i+=temp){
            plotEllipseCustom(color,origin,i,radius,precision,thickness);
        }
    }
    //horizontal lines
    temp=(2*radius)/(hlines+1);
    double sradius=radius*radius;
    for(double y=temp-radius;y<radius;y+=temp){
        double x=sqrt(sradius-(y*y));
        // Line(color,{  {origin.first-x,origin.second+y},{origin.first+x,origin.second+y}   },thickness/2);
        plotEllipseCustom(color,{origin.first,origin.second+y},x,temp/3,precision,thickness);
    }
}


#endif