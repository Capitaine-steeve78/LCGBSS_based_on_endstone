// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifdef __linux__

#include <climits>
#include <fstream>

#include <fmt/format.h>

#include "endstone/detail/platform.h"

namespace endstone::detail {

namespace {
struct ModuleInfo {
    void *base;
    std::string pathname;
};

struct MmapRegion {
    std::size_t begin;
    std::size_t end;
    char perms[4 + 1];  // rwxp(4) + \0(1)
    std::size_t offset;
    char device[255 + 1];
    std::size_t inode;
    char pathname[PATH_MAX + 1];
};

ModuleInfo get_module_info(const char *module_name)
{
    std::ifstream file("/proc/self/maps");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open /proc/self/maps");
    }

    for (std::string line; std::getline(file, line);) {
        MmapRegion region;
        int r = sscanf(line.c_str(), "%lx-%lx %4s %lx %10s %ld %s", &region.begin, &region.end, region.perms,
                       &region.offset, region.device, &region.inode, region.pathname);
        if (r != 7) {
            continue;
        }

        auto pathname = std::string(region.pathname);
        std::size_t pos = pathname.find_last_of('/');
        if (pos != std::string::npos) {
            pathname = pathname.substr(pos + 1);
        }

        if (module_name == nullptr || pathname == module_name) {
            return {reinterpret_cast<void *>(region.begin), region.pathname};
        }
    }

    throw std::runtime_error(fmt::format("Module {} not found in {}", module_name, "/proc/self/maps"));
}
}  // namespace

void *get_module_base()
{
    static void *base = []() {
        auto module_info = get_module_info("libendstone_runtime.so");
        return module_info.base;
    }();
    return base;
}

std::string get_module_pathname()
{
    auto module_info = get_module_info("libendstone_runtime.so");
    return module_info.pathname;
}

void *get_executable_base()
{
    static void *base = []() {
        auto module_info = get_module_info(nullptr);
        return module_info.base;
    }();
    return base;
}

std::string get_executable_pathname()
{
    auto module_info = get_module_info(nullptr);
    return module_info.pathname;
}

std::string_view get_platform()
{
    return "Linux";
}

std::size_t get_proc_status(std::string_view key)
{
    std::ifstream file("/proc/self/status");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open /proc/self/status");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.size() > key.size() && line.substr(0, key.size()) == key && line[key.size()] == ':') {
            return std::stoi(line.substr(key.size() + 1));
        }
    }

    throw std::runtime_error(fmt::format("Key {} not found in {}", key, "/proc/self/status"));
}

std::size_t get_thread_count()
{
    return get_proc_status("Threads");
}

std::size_t get_used_physical_memory()
{
    return get_proc_status("VmRSS") * 1024;
}

std::size_t get_total_virtual_memory()
{
    return get_proc_status("VmSize") * 1024;
}

}  // namespace endstone::detail

#endif
