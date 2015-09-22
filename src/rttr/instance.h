/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014, 2015 Axel Menzel <info@axelmenzel.de>                       *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#ifndef RTTR_INSTANCE_H_
#define RTTR_INSTANCE_H_

#include "rttr/detail/base/core_prerequisites.h"
#include "rttr/detail/misc/misc_type_traits.h"
#include "rttr/detail/misc/data_address_container.h"

namespace rttr
{
class variant;
class type;
class argument;

/*!
 * This class is used for forwarding the instance of an object to the function calls.
 *
 * \remark You should never explicit instantiate this class by yourself.
 */
class RTTR_API instance
{
public:
    RTTR_INLINE instance();

    RTTR_INLINE instance(variant& var);

    RTTR_INLINE instance(const instance& other);

    RTTR_INLINE instance(instance&& other);

    template<typename T> // TO DO DISALLOW VARIANT ACCESS!!
    RTTR_INLINE instance(const T& data, typename std::enable_if<!std::is_same<instance, T>::value >::type* = 0);

    template<typename T>
    RTTR_INLINE instance(T& data, typename std::enable_if<!std::is_same<instance, T>::value >::type* = 0);

    template<typename TargetType>
    RTTR_INLINE TargetType* try_convert() const;

    RTTR_INLINE bool is_valid() const;
    explicit operator bool() const;

    RTTR_INLINE type get_type() const;

private:
    instance& operator=(const instance& other);

    detail::data_address_container m_data_container;
};

/*!
 * \brief Returns a dummy instance object.
 *         Use this function when you have a static \ref method or \ref property which you need to invoke.
 *
 * \return An instance object.
 */
RTTR_INLINE static instance empty_instance() { return instance(); }

} // end namespace rttr

#include "rttr/detail/impl/instance_impl.h"

#endif // RTTR_INSTANCE_H_