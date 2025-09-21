#include "FileCrawler.h"

#include <system_error>

namespace findex {

FileCrawler::FileCrawler(std::unordered_set<std::string> ignore_dirs)
    : ignore_dirs_(std::move(ignore_dirs)) {}

// Returns a vector by value
std::vector<std::filesystem::path> FileCrawler::crawlPath(const std::filesystem::path& root) const noexcept {
    std::vector<std::filesystem::path> result;
    // if the root doesn't exist, return an empty vector

    std::error_code ec;
    if (!std::filesystem::exists(root, ec) || !std::filesystem::is_directory(root, ec)) {
        // caller can log; keep function noexcept
        return result;
    }
    listContent(root, result);
    return result;
}

// Recursive directory walk.
// Uses ignore_dirs_ to skip directories by name.
void FileCrawler::listContent(const std::filesystem::path& dir,
                              std::vector<std::filesystem::path>& out) const noexcept {
    std::error_code ec;
    for (auto it = std::filesystem::directory_iterator(dir, ec); it != std::filesystem::directory_iterator(); it.increment(ec)) {
        if (ec) {
            // skip entries we can't read (permission, symlink loops, etc.)
            ec.clear();
            continue;
        }

        const auto& entry = *it;
        const auto& p = entry.path();

        // If entry is a directory and named in ignore set -> skip subtree.
        if (entry.is_directory(ec)) {
            const auto name = p.filename().string();
            if (ignore_dirs_.find(name) != ignore_dirs_.end()) {
                // skip recursion into ignored dir
                continue;
            }
            // Recurse into directory
            listContent(p, out);
            continue;
        }

        // If entry is a regular file, append path
        if (entry.is_regular_file(ec)) {
            out.push_back(p);
        }
    }
}
} // namespace findex
