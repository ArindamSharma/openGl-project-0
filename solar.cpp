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

#ifndef CUSTOM_COLORS
#include"color.h"
#endif

#ifndef CUSTOM_PLOT
#include"plotfunc.h"//plotpoint
#endif

#ifndef PI
#define PI 3.14159265 //Value of PI
#endif

#ifndef deg
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)
#endif

#define globalprec 1000
#define ldrand (double)(rand()%globalprec)+(1.0/(double)(rand()%globalprec))
#define intrand (rand()%globalprec)

template <typename T>
T customScaling(T x,std::pair<double,double> inputRange,std::pair<double,double> outputRange){
    ld tmp1=-inputRange.first;
    // inputRange.first+=tmp1;
    inputRange.second+=tmp1;
    ld tmp2=-outputRange.first;
    // outputRange.first+=tmp2;
    outputRange.second+=tmp2;
    x+=tmp1;
    x=x/(inputRange.second);
    x*=outputRange.second;
    x-=tmp2;
    return x;
    // return ((x/(inputRange.second-inputRange.first))*(outputRange.second-outputRange.first))+outputRange.first;
}


void solarsystem(void){
    std::cout.precision(10);
    srand(time(0));
    double earthorbit_a=400,earthorbit_b=50;
    double moonorbit_a=100,moonorbit_b=20;
    double sunradius=100,earthradius=50,moonradius=20;
    double rotation_earth_wrt_sun=10;
    double rate_of_rotation_moon_wrt_earth=3;
    double earth_to_moon_angle=0;
    
        // Array2D(ld) starset1,starset2,starset3;
        // for(int i=0;i<intrand;i++){
        //     starset1.push_back({ldrand,ldrand}); starset2.push_back({ldrand,ldrand}); starset3.push_back({ldrand,ldrand});
        //     starset1.push_back({-ldrand,ldrand}); starset2.push_back({-ldrand,ldrand}); starset3.push_back({-ldrand,ldrand});
        //     starset1.push_back({-ldrand,-ldrand}); starset2.push_back({-ldrand,-ldrand}); starset3.push_back({-ldrand,-ldrand});
        //     starset1.push_back({ldrand,-ldrand}); starset2.push_back({ldrand,-ldrand}); starset3.push_back({ldrand,-ldrand});
            
        // }//stars
        
    for(double rot=0;rot<360*rotation_earth_wrt_sun;rot+=1/rate_of_rotation_moon_wrt_earth){
        double x=(earthorbit_a*cos(rot deg)),y=(earthorbit_b*sin(rot deg));
        double sun_to_earth_angle=(int)rot%360;
        std::vector<double> mooncolor=grey;
        std::vector<double> earthcolor=green;
        std::vector<double> suncolor=rgb(207, 182, 0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0;i<intrand;i++){plotPoint(white,{{ldrand,ldrand},{-ldrand,ldrand},{-ldrand,-ldrand},{ldrand,-ldrand}},2);}//stars
        plotEllipseCustom(darkgray,{0,0},earthorbit_a,earthorbit_b,0.8,0.5);//sun orbit
        if(sun_to_earth_angle>0 && sun_to_earth_angle<=90){
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius/2})
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius/2})
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
            plotSphereCustom(suncolor,{0,0},sunradius,16,16,0.8,2);//sun
        }
        else if(sun_to_earth_angle>90 && sun_to_earth_angle<=180){
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
            plotSphereCustom(suncolor,{0,0},sunradius,16,16,0.8,2);//sun
        }
        else if(sun_to_earth_angle>180 && sun_to_earth_angle<=270){
            plotSphereCustom(suncolor,{0,0},sunradius,16,16,0.8,1.5);//sun
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;

        }
        else if(sun_to_earth_angle>270 && sun_to_earth_angle<=360){
            plotSphereCustom(suncolor,{0,0},sunradius,16,16,0.8,2);//sun
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                plotSphereCustom(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
                plotSphereCustom(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
        }
        glFlush();
    }
}
