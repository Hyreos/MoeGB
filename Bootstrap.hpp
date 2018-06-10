#pragma once

#include "Cartrigbe.hpp"

class Bootstrap {
public:
    Bootstrap() = default;

    Bootstrap(Cartrigbe cartrigbe);

    ~Bootstrap() = default;

    void start(Cartrigbe cartrigbe);
};