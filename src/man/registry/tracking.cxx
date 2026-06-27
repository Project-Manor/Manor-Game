#include "tracking.hxx"

namespace man::registry::tracking {
    static unsigned long long c = 0;
    static unsigned long long a = 0;
    static unsigned long long d = 0;

    void incrementTotalEntryCount() { c++; a++; }
    void decrementTotalEntryCount() { a--; d++; }

    const unsigned long long &getTotalCreatedEntries() { return c; }
    const unsigned long long &getTotalAliveEntries() { return a; }
    const unsigned long long &getTotalDeadEntries() { return d; }
}