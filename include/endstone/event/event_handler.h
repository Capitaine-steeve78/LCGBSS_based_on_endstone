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
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "endstone/event/event.h"
#include "endstone/event/event_priority.h"
#include "endstone/plugin/plugin.h"

namespace endstone {

/**
 * @brief Represents a registered EventHandler which associates with a Plugin
 */
class EventHandler {
public:
    EventHandler(std::string event, std::function<void(Event &)> executor, EventPriority priority, Plugin &plugin,
                 bool ignore_cancelled)
        : event_(std::move(event)), executor_(std::move(executor)), priority_(priority), plugin_(plugin),
          ignore_cancelled_(ignore_cancelled)
    {
    }

    /**
     * Gets the plugin for this registration
     *
     * @return Registered Plugin
     */
    [[nodiscard]] Plugin &getPlugin() const
    {
        return plugin_;
    }
    /**
     * Gets the priority for this registration
     *
     * @return Registered Priority
     */
    [[nodiscard]] EventPriority getPriority() const
    {
        return priority_;
    }

    /**
     * Whether this listener accepts cancelled events
     *
     * @return True when ignoring cancelled events
     */
    [[nodiscard]] bool isIgnoreCancelled() const
    {
        return ignore_cancelled_;
    }

    /**
     * Calls the event executor
     *
     * @param event The event
     */
    void callEvent(Event &event) const
    {
        if (event.getEventName() != event_) {
            return;
        }
        if (event.isCancellable() && event.cancelled_ && isIgnoreCancelled()) {
            return;
        }
        executor_(event);
    };

    /**
     * Gets the event type for this registration
     *
     * @return Registered event type
     */
    [[nodiscard]] std::string getEventType() const
    {
        return event_;
    }

private:
    std::string event_;
    std::function<void(Event &)> executor_;
    EventPriority priority_;
    Plugin &plugin_;
    bool ignore_cancelled_;
};

}  // namespace endstone
