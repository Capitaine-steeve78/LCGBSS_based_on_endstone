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

#include "endstone/core/scoreboard/criteria.h"

namespace endstone::core {

EndstoneCriteria::EndstoneCriteria(const ObjectiveCriteria &criteria) : criteria_(criteria) {}

std::string EndstoneCriteria::getName() const
{
    return criteria_.getName();
}

bool EndstoneCriteria::isReadOnly() const
{
    return criteria_.isReadOnly();
}

RenderType EndstoneCriteria::getDefaultRenderType() const
{
    return static_cast<RenderType>(criteria_.getRenderType());
}

}  // namespace endstone::core
