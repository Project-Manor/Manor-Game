#pragma once

namespace man::render {
    class UIRenderable {
    public:
        UIRenderable(const int renderLayer);
        virtual ~UIRenderable();

        virtual void draw() = 0;

    private:
        const int _renderLayer;
    };
}