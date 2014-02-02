//  Copyright (c) 2012-2014 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ECHELON_HDF5_CONTAINER_ADAPTION_HPP
#define ECHELON_HDF5_CONTAINER_ADAPTION_HPP

#include <echelon/std/stl_support.hpp>

#include <type_traits>
#include <utility>

namespace echelon
{
namespace hdf5
{
    
template <typename C>
inline auto data(const C& container) -> decltype(container.data())
{
    return container.data();
}

template <typename C>
inline auto data(C& container) -> decltype(container.data())
{
    return container.data();
}

template <typename C>
inline auto shape(const C& container) -> decltype(container.shape())
{
    return container.shape();
}

/** \brief Reshapes the container.
 *
 *  \tparam C type of the container
 *
 *  \param container container, which should be reshaped
 *  \param new_shape new shape of the container
 */
template <typename C>
inline auto reshape(C& container, const std::vector<std::size_t>& new_shape) -> decltype(container.reshape(new_shape))
{
    container.reshape(new_shape);
}

namespace detail
{
    struct function_not_overloaded {};
}

inline detail::function_not_overloaded data(...)
{
    return {};
}

inline detail::function_not_overloaded shape(...)
{
    return {};
}

inline detail::function_not_overloaded reshape(...)
{
    return {};
}

// Function template which simply forwards its arguments to an overload of
// shape.
// Its sole purpose is to ensure that the correct overload can be found by ADL.
template <typename C>
inline auto shape_adl(const C& container) -> decltype(shape(container))
{
    return shape(container);
}

template<typename T>
constexpr bool has_data_accessor()
{
    return !std::is_same<decltype(data(std::declval<T&>())), detail::function_not_overloaded>::value;
}

template<typename T>
constexpr bool has_shape_property()
{
    return !std::is_same<decltype(shape(std::declval<T&>())), detail::function_not_overloaded>::value;
}

template<typename T>
constexpr bool has_reshape_member()
{
    return !std::is_same<decltype(reshape(std::declval<T&>(), std::declval<std::vector<std::size_t>>())), detail::function_not_overloaded>::value;
}

template <typename T>
constexpr bool is_container()
{
    return has_data_accessor<T>() && has_shape_property<T>() && has_reshape_member<T>();
}

}
}

#endif
