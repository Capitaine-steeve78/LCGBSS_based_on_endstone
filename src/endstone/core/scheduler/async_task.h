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

#include <mutex>
#include <thread>

#include "endstone/core/scheduler/task.h"

namespace endstone::core {

class EndstoneAsyncTask : public EndstoneTask {
public:
    struct Worker {
        std::thread::id thread_id;
        TaskId task_id;
        Plugin *owner_;
    };

    using EndstoneTask::EndstoneTask;
    [[nodiscard]] bool isSync() const override;

    void run() override;
    void doCancel() override;

    std::vector<Worker> getWorkers() const;

private:
    mutable std::mutex mutex_;
    std::vector<Worker> workers_;
};

}  // namespace endstone::core
