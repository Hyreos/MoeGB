#include "Cartrigbe.hpp"
#include <iostream>
#include <cstring>

Cartrigbe::Cartrigbe(const std::string_view path) {    
    load(path);
}

void Cartrigbe::load(const std::string_view path) {    
    std::ifstream file(path.data(), std::ios::binary | std::ios::ate);
    
    std::size_t size = file.tellg();

    m_content.resize(size);
    
    file.seekg(std::streampos(0));
    
    file.read(reinterpret_cast<char*>(m_content.data()), size);

    file.close();
}

std::vector<uint8_t>& Cartrigbe::content() {
    return m_content;
}