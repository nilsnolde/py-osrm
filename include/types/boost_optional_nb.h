#ifndef OSRM_NB_BOOST_OPTIONAL_H
#define OSRM_NB_BOOST_OPTIONAL_H

#include <boost/optional.hpp>

#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>

// Boost Optional Type Caster (nanobind/stl/optional.h)
namespace nanobind::detail {

template <typename T> struct remove_opt_mono<boost::optional<T>>
    : remove_opt_mono<T> { };

template <typename T>
struct type_caster<boost::optional<T>> {
    using Caster = make_caster<T>;

    NB_TYPE_CASTER(boost::optional<T>, const_name("Optional[") +
                                         concat(Caster::Name) +
                                         const_name("]"))

    type_caster() : value(boost::none) { }

    bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept {
        if (src.is_none()) {
            value = boost::none;
            return true;
        }

        Caster caster;
        if (!caster.from_python(src, flags, cleanup))
            return false;

        static_assert(
            !std::is_pointer_v<T> || is_base_caster_v<Caster>,
            "Binding ``optional<T*>`` requires that ``T`` is handled "
            "by nanobind's regular class binding mechanism. However, a "
            "type caster was registered to intercept this particular "
            "type, which is not allowed.");

        value.emplace(caster.operator cast_t<T>());

        return true;
    }

    template <typename T_>
    static handle from_cpp(T_ &&value, rv_policy policy, cleanup_list *cleanup) noexcept {
        if (!value)
            return none().release();

        return Caster::from_cpp(forward_like<T_>(*value), policy, cleanup);
    }
};

}

#endif //OSRM_NB_BOOST_OPTIONAL_H
