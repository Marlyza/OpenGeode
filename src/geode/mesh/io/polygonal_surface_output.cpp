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

#include <geode/mesh/io/polygonal_surface_output.h>

#include <geode/mesh/core/polygonal_surface.h>
#include <geode/mesh/io/vertex_set_output.h>

namespace geode
{
    template < index_t dimension >
    void save_polygonal_surface(
        const PolygonalSurface< dimension >& polygonal_surface,
        absl::string_view filename )
    {
        try
        {
            const auto extension =
                to_string( extension_from_filename( filename ) );
            if( PolygonalSurfaceOutputFactory< dimension >::has_creator(
                    extension ) )
            {
                PolygonalSurfaceOutputFactory< dimension >::create(
                    extension, polygonal_surface, filename )
                    ->write();
            }
            else if( VertexSetOutputFactory::has_creator( extension ) )
            {
                VertexSetOutputFactory::create(
                    extension, polygonal_surface, filename )
                    ->write();
            }
            else
            {
                throw OpenGeodeException{ "Unknown extension: ", extension };
            }
            Logger::info(
                "PolygonalSurface", dimension, "D saved in ", filename );
        }
        catch( const OpenGeodeException& e )
        {
            Logger::error( e.what() );
            throw OpenGeodeException{ "Cannot save PolygonalSurface in file: ",
                filename };
        }
    }

    template < index_t dimension >
    PolygonalSurfaceOutput< dimension >::PolygonalSurfaceOutput(
        const PolygonalSurface< dimension >& polygonal_surface,
        absl::string_view filename )
        : VertexSetOutput( polygonal_surface, filename ),
          polygonal_surface_( polygonal_surface )
    {
    }

    template void opengeode_mesh_api save_polygonal_surface(
        const PolygonalSurface< 2 >&, absl::string_view );
    template void opengeode_mesh_api save_polygonal_surface(
        const PolygonalSurface< 3 >&, absl::string_view );

    template class opengeode_mesh_api PolygonalSurfaceOutput< 2 >;
    template class opengeode_mesh_api PolygonalSurfaceOutput< 3 >;
} // namespace geode
