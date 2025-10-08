#include "CounterComponent.hpp"
#include <iostream>


class Counter : Component {
    public:
    void update() override {
        std::cout << count << std::endl;
        count++;
    }
    private:
    int count = 0;
};
