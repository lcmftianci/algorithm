#include <iostream>
#include "demo_ninja_const.h"

extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
}

int main(int argc, char* argv[])
{
    std::cout << "hello ninja hello clang" << std::endl;

    auto dc = new DemoConst();
    dc->ConstSay("const say");

    return 0;
}