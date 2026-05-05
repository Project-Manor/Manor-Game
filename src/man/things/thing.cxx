#include "thing.hxx"

man::things::Thing::Thing() :
    _inits(0),
    _procs(0),
    _terms(0)
{}

man::things::Thing::~Thing() = default;

void man::things::Thing::launch() {}
void man::things::Thing::process() {}
void man::things::Thing::finish() {}