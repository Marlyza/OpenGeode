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

#include <geode/mesh/builder/vertex_set_builder.h>
#include <geode/mesh/common.h>

namespace geode
{
    class OpenGeodeVertexSet;
}

namespace geode
{
    /*!
     * Implementation class for VertexSetBuilder using OpenGeode data structure
     */
    class opengeode_mesh_api OpenGeodeVertexSetBuilder : public VertexSetBuilder
    {
    public:
        OpenGeodeVertexSetBuilder( VertexSet& vertex_set );

    private:
        void do_create_vertex() override;

        void do_create_vertices( index_t nb ) override;

        void do_delete_vertices(
            const std::vector< bool >& to_delete ) override;

    private:
        OpenGeodeVertexSet& geode_vertex_set_;
    };
} // namespace geode
