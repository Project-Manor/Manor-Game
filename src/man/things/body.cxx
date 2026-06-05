#include "body.hxx"

#define GLSL_VERSION 330

man::things::Body::Body() :
    _isValid(false),
    _model({0}),
    _texture({0})
{
    _addTerm(this, &Body::_cleanup);
}

void man::things::Body::_initModel (
    std::string modelPath,
    std::string texturePath,
    std::string shaderPath
) {
    _model = LoadModel(modelPath.c_str());
    _texture = LoadTexture(texturePath.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    if ("" != shaderPath) {
        Shader shader = LoadShader(0, TextFormat(shaderPath.c_str(), GLSL_VERSION));
        _model.materials[0].shader = shader;
    }
    _isValid = true;
};

void man::things::Body::_cleanup() {
    if (!_isValid) return;
    UnloadModel(_model);
    UnloadTexture(_texture);
};

void man::things::Body::draw() {
    if (!_isValid) return;
    DrawModel(_model, _pos, 1.0f, WHITE);
}