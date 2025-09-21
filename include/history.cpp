#include <iostream>
#include <fstream>
#include <algorithm>
#include <termios.h>
#include <unistd.h>

#include "history.h"

#include <absl/strings/str_cat.h>

void History::load() {
    std::ifstream file(historyFile_);
    if(!file) return;

    std::string buffer{};
    while (std::getline(file, buffer) && history_.size() < maxSieze_) {
        if (!buffer.empty()) {
            history_.push_back(buffer);
        }        
    }
    currentIndex_ = history_.size();
}

void History::save() {
    std::ofstream file(historyFile_);
    if(!file) return;

    for(const auto& cmd : history_) {
        file << cmd << '\n';
    }
}

void History::add(const std::string& command) {
    if(command.empty() || command[0] == ' ') return; // skip empty commands

    // delete dublicates
    auto iter = std::find(history_.begin(), history_.end(), command);
    if (iter != history_.end()) {
        history_.erase(iter);
    }

    history_.push_back(command);
    if (history_.size() > maxSieze_) {
        history_.erase(history_.begin());
    }
    
    currentIndex_ = history_.size();
}

void History::print() {
    int count = 0;
    for(const auto& cmd : history_) {
        std::cout << count << " " << cmd << '\n';
        count++;
    }
}

bool History::empty() const {
    return history_.empty();
}

size_t History::size() {
    return history_.size();
}

absl::StatusOr<std::string> History::last() const {
    if(history_.empty()) return absl::NotFoundError("No commands in history");
    return history_.back();
}

absl::StatusOr<std::string> History::get(int n) const {
    if(n < 1 || n > static_cast<int>(history_.size())) return absl::NotFoundError(absl::StrCat("Invalid history index: ", n));
    return history_[n - 1];
}