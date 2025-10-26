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

#include "bedrock/core/container/intrusive_list.h"
#include "bedrock/core/utility/pub_sub/detail/subscription_body.h"

namespace Bedrock::PubSub::Detail {

class PublisherBase : public PublisherDisconnector {
    using ConnectionList = Intrusive::list<SubscriptionBodyBase, Intrusive::list_base_hook<SubscriptionBodyBase>>;

protected:
    ConnectionList subscriptions_;    // +8
    std::uint32_t subscriber_count_;  // +24
};

}  // namespace Bedrock::PubSub::Detail
