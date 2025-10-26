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

#include "bedrock/platform/threading/mutex_details.h"

namespace Bedrock::PubSub::ThreadModel {

struct SingleThreaded {
    class NullMutex {
    public:
        void lock() const {}
        [[nodiscard]] bool try_lock() const
        {
            return true;
        };
        void unlock() const {}
    };
    using MutexType = NullMutex;
};

struct MultiThreaded {
    using MutexType = Threading::Mutex;
};

struct MultiThreadedStrict {
    using MutexType = Threading::RecursiveMutex;
};

}  // namespace Bedrock::PubSub::ThreadModel
