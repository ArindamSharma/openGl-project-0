#ifndef CUSTOM_TRANSFORM
#define CUSTOM_TRANSFORM

#ifndef _GLIBCXX_MATH_H
#include<math.h>
#endif

#ifndef _GLIBCXX_VECTOR
#include<vector>
#endif

#ifndef __GLUT_H__
#include<GL/glut.h>
#endif
#ifndef PI
#define PI 3.14159265 //Value of PI
#endif

#ifndef deg
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)
#endif

std::vector<std::pair<double,double>> translate(std::vector<std::pair<double,double>> figure,std::pair<double,double> factor){
    std::vector<std::pair<double,double>> f;
    for(int i=0;i<figure.size();i++){
        f.push_back({figure[i].first+factor.first,figure[i].second+factor.second});
    }
    return f;
}
std::pair<double,double> find_center(std::vector<std::pair<double,double>> figure){
    double maxx=figure[0].first;
    double maxy=figure[0].second;
    double minx=figure[0].first;
    double miny=figure[0].second;
    for(int i=0;i<figure.size();i++){
        if(maxx<figure[i].first){maxx=figure[i].first;}
        if(maxy<figure[i].second){maxy=figure[i].second;}
        if(minx>figure[i].first){minx=figure[i].first;}
        if(miny>figure[i].second){miny=figure[i].second;}
    }
    return {minx+((maxx-minx)/2),miny+((maxy-miny)/2)};
}
std::vector<std::pair<double,double>> rotate(std::vector<std::pair<double,double>> figure,double degree,bool origin=false){
    std::vector<std::pair<double,double>> f;
    if(origin){
        for(int i=0 ;i<figure.size();i++){
            f.push_back({
                figure[i].first*cos(degree deg)-figure[i].second*sin(degree deg),
                figure[i].second*cos(degree deg)+figure[i].first*sin(degree deg),
            });
        }
        return f;
    }
    else{
        std::pair<double,double> a=find_center(figure);
        a.first*=-1;a.second*=-1;
        std::vector<std::pair<double,double>> final=translate(figure,a);
        for(int i=0;i<final.size();i++){
            double x=final[i].first,y=final[i].second;
            final[i].first=x*cos(degree deg)-y*sin(degree deg);
            final[i].second=y*cos(degree deg)+x*sin(degree deg);
        }
        return translate(final,find_center(figure));
    }
}
std::vector<std::pair<double,double>> scale(std::vector<std::pair<double,double>> figure,double factor){
    std::pair<double,double> a=find_center(figure);
    a.first*=-1;a.second*=-1;
    std::vector<std::pair<double,double>> f=translate(figure,a);
    for(int i=0;i<f.size();i++){
        f[i].first*=factor;
        f[i].second*=factor;
    }
    f=translate(f,find_center(figure));
    return f;
}
#endif