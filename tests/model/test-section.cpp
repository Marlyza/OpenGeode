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

#include <geode/basic/algorithm.h>
#include <geode/basic/assert.h>
#include <geode/basic/logger.h>
#include <geode/basic/range.h>
#include <geode/basic/uuid.h>

#include <geode/model/representation/builder/section_builder.h>
#include <geode/model/representation/core/section.h>
#include <geode/model/representation/io/section_input.h>
#include <geode/model/representation/io/section_output.h>

#include <geode/basic/attribute_manager.h>
#include <geode/mesh/core/geode_edged_curve.h>
#include <geode/mesh/core/geode_point_set.h>
#include <geode/mesh/core/geode_polygonal_surface.h>
#include <geode/mesh/core/geode_polyhedral_solid.h>
#include <geode/mesh/core/point_set.h>
#include <geode/model/mixin/core/block.h>
#include <geode/model/mixin/core/corner.h>
#include <geode/model/mixin/core/line.h>
#include <geode/model/mixin/core/surface.h>

template < typename Range >
geode::index_t count_components( Range range )
{
    geode::index_t count{ 0 };
    for( const auto& unused : range )
    {
        geode_unused( unused );
        count++;
    }
    return count;
}

std::vector< geode::uuid > add_corners(
    const geode::Section& model, geode::SectionBuilder& builder )
{
    geode::index_t nb{ 5 };
    std::vector< geode::uuid > uuids;
    for( auto unused : geode::Range{ nb } )
    {
        geode_unused( unused );
        uuids.push_back( builder.add_corner() );
    }
    const auto& temp_corner = model.corner(
        builder.add_corner( geode::OpenGeodePointSet2D::type_name_static() ) );
    builder.remove_corner( temp_corner );
    auto message = "Section should have " + std::to_string( nb ) + " corners";
    OPENGEODE_EXCEPTION( model.nb_corners() == nb, message );
    OPENGEODE_EXCEPTION( count_components( model.corners() ) == nb, message );
    return uuids;
}

std::vector< geode::uuid > add_lines(
    const geode::Section& model, geode::SectionBuilder& builder )
{
    geode::index_t nb{ 6 };
    std::vector< geode::uuid > uuids;
    for( auto unused : geode::Range{ nb } )
    {
        geode_unused( unused );
        uuids.push_back( builder.add_line() );
    }
    const auto& temp_line = model.line(
        builder.add_line( geode::OpenGeodeEdgedCurve2D::type_name_static() ) );
    builder.remove_line( temp_line );
    auto message = "Section should have " + std::to_string( nb ) + " lines";
    OPENGEODE_EXCEPTION( model.nb_lines() == nb, message );
    OPENGEODE_EXCEPTION( count_components( model.lines() ) == nb, message );
    return uuids;
}

std::vector< geode::uuid > add_surfaces(
    const geode::Section& model, geode::SectionBuilder& builder )
{
    geode::index_t nb{ 2 };
    std::vector< geode::uuid > uuids;
    for( auto unused : geode::Range{ nb } )
    {
        geode_unused( unused );
        uuids.push_back( builder.add_surface() );
    }
    const auto& temp_surface = model.surface( builder.add_surface(
        geode::OpenGeodePolygonalSurface2D::type_name_static() ) );
    builder.remove_surface( temp_surface );
    auto message = "Section should have " + std::to_string( nb ) + " surfaces";
    OPENGEODE_EXCEPTION( model.nb_surfaces() == nb, message );
    OPENGEODE_EXCEPTION( count_components( model.surfaces() ) == nb, message );
    return uuids;
}

void add_corner_line_relation( const geode::Section& model,
    geode::SectionBuilder& builder,
    const std::vector< geode::uuid >& corner_uuids,
    const std::vector< geode::uuid >& line_uuids )
{
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[0] ), model.line( line_uuids[0] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[0] ), model.line( line_uuids[1] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[1] ), model.line( line_uuids[0] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[1] ), model.line( line_uuids[2] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[1] ), model.line( line_uuids[3] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[2] ), model.line( line_uuids[1] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[2] ), model.line( line_uuids[2] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[2] ), model.line( line_uuids[4] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[3] ), model.line( line_uuids[3] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[3] ), model.line( line_uuids[5] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[4] ), model.line( line_uuids[4] ) );
    builder.add_corner_line_relationship(
        model.corner( corner_uuids[4] ), model.line( line_uuids[5] ) );

    for( const auto& corner_id : corner_uuids )
    {
        for( const auto& incidence :
            model.incidences( model.corner( corner_id ) ) )
        {
            OPENGEODE_EXCEPTION( geode::contain( line_uuids, incidence.id() ),
                "All Corners incidences should be Lines" );
        }
    }

    for( const auto& line_id : line_uuids )
    {
        for( const auto& boundary : model.boundaries( model.line( line_id ) ) )
        {
            OPENGEODE_EXCEPTION( geode::contain( corner_uuids, boundary.id() ),
                "All Lines incidences should be Corners" );
        }
    }
}

void add_line_surface_relation( const geode::Section& model,
    geode::SectionBuilder& builder,
    const std::vector< geode::uuid >& line_uuids,
    const std::vector< geode::uuid >& surface_uuids )
{
    builder.add_line_surface_relationship(
        model.line( line_uuids[0] ), model.surface( surface_uuids[0] ) );
    builder.add_line_surface_relationship(
        model.line( line_uuids[1] ), model.surface( surface_uuids[0] ) );
    builder.add_line_surface_relationship(
        model.line( line_uuids[2] ), model.surface( surface_uuids[0] ) );
    builder.add_line_surface_relationship(
        model.line( line_uuids[2] ), model.surface( surface_uuids[1] ) );
    builder.add_line_surface_relationship(
        model.line( line_uuids[3] ), model.surface( surface_uuids[1] ) );
    builder.add_line_surface_relationship(
        model.line( line_uuids[4] ), model.surface( surface_uuids[1] ) );
    builder.add_line_surface_relationship(
        model.line( line_uuids[5] ), model.surface( surface_uuids[1] ) );

    for( const auto& line_id : line_uuids )
    {
        for( const auto& incidence : model.incidences( model.line( line_id ) ) )
        {
            OPENGEODE_EXCEPTION(
                geode::contain( surface_uuids, incidence.id() ),
                "All Lines incidences should be Surfaces" );
        }
    }
    OPENGEODE_EXCEPTION( model.nb_boundaries( surface_uuids[0] ) == 3,
        "Surface 0 should have 3 Lines as boundaries" );
    OPENGEODE_EXCEPTION( model.nb_boundaries( surface_uuids[1] ) == 4,
        "Surface 1 should have 4 Lines as boundaries" );
}

void test_boundary_ranges( const geode::Section& model,
    const std::vector< geode::uuid >& corner_uuids,
    const std::vector< geode::uuid >& line_uuids,
    const std::vector< geode::uuid >& surface_uuids )
{
    const auto& line_boundaries =
        model.boundaries( model.line( line_uuids[0] ) );
    geode::index_t line_boundary_count{ 0 };
    for( const auto& line_boundary : line_boundaries )
    {
        line_boundary_count++;
        OPENGEODE_EXCEPTION( line_boundary.id() == corner_uuids[0]
                                 || line_boundary.id() == corner_uuids[1],
            "LineBoundaryRange iteration result is not correct" );
    }
    OPENGEODE_EXCEPTION( line_boundary_count == 2,
        "LineBoundaryRange should iterates on 2 Corners" );

    const auto& surface_boundaries =
        model.boundaries( model.surface( surface_uuids[0] ) );
    geode::index_t surface_boundary_count{ 0 };
    for( const auto& surface_boundary : surface_boundaries )
    {
        surface_boundary_count++;
        OPENGEODE_EXCEPTION( surface_boundary.id() == line_uuids[0]
                                 || surface_boundary.id() == line_uuids[1]
                                 || surface_boundary.id() == line_uuids[2],
            "SurfaceBoundaryRange iteration result is not correct" );
    }
    OPENGEODE_EXCEPTION( surface_boundary_count == 3,
        "SurfaceBoundaryRange should iterates on 3 Lines" );
}

void test_incidence_ranges( const geode::Section& model,
    const std::vector< geode::uuid >& corner_uuids,
    const std::vector< geode::uuid >& line_uuids,
    const std::vector< geode::uuid >& surface_uuids )
{
    const auto& corner_incidences =
        model.incidences( model.corner( corner_uuids[0] ) );
    geode::index_t corner_incidence_count{ 0 };
    for( const auto& corner_incidence : corner_incidences )
    {
        corner_incidence_count++;
        OPENGEODE_EXCEPTION( corner_incidence.id() == line_uuids[0]
                                 || corner_incidence.id() == line_uuids[1],
            "CornerIncidenceRange iteration result is not correct" );
    }
    OPENGEODE_EXCEPTION( corner_incidence_count == 2,
        "CornerIncidenceRange should iterates on 2 Lines" );

    const auto& line_incidences =
        model.incidences( model.line( line_uuids[0] ) );
    geode::index_t line_incidence_count{ 0 };
    for( const auto& line_incidence : line_incidences )
    {
        line_incidence_count++;
        OPENGEODE_EXCEPTION( line_incidence.id() == surface_uuids[0],
            "LineIncidenceRange iteration result is not correct" );
    }
    OPENGEODE_EXCEPTION( line_incidence_count == 1,
        "LineIncidenceRange should iterates on 1 Surface" );
}

class OtherModel : public geode::Section,
                   public geode::AddComponents< 3, geode::Blocks >
{
public:
    OtherModel() = default;
};

int main()
{
    using namespace geode;

    try
    {
        Section model;
        SectionBuilder builder( model );
        OtherModel other;

        // This Section represents a house (with one triangle and one square as
        // in children sketches)
        auto corner_uuids = add_corners( model, builder );
        auto line_uuids = add_lines( model, builder );
        auto surface_uuids = add_surfaces( model, builder );

        add_corner_line_relation( model, builder, corner_uuids, line_uuids );
        add_line_surface_relation( model, builder, line_uuids, surface_uuids );
        test_boundary_ranges( model, corner_uuids, line_uuids, surface_uuids );
        test_incidence_ranges( model, corner_uuids, line_uuids, surface_uuids );

        std::string file_io{ "test." + model.native_extension() };
        save_section( model, file_io );

        Section model2;
        load_section( model2, file_io );

        Logger::info( "TEST SUCCESS" );
        return 0;
    }
    catch( ... )
    {
        return geode_lippincott();
    }
}