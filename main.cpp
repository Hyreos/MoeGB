#include "System.hpp"

int main(int argc, const char **argv) {
    if (argc < 2) {
        return 1;
    }

    try {
        System sys;
        sys.start(argv[1]);
    } catch (const std::runtime_error exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }

    return 0;
}