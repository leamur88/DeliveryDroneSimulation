#include "vector3D.h"
#include<cmath>
namespace csci3081 {

Vector3D::Vector3D(std::vector<float> temp){
    for (int i=0; i < temp.size();i++){
        vec.push_back(temp[i]);
    }
}


Vector3D& Vector3D::operator+(const csci3081::Vector3D& other){
    std::vector<float> sum;

    for (int i=0; i < vec.size();i++){
        sum.push_back(other.vec[i]+vec[i]);
    }

    Vector3D* ret = new Vector3D(sum);
    return *ret;
}

Vector3D& Vector3D::operator-(const csci3081::Vector3D& other){
    std::vector<float> diff;

    for (int i=0; i < vec.size();i++){
        diff.push_back(vec[i]-other.vec[i]);
    }

    Vector3D* ret = new Vector3D(diff);
    return *ret;

}

Vector3D& Vector3D::operator=(const csci3081::Vector3D& other){
    std::vector<float> temp;

    for (int i=0; i < vec.size();i++){
        temp.push_back(other.vec[i]);
    }

    SetVector(temp);
    return *this;

}

std::vector<float>& Vector3D::GetVector(){
    return vec;
}

void Vector3D::SetVector(std::vector<float> other){
    vec.clear();
    for (int i=0; i < other.size();i++){
        vec.push_back(other[i]);
    }
}

void Vector3D::Normalize(){
    std::vector<float> ret;
    float divisor = 0;

    for (int i=0; i < vec.size();i++){
        divisor += pow(vec[i],2.0);
    }

    for (int i=0; i < vec.size();i++){
        ret.push_back((vec[i]/sqrt(divisor)));
    }

    SetVector(ret);
}

float Vector3D::Magnitude(){
    float ret = 0;

    for (int i=0; i < vec.size();i++){
        ret += pow(vec[i],2.0);
    }

    return sqrt(ret);
}

void Vector3D::Scale(float s){
    for (int i=0; i < vec.size();i++){
        vec[i] *= s;
    }
}


}