#pragma once

#include "Bindable.h"

namespace Developing::Graphics {
    class BindableResolver {
    public:
        template <typename T, typename... Params>
        static std::shared_ptr<T> Resolve(GraphicsContext& gfx, Params... p) noexcept {
            static_assert(std::is_base_of_v<Bindable, T>);
            return Get().Resolve_<T>(gfx, std::forward<Params>(p)...);
        }

        static void Store(std::shared_ptr<Bindable> bind) {
            Get().Store_(std::move(bind));
        }
    private:
        template <typename T, typename... Params>
        [[nodiscard]] std::shared_ptr<T> Resolve_(GraphicsContext& gfx, Params&&... p) noexcept {
            std::string const key {T::GenerateUID(std::forward<Params>(p)...)};

            if (binds.contains(key)) {
                return std::static_pointer_cast<T>(binds.at(key));
            }
            else {
                auto bind {std::make_shared<T>(gfx, std::forward<Params>(p)...)};
                binds[key] = bind;
                return bind;
            }
        }

        void Store_(std::shared_ptr<Bindable> bind) {
            binds[bind->GetUID()] = std::move(bind);
        }

        static BindableResolver& Get() {
            static BindableResolver resolver;
            return resolver;
        }
    private:
        inline static std::unordered_map<std::string, std::shared_ptr<Bindable>> binds;
    };
}

