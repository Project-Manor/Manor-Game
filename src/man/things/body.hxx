#pragma once
#include <raylib.h>
#include <string>
#include "renderable.hxx"

namespace man::things {
    class Body : public render::Renderable {
    public:
        Body();
        void draw() override;

    protected:
        void _initModel (
            std::string modelPath,
            std::string texturePath
        );

    private:
        bool _isValid;
        Model _model;
        Texture2D _texture;

        void _cleanup();
    };
}