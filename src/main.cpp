#include <iostream>
#include <memory>

#include "FileCrawler.h"

int main(int argc, char* argv[]) {

    // root dir search engine will crawl index and search
    // TODO : will be later taken as args from user
    std::filesystem::path root = "C:/dev/";

    // Default ignore list: common dev junk.
    // more will be added as we go
    // TODO: way to let user set and configure it.

    std::unordered_set<std::string> ignore = {
        ".git",
        ".idea",
        "cmake-build-debug",
        "build",
        "node_modules",
        ".venv",
        "_pycache",
        ".next",
        "cache",
        "__pycache__",
    };

    findex::FileCrawler crawler(ignore);

    auto files = crawler.crawlPath(root);

    for (const auto& p : files) {
        std::cout << p.string() << '\n';
    }

    return 0;
}
