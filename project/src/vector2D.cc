#include "vector2D.h"
#include<cmath>
namespace csci3081 {

Vector2D::Vector2D(){}
Vector2D::Vector2D(std::vector<float> temp){
    for (int i=0; i < temp.size();i++){
        vec.push_back(temp[i]);
    }
}

Vector2D& Vector2D::operator+(const csci3081::Vector2D& other){
    std::vector<float> sum;

    for (int i=0; i < vec.size();i++){
        if (i!=1){
            sum.push_back(other.vec[i]+vec[i]);
        }
        else{
            sum.push_back(vec[i]);
        }
    }

    Vector2D* ret = new Vector2D(sum);
    return *ret;
}

Vector2D& Vector2D::operator-(const csci3081::Vector2D& other){
    std::vector<float> diff;

    for (int i=0; i < vec.size();i++){
        if (i!=1){
            diff.push_back(vec[i]-other.vec[i]);
        }
        else{
            diff.push_back(vec[i]);
        }
        
    }

    Vector2D* ret = new Vector2D(diff);
    return *ret;

}

Vector2D& Vector2D::operator=(const csci3081::Vector2D& other){
    std::vector<float> temp;

    for (int i=0; i < vec.size();i++){
        temp.push_back(other.vec[i]);
    }

    SetVector(temp);
    return *this;
}

std::vector<float>& Vector2D::GetVector(){
    return vec;
}

void Vector2D::SetVector(std::vector<float> other){
    vec.clear();
    for (int i=0; i < other.size();i++){
        vec.push_back(other[i]);
    }
}
void Vector2D::Normalize(){
    std::vector<float> ret;
    float divisor = 0;

    for (int i=0; i < vec.size();i++){
        if (i!=1){
            divisor += pow(vec[i],2.0);
        }
        
    }

    for (int i=0; i < vec.size();i++){
        if (i!=1){
            ret.push_back((vec[i]/sqrt(divisor)));
        }
        else{
            ret.push_back(0);
        }
        
    }

    SetVector(ret);
}

float Vector2D::Magnitude(){
    float ret = 0;

    for (int i=0; i < vec.size();i++){
        if (i!=1){
            ret += pow(vec[i],2.0);
        }
    }
    return sqrt(ret);
}

void Vector2D::Scale(float s){
    for (int i=0; i < vec.size();i++){
        if (i!=1){
            vec[i] *= s;
        }
    }
}

float Vector2D::Distance(std::vector<float> vector1, std::vector<float> vector2){
  return sqrt ( pow((vector1[0] - vector2[0]), 2) +  pow((vector1[2] - vector2[2]), 2));
}

}