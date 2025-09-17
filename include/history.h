#ifndef INCLUDE_HISTORY_H_
#define INCLUDE_HISTORY_H_

#include <vector>
#include <string>

class History {
public:
    explicit History(size_t maxSieze = 500, const std::string& file = ".moser_history") : 
        maxSieze_(maxSieze), historyFile_(file), currentIndex_(0) {}

    void load();
    void save();
    void add(const std::string& command);
    void print();

    std::string navigationOnHistory(History& history) {};
private:
    std::vector<std::string> history_{};
    std::string historyFile_{};
    size_t maxSieze_{};
    size_t currentIndex_{};
};

#endif // INCLUDE_HISTORY_H_