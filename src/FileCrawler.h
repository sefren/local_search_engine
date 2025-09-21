#pragma once
// Purpose: walk a directory tree and collect file paths (skips directories in the ignore set).

#include <filesystem>
#include <string>
#include <vector>
#include <unordered_set>

namespace findex {

    class FileCrawler {
    public:
        // Construct crawler with optional ignore set (directory names to skip, e.g. "node_modules").
        explicit FileCrawler(std::unordered_set<std::string> ignore_dirs = {});

        ~FileCrawler() = default;

        // Crawl the given root path and return a vector of discovered file paths.
        std::vector<std::filesystem::path> crawlPath(const std::filesystem::path& root) const noexcept;

    private:
        // Recursive helper that appends files into 'out'.
        void listContent(const std::filesystem::path& dir,
                         std::vector<std::filesystem::path>& out) const noexcept;

        std::unordered_set<std::string> ignore_dirs_;
    };
} // namespace findex
