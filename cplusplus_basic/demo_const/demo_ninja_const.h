#ifndef _DEMO_NINJA_CONST_H_
#define _DEMO_NINJA_CONST_H_

#include <iostream>

class DemoConst{
    public:
    DemoConst():numA(12){

    }

    virtual ~DemoConst(){

    }

    void ConstSay(std::string word){
        std::cout << word.c_str() << std::endl;
    }

    void ConstEat();

    public:
    int getConstValue(){ return numA;}    //成员函数
    int getConstValue() const{  return numA;}    //常成员函数，不能修改数据成员变量

    private:
    const int numA;    //只能初始化一次
};

#endif