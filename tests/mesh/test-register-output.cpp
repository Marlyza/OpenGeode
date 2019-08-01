/*
 * Copyright (c) 2019 Geode-solutions
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

#include <geode/basic/logger.h>

#include <geode/mesh/io/detail/register_output.h>

#include <geode/mesh/core/geode_edged_curve.h>
#include <geode/mesh/core/geode_graph.h>
#include <geode/mesh/core/geode_point_set.h>
#include <geode/mesh/core/geode_polygonal_surface.h>
#include <geode/mesh/core/geode_polyhedral_solid.h>
#include <geode/mesh/core/geode_tetrahedral_solid.h>
#include <geode/mesh/core/geode_triangulated_surface.h>

#include <geode/mesh/io/detail/geode_edged_curve_output.h>
#include <geode/mesh/io/detail/geode_graph_output.h>
#include <geode/mesh/io/detail/geode_point_set_output.h>
#include <geode/mesh/io/detail/geode_polygonal_surface_output.h>
#include <geode/mesh/io/detail/geode_polyhedral_solid_output.h>
#include <geode/mesh/io/detail/geode_tetrahedral_solid_output.h>
#include <geode/mesh/io/detail/geode_triangulated_surface_output.h>

template < typename GeodeFactory >
void check_register( const std::string& extension )
{
    OPENGEODE_EXCEPTION( GeodeFactory::has_creator( extension ),
        std::string(
            "No creator for extension " + extension + " is not correct" ) );
}

int main()
{
    using namespace geode;

    try
    {
        /* To initialize the mesh library */
        register_geode_mesh_output();

        /* Run checks */
        check_register< GraphOutputFactory >(
            OpenGeodeGraph::native_extension_static() );
        check_register< PointSetOutputFactory2D >(
            OpenGeodePointSet2D::native_extension_static() );
        check_register< PointSetOutputFactory3D >(
            OpenGeodePointSet3D::native_extension_static() );
        check_register< EdgedCurveOutputFactory2D >(
            OpenGeodeEdgedCurve2D::native_extension_static() );
        check_register< EdgedCurveOutputFactory3D >(
            OpenGeodeEdgedCurve3D::native_extension_static() );
        check_register< PolygonalSurfaceOutputFactory2D >(
            OpenGeodePolygonalSurface2D::native_extension_static() );
        check_register< PolygonalSurfaceOutputFactory3D >(
            OpenGeodePolygonalSurface3D::native_extension_static() );
        check_register< TriangulatedSurfaceOutputFactory2D >(
            OpenGeodeTriangulatedSurface2D::native_extension_static() );
        check_register< TriangulatedSurfaceOutputFactory3D >(
            OpenGeodeTriangulatedSurface3D::native_extension_static() );
        check_register< PolyhedralSolidOutputFactory3D >(
            OpenGeodePolyhedralSolid3D::native_extension_static() );
        check_register< TetrahedralSolidOutputFactory3D >(
            OpenGeodeTetrahedralSolid3D::native_extension_static() );

        Logger::info( "TEST SUCCESS" );
        return 0;
    }
    catch( ... )
    {
        return geode_lippincott();
    }
}
