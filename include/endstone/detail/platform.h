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

#pragma once

#include <string>

namespace endstone::detail {
void *get_module_base();
std::string get_module_pathname();
void *get_executable_base();
std::string get_executable_pathname();
std::string_view get_platform();
std::size_t get_thread_count();
std::size_t get_used_physical_memory();
std::size_t get_total_virtual_memory();
}  // namespace endstone::detail
