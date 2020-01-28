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

#include <geode/geometry/bounding_box.h>

#include <geode/model/representation/core/section.h>

namespace geode
{
    void define_section( pybind11::module& module )
    {
        pybind11::class_< Section, Topology, Corners2D, Lines2D, Surfaces2D,
            ModelBoundaries2D >( module, "Section" )
            .def( pybind11::init<>() )
            .def(
                "boundary_corners",
                []( const Section& section, const Line2D& line ) {
                    std::vector< const Corner2D* > components;
                    for( const auto& component : section.boundaries( line ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def(
                "boundary_lines",
                []( const Section& section, const Surface2D& surface ) {
                    std::vector< const Line2D* > components;
                    for( const auto& component : section.boundaries( surface ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def(
                "incident_lines",
                []( const Section& section, const Corner2D& corner ) {
                    std::vector< const Line2D* > components;
                    for( const auto& component : section.incidences( corner ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def(
                "incident_surfaces",
                []( const Section& section, const Line2D& line ) {
                    std::vector< const Surface2D* > components;
                    for( const auto& component : section.incidences( line ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def( "nb_internal_surface_corners", &Section::nb_internal_corners )
            .def(
                "internal_surface_corners",
                []( const Section& section, const Surface2D& surface ) {
                    std::vector< const Corner2D* > components;
                    for( const auto& component :
                        section.internal_corners( surface ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def( "nb_internal_surface_lines", &Section::nb_internal_lines )
            .def(
                "internal_surface_lines",
                []( const Section& section, const Surface2D& surface ) {
                    std::vector< const Line2D* > components;
                    for( const auto& component :
                        section.internal_lines( surface ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def( "nb_embedded_corner_surfaces",
                ( index_t( Section::* )( const Corner2D& ) const )
                    & Section::nb_embedded_surfaces )
            .def(
                "embedded_corner_surfaces",
                []( const Section& section, const Corner2D& corner ) {
                    std::vector< const Surface2D* > components;
                    for( const auto& component :
                        section.embedded_surfaces( corner ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def( "nb_embedded_line_surfaces",
                ( index_t( Section::* )( const Line2D& ) const )
                    & Section::nb_embedded_surfaces )
            .def(
                "embedded_line_surfaces",
                []( const Section& section, const Line2D& line ) {
                    std::vector< const Surface2D* > components;
                    for( const auto& component :
                        section.embedded_surfaces( line ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def(
                "items",
                []( const Section& section, const ModelBoundary2D& boundary ) {
                    std::vector< const Line2D* > components;
                    for( const auto& component : section.items( boundary ) )
                    {
                        components.push_back( &component );
                    }
                    return components;
                },
                pybind11::return_value_policy::reference )
            .def( "is_line_closed", &Section::is_closed )
            .def( "bounding_box", &Section::bounding_box )
            .def( "native_extension", &Section::native_extension );
    }
} // namespace geode
