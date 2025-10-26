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

#include <vector>

#include "bedrock/world/actor/actor_unique_id.h"
#include "bedrock/world/actor/player/layered_abilities.h"
#include "bedrock/world/actor/player/permissions_handler.h"

class SerializedAbilitiesData {
    enum class SerializedAbilitiesLayer : std::uint16_t {
        CustomCache = 0,
        Base = 1,
        Spectator = 2,
        Commands = 3,
        Editor = 4,
        LoadingScreen = 5
    };

    struct SerializedLayer {
        SerializedAbilitiesLayer serialized_layer{SerializedAbilitiesLayer::Base};  // +0
        std::uint32_t abilities_set;                                                // +4
        std::uint32_t ability_values;                                               // +8
        float fly_speed;                                                            // +12
        float vertical_fly_speed;                                                   // +16
        float walk_speed;                                                           // +20
    };

public:
    SerializedAbilitiesData() = default;
    SerializedAbilitiesData(ActorUniqueID target_player, const LayeredAbilities &layered_abilities);

private:
    ActorUniqueID target_player_{-1};             // +0
    CommandPermissionLevel command_permissions_;  // +8
    PlayerPermissionLevel player_permissions_;    // +9
    std::vector<SerializedLayer> layers_;         // +16

    inline static const std::array<SerializedAbilitiesLayer, static_cast<int>(AbilitiesLayer::LayerCount)>
        // NOLINTNEXTLINE(*-identifier-naming)
        ABILITIES_LAYER_MAP = {SerializedAbilitiesLayer::CustomCache, SerializedAbilitiesLayer::Base,
                               SerializedAbilitiesLayer::Spectator,   SerializedAbilitiesLayer::Commands,
                               SerializedAbilitiesLayer::Editor,      SerializedAbilitiesLayer::LoadingScreen};
};
