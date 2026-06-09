#pragma once

namespace man::render {
    class UIRenderable {
    public:
        UIRenderable();
        virtual ~UIRenderable();

        virtual void draw() = 0;

    protected:
        #define UIRenderable_initUIRenderableTemplate   \
        template <int RenderLayer>                      \
        requires (RenderLayer <= 15 && RenderLayer >= 0)

        UIRenderable_initUIRenderableTemplate
        void _initUIRenderable();

    private:
        bool _isInitialized;
        int _renderLayer;
        void _initUIRenderable2();
    };
}

#include "ui_renderable.t.hxx"