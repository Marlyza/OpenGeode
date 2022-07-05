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

#pragma once

#include <absl/types/optional.h>

#include <geode/basic/pimpl.h>

#include <geode/geometry/basic_objects/infinite_line.h>

#include <geode/mesh/common.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( SurfaceMesh );
    ALIAS_3D( SurfaceMesh );
} // namespace geode

namespace geode
{
    class opengeode_mesh_api RayTracing3D
    {
    public:
        struct PolygonDistance
        {
            PolygonDistance( index_t polygon_in, double distance_in )
                : polygon{ polygon_in }, distance{ distance_in }
            {
            }

            bool operator<( const PolygonDistance& other ) const
            {
                return distance < other.distance;
            }

            index_t polygon;
            double distance;
        };

    public:
        RayTracing3D( const SurfaceMesh3D& mesh, const Ray3D& ray );
        RayTracing3D( RayTracing3D&& other );
        ~RayTracing3D();

        absl::optional< PolygonDistance > closest_polygon() const;

        void operator()( index_t polygon_id );

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };

} // namespace geode
