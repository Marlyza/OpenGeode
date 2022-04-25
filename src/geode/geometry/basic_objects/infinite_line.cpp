/*
 * Copyright (c) 2019 - 2022 Geode-solutions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <geode/geometry/basic_objects/infinite_line.h>

#include <geode/geometry/basic_objects/segment.h>

namespace geode
{
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >::GenericInfiniteLine(
        const Vector< dimension >& direction, const Point< dimension >& origin )
        : origin_( origin ), direction_( direction.normalize() )
    {
    }
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >::GenericInfiniteLine(
        const GenericSegment< PointType, dimension >& segment )
        : GenericInfiniteLine(
            segment.normalized_direction(), segment.vertices()[0] )
    {
    }
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >::GenericInfiniteLine(
        const GenericInfiniteLine< PointType, dimension >& other )
        : origin_( other.origin_ ), direction_( other.direction_ )
    {
    }
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >&
        GenericInfiniteLine< PointType, dimension >::operator=(
            const GenericInfiniteLine< PointType, dimension >& other )
    {
        origin_ = other.origin_;
        direction_ = other.direction_;
        return *this;
    }
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >::GenericInfiniteLine(
        GenericInfiniteLine< PointType, dimension >&& other )
        : origin_( std::move( other.origin_ ) ),
          direction_( std::move( other.direction_ ) )
    {
    }
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >&
        GenericInfiniteLine< PointType, dimension >::operator=(
            GenericInfiniteLine< PointType, dimension >&& other )
    {
        origin_ = std::move( other.origin_ );
        direction_ = std::move( other.direction_ );
        return *this;
    }
    template < typename PointType, index_t dimension >
    const Point< dimension >&
        GenericInfiniteLine< PointType, dimension >::origin() const
    {
        return origin_;
    }
    template < typename PointType, index_t dimension >
    const Vector< dimension >&
        GenericInfiniteLine< PointType, dimension >::direction() const
    {
        return direction_;
    }
    template < typename PointType, index_t dimension >
    GenericInfiniteLine< PointType, dimension >::GenericInfiniteLine(
        const OwnerInfiniteLine< dimension >& other )
        : origin_( other.origin() ), direction_( other.direction() )
    {
    }

    template < index_t dimension >
    OwnerInfiniteLine< dimension >::OwnerInfiniteLine(
        const Vector< dimension >& direction, const Point< dimension >& origin )
        : Base( direction, origin )
    {
    }
    template < index_t dimension >
    OwnerInfiniteLine< dimension >::OwnerInfiniteLine(
        const Segment< dimension >& segment )
        : OwnerInfiniteLine(
            segment.normalized_direction(), segment.vertices()[0] )
    {
    }
    template < index_t dimension >
    OwnerInfiniteLine< dimension >::OwnerInfiniteLine(
        const OwnerInfiniteLine< dimension >& other )
        : Base( other )
    {
    }
    template < index_t dimension >
    OwnerInfiniteLine< dimension >& OwnerInfiniteLine< dimension >::operator=(
        const OwnerInfiniteLine< dimension >& other )
    {
        Base::operator=( other );
        return *this;
    }
    template < index_t dimension >
    OwnerInfiniteLine< dimension >::OwnerInfiniteLine(
        OwnerInfiniteLine< dimension >&& other )
        : Base( other )
    {
    }
    template < index_t dimension >
    OwnerInfiniteLine< dimension >& OwnerInfiniteLine< dimension >::operator=(
        OwnerInfiniteLine< dimension >&& other )
    {
        Base::operator=( other );
        return *this;
    }

    template < index_t dimension >
    InfiniteLine< dimension >::InfiniteLine(
        const Vector< dimension >& direction, const Point< dimension >& origin )
        : Base( direction, origin )
    {
    }
    template < index_t dimension >
    InfiniteLine< dimension >::InfiniteLine(
        const Segment< dimension >& segment )
        : InfiniteLine( segment.normalized_direction(), segment.vertices()[0] )
    {
    }
    template < index_t dimension >
    InfiniteLine< dimension >::InfiniteLine(
        const InfiniteLine< dimension >& other )
        : Base( other )
    {
    }
    template < index_t dimension >
    InfiniteLine< dimension >::InfiniteLine(
        const OwnerInfiniteLine< dimension >& other )
        : Base( other )
    {
    }
    template < index_t dimension >
    InfiniteLine< dimension >& InfiniteLine< dimension >::operator=(
        const InfiniteLine< dimension >& other )
    {
        Base::operator=( other );
        return *this;
    }
    template < index_t dimension >
    InfiniteLine< dimension >::InfiniteLine( InfiniteLine< dimension >&& other )
        : Base( other )
    {
    }
    template < index_t dimension >
    InfiniteLine< dimension >& InfiniteLine< dimension >::operator=(
        InfiniteLine< dimension >&& other )
    {
        Base::operator=( other );
        return *this;
    }

    template class opengeode_geometry_api GenericInfiniteLine< Point< 2 >, 2 >;
    template class opengeode_geometry_api GenericInfiniteLine< Point< 3 >, 3 >;
    template class opengeode_geometry_api
        GenericInfiniteLine< RefPoint< 2 >, 2 >;
    template class opengeode_geometry_api
        GenericInfiniteLine< RefPoint< 3 >, 3 >;
    template class opengeode_geometry_api OwnerInfiniteLine< 2 >;
    template class opengeode_geometry_api OwnerInfiniteLine< 3 >;
    template class opengeode_geometry_api InfiniteLine< 2 >;
    template class opengeode_geometry_api InfiniteLine< 3 >;
} // namespace geode