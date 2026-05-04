#include "body.hxx"

man::things::Body::Body() :
    _isValid(false),
    _model({0}),
    _texture({0})
{}

void man::things::Body::_initModel (
    std::string modelPath,
    std::string texturePath
) {
    _model = LoadModel(modelPath.c_str());
    _texture = LoadTexture(texturePath.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    _isValid = true;
};

void man::things::Body::finish() {
    if (!_isValid) return;
    UnloadModel(_model);
    UnloadTexture(_texture);
};

void man::things::Body::draw() {
    if (!_isValid) return;
    DrawModel(_model, _pos, 1.0f, WHITE);
}