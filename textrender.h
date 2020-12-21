#ifndef CUSTOM_TEXT_RENDERING
#define CUSTOM_TEXT RENDERING

#ifndef _GLIBCXX_STRING
#include<string>
#endif

#ifndef _GLIBCXX_IOSTREAM
#include<iostream>
#endif

#ifndef _GLIBCXX_VECTOR
#include<vector>
#endif

#ifndef _GLIBCXX_MATH_H
#include<math.h>
#endif

#ifndef CUSTOM_PLOT
#include"plotfunc.h"//plotpoint
#endif

#ifndef CUSTOM_GET
#include"getfunc.h"//getpixelcolor
#endif

#ifndef CUSTOM_TRANSFORM
#include"transformation.h"//plotpoint
#endif

#ifndef PI
#define PI 3.14159265 //Value of PI
#endif

#ifndef deg
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)
#endif

class LinearEquation{
private:
    /* data */
public:
    double m,c;
    LinearEquation(std::vector<double> p1,std::vector<double> p2){
        m=(p2[1]-p1[1])/(p2[0]-p1[0]);
        c=p1[1]-(m*p1[0]);
    }
    LinearEquation(double a,double b,double c){
        // ax+by+c=0
        m=-(a/b);
        c=-(c/b);
    }
    LinearEquation(std::vector<double> p,double slope){
        // ax+by+c=0
        m=slope;
        c=p[1]-(m*p[0]);
    }
    double y_value(double x){return m*x+c;}
    double x_value(double y){return (y-c)/m;}
    double Func(double x,double y){return (m*x)+c-y;}
};
std::vector<std::pair<double,double>> font_letter(char l,double precision);

void textRendering(std::string str,std::vector<double> location,std::vector<double> color,double mysize=8){
    double strsize=str.size();
    double space_btw_letter=6;
    strsize=-(strsize*mysize*space_btw_letter)/2.0;
    for(int i=0;i<str.size();i++){
        strsize+=mysize*space_btw_letter;
        double fontthickness=mysize/2;
        std::vector<std::pair<double,double>> l=scale(font_letter(str[i],1.25/mysize),mysize);
        std::vector<double> origin={location[0]*mysize+strsize,location[1]*mysize};
        // for(ll j=0;j<l.size();j++){//letter outline
        //     plotPolygon(black, getcirclepoints({origin[0]+l[j][0],origin[1]+l[j][1]},fontthickness,{0,360},0.5) );
        //     glFlush();
        // }
        for(int j=0;j<l.size();j++){//actual letter
            plotPolygon(color, getCirclePoints({origin[0]+l[j].first,origin[1]+l[j].second},fontthickness-mysize/10,{0,360},0.5) );
            glFlush();
        }
        // glFlush();
    }
}


std::vector<std::pair<double,double>> font_letter(char l,double precision=0.1){
    std::vector<std::pair<double,double>> letter;
    int temp=l;
    if(temp==65){
        // cout<<"the Letter used is A"<<endl;
        LinearEquation a1({2,0},{-2,0});//horizontal
        LinearEquation a2({3,-2},{0,4});//right
        LinearEquation a3({-3,-2},{0,4});//left
        for(double i=-2;i<2;i+=precision*2){ letter.push_back({i,a1.y_value(i)});}
        for(double i=0;i<3;i+=precision){ letter.push_back({i,a2.y_value(i)});}
        for(double i=-3;i<0;i+=precision){ letter.push_back({i,a3.y_value(i)});}
        return letter;
    }
    else if(temp==66){
        // cout<<"the Letter used is B"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(double x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(double i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper
        for(double x=0;x>-2;x-=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(double i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(-0.5+1.5*sin(i deg))});}//semicircle bottom
        for(double x=0;x>-2;x-=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        return letter;
    }
    else if(temp==67){
        // cout<<"the Letter used is C"<<endl;
        for(double i=45;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper
        for(double y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//left
        for(double i=180;i<315;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        return letter;
    }
    else if(temp==68){
        // cout<<"the Letter used is D"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(double x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(double i=90;i>0;i-=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle
        for(double y=2;y>0;y-=precision*2){ letter.push_back({2,y});}//right
        for(double i=0;i>-90;i-=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle
        for(double x=0;x>-2;x-=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        return letter;
    }
    else if(temp==69){
        // cout<<"the Letter used is E"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(double x=-2;x<1.5;x+=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        return letter;
    }
    else if(temp==70){
        // cout<<"the Letter used is F"<<endl;
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        return letter;
    }
    else if(temp==71){
        // cout<<"the Letter used is G"<<endl;
        for(double i=23;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper
        for(double y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(double i=180;i<337;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        double lx=letter[letter.size()-1].first,ly=letter[letter.size()-1].second;
        for(double y=ly;y<0.5;y+=precision*2){ letter.push_back({lx,y});}// vertical right
        for(double x=lx;x>0;x-=precision*2){ letter.push_back({x,0.5});}//horizontal middle
        return letter;
    }
    else if(temp==72){
        // cout<<"the Letter used is H"<<endl;
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,1});}//horizontal
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({2,y});}//right
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        // print2D(letter);
        return letter;
    }
    else if(temp==73){
        // cout<<"the Letter used is I"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({0,y});}//vertical
        return letter;
    }
    else if(temp==74){
        // cout<<"the Letter used is J"<<endl;
        for(double i=180;i<360;i+=precision*75){letter.push_back({(1+1*cos(i deg)),(-1+1*sin(i deg))});}//semicircle
        for(double y=-1;y<4;y+=precision*2){ letter.push_back({2,y});}//right vertical
        return letter;
    }
    else if(temp==75){
        // cout<<"the Letter used is K"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-1.5,y});}//vertical
        std::vector<double> p1={1.5,4},p2={1.5,-2},p3={-1.25,1};
        LinearEquation a2(p1,p3);//right
        LinearEquation a3(p2,p3);//left
        for(double x=p1[0];x>p3[0];x-=precision){ letter.push_back({x,a2.y_value(x)});}//top
        for(double x=p3[0];x<p2[0];x+=precision){ letter.push_back({x,a3.y_value(x)});}//bottom
        return letter;
    }
    else if(temp==76){
        // cout<<"the Letter used is L"<<endl;
        for(double y=4;y>-2;y-=precision*2){ letter.push_back({-2,y});}//left
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,-2});}//horizontal top
        return letter;
    }
    else if(temp==77){
        // cout<<"the Letter used is M"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        std::vector<double> p1={-2,4},p3={0,0},p2={2,4};
        LinearEquation a2(p1,p3);//left
        LinearEquation a3(p3,p2);//right
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        for(double x=p3[0];x<p2[0];x+=precision){ letter.push_back({x,a3.y_value(x)});}//right
        for(double y=4;y>-2;y-=precision*2){ letter.push_back({2,y});}//right
        return letter;
    }
    else if(temp==78){
        // cout<<"the Letter used is N"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        std::vector<double> p1={-2,4},p3={2,-2};
        LinearEquation a2(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({2,y});}//right
        return letter;
    }
    else if(temp==79){
        // cout<<"the Letter used is O"<<endl;
        for(double i=90;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper left
        for(double y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(double i=180;i<360;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        for(double y=0;y<2;y+=precision*2){ letter.push_back({2,y});}//vertical right
        for(double i=0;i<90;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
        return letter;
    }
    else if(temp==80){
        // cout<<"the Letter used is P"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(double x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(double i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper
        for(double x=0;x>-2;x-=precision*2){ letter.push_back({x,1});}//horizontal middle
        return letter;
    }
    else if(temp==81){
        // cout<<"the Letter used is Q"<<endl;
        for(double i=90;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper left
        for(double y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(double i=180;i<360;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        for(double y=0;y<2;y+=precision*2){ letter.push_back({2,y});}//vertical right
        for(double i=0;i<90;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
        for(double i=225;i<270;i+=precision*75){letter.push_back({(2+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle upper right
        return letter;
    }
    else if(temp==82){
        // cout<<"the Letter used is R"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(double x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(double i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper
        for(double x=0;x>-2;x-=precision*2){ letter.push_back({x,1});}//horizontal middle
        std::vector<double> p1={0,1},p3={2,-2};
        LinearEquation a2(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        
        return letter;
    }
    else if(temp==83){
        // cout<<"the Letter used is S"<<endl;
        for(double i=45;i<90;i+=precision*75){letter.push_back({(0.5+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
        for(double x=0.5;x>-0.5;x-=precision*2){ letter.push_back({x,4});}//horizontal top
        for(double i=90;i<270;i+=precision*75){letter.push_back({(-0.5+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper left
        for(double x=-0.5;x<0.5;x+=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(double i=90;i>-90;i-=precision*75){letter.push_back({(0.5+1.5*cos(i deg)),(-0.5+1.5*sin(i deg))});}//semicircle lower right
        for(double x=0.5;x>-0.5;x-=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        for(double i=270;i>202.5;i-=precision*75){letter.push_back({(-0.5+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle lower left
        return letter;
    }
    else if(temp==84){
        // cout<<"the Letter used is T"<<endl;
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({0,y});}//left
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top
        return letter;
    }
    else if(temp==85){
        // cout<<"the Letter used is U"<<endl;
        for(double y=4;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(double i=180;i<360;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        for(double y=0;y<4;y+=precision*2){ letter.push_back({2,y});}//vertical right
        return letter;
    }
    else if(temp==86){
        // cout<<"the Letter used is V"<<endl;
        std::vector<double> p1={-2,4},p3={0,-2};
        LinearEquation a2(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        p3={2,4},p1={0,-2};
        LinearEquation a1(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a1.y_value(x)});}//left
        return letter;
    }
    else if(temp==87){
        // cout<<"the Letter used is W"<<endl;
        // letter=rotate(font_letter('M',precision),180);
        for(double y=4;y>-2;y-=precision*2){ letter.push_back({-2,y});}//left
        std::vector<double> p1={-2,-2},p3={0,2},p2={2,-2};
        LinearEquation a2(p1,p3);//left
        LinearEquation a3(p3,p2);//right
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        for(double x=p3[0];x<p2[0];x+=precision){ letter.push_back({x,a3.y_value(x)});}//right
        for(double y=-2;y<4;y+=precision*2){ letter.push_back({2,y});}//right
        return letter;
    }
    else if(temp==88){
        // cout<<"the Letter used is X"<<endl;
        std::vector<double> p1={-2,4},p3={2,-2};
        LinearEquation a2(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        p3={2,4},p1={-2,-2};
        LinearEquation a1(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a1.y_value(x)});}//left
        return letter;
    }
    else if(temp==89){
        // cout<<"the Letter used is Y"<<endl;
        std::vector<double> p1={-2,4},p3={0,1};
        LinearEquation a2(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        p3={2,4},p1={0,1};
        LinearEquation a1(p1,p3);//left
        for(double x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a1.y_value(x)});}//left
        
        for(double y=-2;y<1;y+=precision*2){ letter.push_back({0,y});}//left
        return letter;
    }
    else if(temp==90){
        // cout<<"the Letter used is Z"<<endl;
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top
        std::vector<double> p1={2,4},p3={-2,-2};
        LinearEquation a1(p1,p3);//left
        for(double x=p1[0];x>p3[0];x-=precision){ letter.push_back({x,a1.y_value(x)});}//left
        for(double x=-2;x<2;x+=precision*2){ letter.push_back({x,-2});}//horizontal top
        return letter;
    }

    
    else if(temp==97){
        // cout<<"the Letter used is a"<<endl;
        return letter;
    }
    else if(temp==98){
        // cout<<"the Letter used is b"<<endl;
        return letter;
    }
    else if(temp==99){
        // cout<<"the Letter used is c"<<endl;
        return letter;
    }
    else if(temp==100){
        // cout<<"the Letter used is d"<<endl;
        return letter;
    }
    else if(temp==101){
        // cout<<"the Letter used is e"<<endl;
        return letter;
    }
    else if(temp==102){
        // cout<<"the Letter used is f"<<endl;
        return letter;
    }
    else if(temp==103){
        // cout<<"the Letter used is g"<<endl;
        return letter;
    }
    else if(temp==104){
        // cout<<"the Letter used is h"<<endl;
        return letter;
    }
    else if(temp==105){
        // cout<<"the Letter used is i"<<endl;
        return letter;
    }
    else if(temp==106){
        // cout<<"the Letter used is j"<<endl;
        return letter;
    }
    else if(temp==107){
        // cout<<"the Letter used is k"<<endl;
        return letter;
    }
    else if(temp==108){
        // cout<<"the Letter used is l"<<endl;
        return letter;
    }
    else if(temp==109){
        // cout<<"the Letter used is m"<<endl;
        return letter;
    }
    else if(temp==110){
        // cout<<"the Letter used is n"<<endl;
        return letter;
    }
    else if(temp==111){
        // cout<<"the Letter used is o"<<endl;
        return letter;
    }
    else if(temp==112){
        // cout<<"the Letter used is p"<<endl;
        return letter;
    }
    else if(temp==113){
        // cout<<"the Letter used is q"<<endl;
        return letter;
    }
    else if(temp==114){
        // cout<<"the Letter used is r"<<endl;
        return letter;
    }
    else if(temp==115){
        // cout<<"the Letter used is s"<<endl;
        return letter;
    }
    else if(temp==116){
        // cout<<"the Letter used is t"<<endl;
        return letter;
    }
    else if(temp==117){
        // cout<<"the Letter used is u"<<endl;
        return letter;
    }
    else if(temp==118){
        // cout<<"the Letter used is v"<<endl;
        return letter;
    }
    else if(temp==119){
        // cout<<"the Letter used is w"<<endl;
        return letter;
    }
    else if(temp==120){
        // cout<<"the Letter used is x"<<endl;
        return letter;
    }
    else if(temp==121){
        // cout<<"the Letter used is y"<<endl;
        return letter;
    }
    else if(temp==122){
        // cout<<"the Letter used is z"<<endl;
        return letter;
    }
    else{
        std::cout<<"Error in Charactor"<<std::endl;
        exit(1);
    }
}




#endif