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

#include "bedrock/util/data_io.h"

class StringByteOutput : public BytesDataOutput {
public:
    StringByteOutput(std::string &buffer) : buffer_(buffer){};
    ~StringByteOutput() override = default;
    void writeBytes(const void *data, std::uint64_t bytes) override;

protected:
    std::string &buffer_;
};
static_assert(sizeof(StringByteOutput) == 16);

class BigEndianStringByteOutput : public StringByteOutput {
public:
    using StringByteOutput::StringByteOutput;
    ~BigEndianStringByteOutput() override = default;
    void writeFloat(float v) override;
    void writeDouble(double v) override;
    void writeShort(std::int16_t v) override;
    void writeInt(std::int32_t v) override;
    void writeLongLong(std::int64_t v) override;
};
static_assert(sizeof(BigEndianStringByteOutput) == 16);
