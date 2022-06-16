//
// Created by Thomas Vallentin on 10/06/2022.
//

#ifndef RBND_NOTIFIER_H
#define RBND_NOTIFIER_H

#include "Rebound/Core/Logging.h"

#include <functional>
#include <map>
#include <vector>


namespace Rebound {

#define DEFINE_NOTIFIER_SENDER_TYPE(_SenderType) template class Notifier<_SenderType>; \
                                    template<> std::map<_SenderType, std::vector<Observer*>> Notifier<_SenderType>::s_observers;

    class Notice {
    public:
        Notice() = default;

        virtual inline std::string GetTypeName() const { return "EmptyNotice"; }
    };

    class Observer {
    public:
        Observer() = default;

        virtual void Notified(Notice* notice) = 0;
    };

    template <class SenderType>
    using ObserverMap = std::map<SenderType, std::vector<Observer*>>;

    template<class SenderType>
    class Notifier {
    public:
        inline static bool RegisterObserver(SenderType sender, Observer* observer) {
            // The sender is not in the map, insert it with the given observer
            const auto it = s_observers.find(sender);
            if (it == s_observers.end()) {
                s_observers.insert({sender, {observer}});
                return true;

            // The sender is in the map, adding the observer if it is not already registered
            } else {
                if (!std::count(it->second.begin(), it->second.end(), observer)) {
                    it->second.push_back(observer);
                    return true;
                }
            }

            return false;
        }

        inline static bool RevokeObserver(SenderType sender, Observer* observer) {
            // Removing the observer if it is registered
            const auto it = s_observers.find(sender);
            if (it != s_observers.end()) {

                // Sender was found, look for the observer and remove it
                const auto obsIt = std::find(it->second.begin(), it->second.end(), observer);
                if (obsIt != it->second.end()) {
                    it->second.erase(obsIt);

                    // No observer is bound to the sender, removing it from the
                    if (it->second.empty()) {
                        s_observers.erase(it);
                    }
                }
            }

            return false;
        }

        inline static void Notify(SenderType sender, Notice *notice) {
            RBND_DEBUG("Notifying %d listener with a %s notice",
                       s_observers.size(),
                       notice->GetTypeName().c_str());

            // Call every observer that are registered for this sender
            // and call their HandleNotice method.
            const auto it = s_observers.find(sender);
            if (it != s_observers.end()) {
                for (auto &observer : it->second) {
                    observer->Notified(notice);
                }
            }
        }

    private:
        static ObserverMap<SenderType> s_observers;

    };


}


#endif //BOUNCE_NOTIFIER_H
