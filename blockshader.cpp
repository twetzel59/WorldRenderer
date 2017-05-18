#include "blockshader.hpp"
#include <iostream>

BlockShader::BlockShader(const std::string &vertex_file, const std::string &fragment_file) {
    loadFromFiles(vertex_file, fragment_file);

    bindAttribLocation(0, "pos");
    //bindAttribLocation(1, "color");

    link();
}
