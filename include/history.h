#ifndef INCLUDE_HISTORY_H_
#define INCLUDE_HISTORY_H_

#include <vector>
#include <string>

#include <absl/status/status.h>
#include <absl/status/statusor.h>

class History {
public:
    explicit History(size_t maxSieze = 500, const std::string& file = ".moser_history") noexcept : 
        maxSieze_(maxSieze), historyFile_(file), currentIndex_(0) {}

    void load();
    void save();
    void add(const std::string& command);
    void print();
    bool empty() const;
    size_t size();

    // ---Comands---
    absl::StatusOr<std::string> last() const;
    absl::StatusOr<std::string> get(int n) const;

private:
    std::vector<std::string> history_{};
    std::string historyFile_{};
    size_t maxSieze_{};
    size_t currentIndex_{};
};

#endif // INCLUDE_HISTORY_H_