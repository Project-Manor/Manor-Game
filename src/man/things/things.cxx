#include "things.hxx"

man::Things &man::Things::instance() {
    static Things inst;
    return inst;
}

man::Things::Things() :
    _uThingCtrs{0},
    _tThingCtrs{0}
{}

man::Things::~Things() {
    for (man::Things::ThingContainer ctr : _uThingCtrs)
        ctr.del(ctr.ptr);

    for (auto &[tag, ctr] : _tThingCtrs)
        ctr.del(ctr.ptr);
}

void man::Things::_proc() {
    for (man::Things::ThingContainer ctr : _uThingCtrs)
        ctr.proc(ctr.ptr);

    for (auto &[tag, ctr] : _tThingCtrs)
        ctr.proc(ctr.ptr);
}