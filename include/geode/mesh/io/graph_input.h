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

#include <geode/basic/factory.h>

#include <geode/mesh/common.h>
#include <geode/mesh/io/vertex_set_input.h>

namespace geode
{
    class Graph;
} // namespace geode

namespace geode
{
    /*!
     * API function for loading an Graph.
     * The adequate loader is called depending on the filename extension.
     * @param[out] graph Loaded Graph.
     * @param[in] filename Path to the file to load.
     */
    void opengeode_mesh_api load_graph(
        Graph& graph, const std::string& filename );

    class opengeode_mesh_api GraphInput : public VertexSetInput
    {
    public:
        virtual ~GraphInput() = default;

    protected:
        GraphInput( Graph& graph, std::string filename );

        Graph& graph()
        {
            return graph_;
        }

    private:
        Graph& graph_;
    };

    using GraphInputFactory =
        Factory< std::string, GraphInput, Graph&, std::string >;
} // namespace geode
