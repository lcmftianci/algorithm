clang++ -E demo_ninja_main.cpp -o test.i
clang++ -S test.i -o test.s
clang++ -c test.s -o test.o
clang++ test.o -o test