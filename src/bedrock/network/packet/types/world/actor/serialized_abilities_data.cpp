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

#include "bedrock/network/packet/types/world/actor/serialized_abilities_data.h"

SerializedAbilitiesData::SerializedAbilitiesData(ActorUniqueID target_player, const LayeredAbilities &layered_abilities)
    : target_player_(target_player), command_permissions_(layered_abilities.getCommandPermissions()),
      player_permissions_(layered_abilities.getPlayerPermissions())
{
    layered_abilities.forEachLayer([this](AbilitiesLayer layer, const Abilities &abilities) {
        if (!abilities.isAnyAbilitySet()) {
            return;
        }

        auto &serialized_layer = layers_.emplace_back(SerializedLayer{});
        serialized_layer.serialized_layer = ABILITIES_LAYER_MAP[static_cast<int>(layer)];
        abilities.forEachAbility(
            [&serialized_layer](Ability const &ability, AbilitiesIndex index) {
                auto flag = (1 << static_cast<int>(index));
                if (ability.isSet()) {
                    serialized_layer.abilities_set |= flag;
                }
                else {
                    serialized_layer.abilities_set &= ~flag;
                }

                if (ability.getType() == Ability::Type::Bool) {
                    if (ability.getBool()) {
                        serialized_layer.ability_values |= flag;
                    }
                    else {
                        serialized_layer.ability_values &= ~flag;
                    }
                }
            },
            Ability::Options::None);
        serialized_layer.fly_speed = abilities.getFloat(AbilitiesIndex::FlySpeed);
        serialized_layer.vertical_fly_speed = abilities.getFloat(AbilitiesIndex::VerticalFlySpeed);
        serialized_layer.walk_speed = abilities.getFloat(AbilitiesIndex::WalkSpeed);
    });
}
