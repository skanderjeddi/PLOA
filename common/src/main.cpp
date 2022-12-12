#include "../include/common.hpp"
#include "../../dominos/include/dominos.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <1 | 2 | 3>" << endl;
        return 1;
    }
    int option = atoi(argv[1]);
    switch (option) {
        case 1: {
                Dominos dominos;
                dominos.play(1, 10, 1);
            }
            break;
        case 2: // TODO
        case 3: // TODO
            cout << "Not implemented yet." << endl;
            return 0;
        default:
            cout << "Invalid option. Please choose 1, 2, or 3." << endl;
            return 1;
    }
    return 0;
}