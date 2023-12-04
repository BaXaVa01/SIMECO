#include <iostream>
#include <random>

#include "pantallacarga3.cpp"
#include "pantallacarga1.cpp"


using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());


    uniform_int_distribution<> dis(1, 2);


    int opcion = dis(gen);


    if (opcion == 1) {
        mainBarra1();

    } else {
        mainP3();

    }

    return 0;
}
