/*
 * Copyright (c) 2019 - 2020 Geode-solutions
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

#include <geode/mesh/io/point_set_input.h>

#include <geode/mesh/core/point_set.h>

namespace geode
{
    template < index_t dimension >
    void load_point_set(
        PointSet< dimension >& point_set, absl::string_view filename )
    {
        try
        {
            auto input = PointSetInputFactory< dimension >::create(
                extension_from_filename( filename ).data(), point_set,
                filename );
            input->read();
        }
        catch( const OpenGeodeException& e )
        {
            Logger::error( e.what() );
            throw OpenGeodeException{ "Cannot load PointSet from file: ",
                filename };
        }
    }

    template < index_t dimension >
    PointSetInput< dimension >::PointSetInput(
        PointSet< dimension >& point_set, absl::string_view filename )
        : VertexSetInput( point_set, filename ), point_set_( point_set )
    {
    }

    template void opengeode_mesh_api load_point_set(
        PointSet< 2 >&, absl::string_view );
    template void opengeode_mesh_api load_point_set(
        PointSet< 3 >&, absl::string_view );

    template class opengeode_mesh_api PointSetInput< 2 >;
    template class opengeode_mesh_api PointSetInput< 3 >;
} // namespace geode
