#include "include/dominos.hpp"

void handleDominos() {
    Dominos dominos(9, 9, 10);
    dominos.play();
}

int main(int argc, char** argv) {
    handleDominos();
    return 0;
}