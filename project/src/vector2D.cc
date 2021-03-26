#include "vector2D.h"
#include<cmath>
namespace csci3081 {

Vector2D::Vector2D(std::vector<float> temp){
    for (int i=0; i < temp.size();i++){
        vec.push_back(temp[i]);
    }
}

Vector2D& Vector2D::operator+(const csci3081::Vector2D& other){
    std::vector<float> sum;

    for (int i=0; i < vec.size();i++){
        sum.push_back(other.vec[i]+vec[i]);
    }

    Vector2D* ret = new Vector2D(sum);
    return *ret;
}

Vector2D& Vector2D::operator-(const csci3081::Vector2D& other){
    std::vector<float> diff;

    for (int i=0; i < vec.size();i++){
        diff.push_back(vec[i]-other.vec[i]);
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

}