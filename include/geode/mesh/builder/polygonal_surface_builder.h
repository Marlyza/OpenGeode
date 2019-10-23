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

#pragma once

#include <vector>

#include <geode/basic/factory.h>

#include <geode/mesh/builder/vertex_set_builder.h>
#include <geode/mesh/common.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
    FORWARD_DECLARATION_DIMENSION_CLASS( PolygonalSurface );

    struct PolygonEdge;
    struct PolygonVertex;
} // namespace geode

namespace geode
{
    /*!
     * Interface class to represent the builder of a PolygonalSurface
     */
    template < index_t dimension >
    class PolygonalSurfaceBuilder : public VertexSetBuilder
    {
    public:
        /*!
         * Create the builder associated with a PolygonalSurface.
         * @param[in] mesh The PolygonalSurface to build/modify
         */
        static std::unique_ptr< PolygonalSurfaceBuilder< dimension > > create(
            PolygonalSurface< dimension >& mesh );

        /*!
         * Set coordinates to a vertex. This vertex should be created before.
         * @param[in] vertex_id The vertex, in [0, nb_vertices()-1].
         * @param[in] point The vertex coordinates
         */
        void set_point( index_t vertex_id, const Point< dimension >& point );

        /*!
         * Create a new point with associated coordinates.
         * @param[in] point The point to create
         * @return the index of the created point
         */
        index_t create_point( const Point< dimension >& point );

        /*!
         * Create a new polygon from vertices.
         * @param[in] vertices The ordered vertices defining the polygon to
         * create
         * @return the index of the created polygon
         */
        index_t create_polygon( const std::vector< index_t >& vertices );

        /*!
         * Modify a polygon vertex.
         * @param[in] polygon_vertex The index of the polygon vertex to modify
         * @param[in] vertex_id Index of the mesh vertex to set as polygon
         * vertex
         */
        void set_polygon_vertex(
            const PolygonVertex& polygon_vertex, index_t vertex_id );

        /*!
         * Set a polygon adjacent through an edge.
         * @param[in] polygon_edge The index of the polygon edge
         * @param[in] adjacent_id Index of the adjacent polygon
         */
        void set_polygon_adjacent(
            const PolygonEdge& polygon_edge, index_t adjacent_id );

        /*!
         * Compute all the adjacencies between the surface polygons
         */
        void compute_polygon_adjacencies();

        /*!
         * Compute the adjacencies between the given surface polygons
         * @param[in] polygons_to_connect Set of polygons for which compute
         * adjacencies
         */
        void compute_polygon_adjacencies(
            const std::vector< index_t >& polygons_to_connect );

        /*!
         * Delete a set of surface polygons
         * @param[in] to_delete Vector of size polygonal_surface_.nb_polygons().
         * If to_delete[i] is true the polygon of index i is deleted, else it is
         * kept.
         */
        void delete_polygons( const std::vector< bool >& to_delete );

        /*!
         * Return one polygon with one of the vertices matching given vertex.
         * @param[in] vertex_id Index of the vertex.
         * @detail If vertex is isolated (no incident polygon), default
         * PolygonVertex is returned.
         */
        const PolygonVertex& polygon_around_vertex( index_t vertex_id ) const;

        /*!
         * Set a polygon vertex to a given vertex.
         * @param[in] polygon_vertex PolygonVertex corresponding to the vertex.
         * @param[in] vertex_id Index of the vertex.
         */
        void associate_polygon_vertex_to_vertex(
            const PolygonVertex& polygon_vertex, index_t vertex_id );

    protected:
        PolygonalSurfaceBuilder(
            PolygonalSurface< dimension >& polygonal_surface )
            : VertexSetBuilder( polygonal_surface ),
              polygonal_surface_( polygonal_surface )
        {
        }

        friend class PolygonalSurface< dimension >;
        void copy( const PolygonalSurface< dimension >& polygonal_surface );

    private:
        virtual void do_set_point(
            index_t vertex_id, const Point< dimension >& point ) = 0;

        void do_delete_vertices( const std::vector< bool >& to_delete ) final;

        virtual void do_delete_surface_vertices(
            const std::vector< bool >& to_delete ) = 0;

        virtual void do_set_polygon_vertex(
            const PolygonVertex& polygon_vertex, index_t vertex_id ) = 0;

        virtual void do_create_polygon(
            const std::vector< index_t >& vertices ) = 0;

        virtual void do_delete_polygons(
            const std::vector< bool >& to_delete ) = 0;

        virtual void do_set_polygon_adjacent(
            const PolygonEdge& polygon_edge, index_t adjacent_id ) = 0;

    private:
        PolygonalSurface< dimension >& polygonal_surface_;
    };
    ALIAS_2D_AND_3D( PolygonalSurfaceBuilder );

    template < index_t dimension >
    using PolygonalSurfaceBuilderFactory = Factory< MeshType,
        PolygonalSurfaceBuilder< dimension >,
        PolygonalSurface< dimension >& >;
    ALIAS_2D_AND_3D( PolygonalSurfaceBuilderFactory );
} // namespace geode
