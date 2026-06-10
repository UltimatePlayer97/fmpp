#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace Utils {

inline std::string format_bytes(uint64_t bytes) {
    constexpr std::array<std::string_view, 6> suffixes = {
        "B", "KB", "MB", "GB", "TB", "PB"
    };

    if (bytes == 0) return "0 B";

    auto i = static_cast<size_t>(std::floor(std::log2(bytes) / 10.0));

    // Safety check to ensure we don't overflow our suffix array bounds
    if (i >= suffixes.size()) {
        i = suffixes.size() - 1;
    }

    double scaled_value = bytes / std::pow(1024.0, i);

    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << scaled_value << " " << suffixes[i];
    return stream.str();
}

}
