#pragma once

namespace man::registry::tracking {
    void incrementTotalEntryCount();
    void decrementTotalEntryCount();
    const unsigned long long &getTotalCreatedEntries();
    const unsigned long long &getTotalAliveEntries();
    const unsigned long long &getTotalDeadEntries();
}