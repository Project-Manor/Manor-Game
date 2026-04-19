#pragma once

namespace man {
    namespace ent {
        class Entity {
            public:
                Entity();
                virtual ~Entity();

                void init();
                void start();

                void proc();

                void term();
        };
    }
}