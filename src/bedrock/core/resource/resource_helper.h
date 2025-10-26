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

#include <functional>
#include <unordered_map>

#include "bedrock/core/file/path.h"
#include "bedrock/core/resource/content_identity.h"
#include "bedrock/core/resource/pack_id_version.h"
#include "bedrock/core/resource/resource_util.h"
#include "bedrock/core/string/string_hash.h"
#include "bedrock/core/utility/enable_non_owner_references.h"

using ContentKeyMap = std::unordered_map<ContentIdentity, std::string>;

class ResourceLocation {
public:
    ResourceLocation();
    explicit ResourceLocation(Core::Path const &path);
    ResourceLocation(Core::Path const &path, ResourceFileSystem file_system);

    [[nodiscard]] Core::HeapPathBuffer const &getRelativePath() const;

private:
    void _computeHashes();

public:
    ResourceFileSystem file_system{ResourceFileSystem::UserPackage};  // +0

private:
    Core::HeapPathBuffer path_;  // +8
    HashType64 path_hash_;       // +40
    std::size_t full_hash_;      // +48
};

struct PackInstanceId {
    PackIdVersion pack_id;
    std::string subpack_name;
};

class ResourceLoader : public Bedrock::EnableNonOwnerReferences {
public:
private:
    std::function<Core::PathBuffer<std::string>()> get_path_;
};

enum class PackOrigin : std::uint8_t {
    _Unknown = 0,
    _RealmsUnknown = 1,
    Package = 2,
    Treatment = 3,
    Dev = 4,
    World = 5,
    User = 6,
    TempCache = 7,
    PremiumCache = 8,
    PremiumTempCache = 9,
    Test = 10,
};

enum class PackCategory : std::int32_t {
    _Unknown = 0,
    _RealmsUnknown = 1,
    Standard = 2,
    Premium = 3,
    Custom = 4,
    Subpack = 5,
    Chemistry = 6,
};

enum class ResourcePackStackType : std::int32_t {
    LEVEL = 0,
    ADDON = 1,
    GLOBAL = 2,
    TREATMENT = 3,
    BASE_GAME = 4,
    SIZE = 5,
};
