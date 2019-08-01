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

#include <fstream>
#include <memory>
#include <unordered_map>

#include <bitsery/ext/std_map.h>

#include <geode/basic/uuid.h>

#include <geode/mesh/core/bitsery_archive.h>
#include <geode/mesh/core/mesh_type.h>

#include <geode/georepresentation/core/bitsery_archive.h>

namespace geode
{
    namespace detail
    {
        template < typename Component >
        class ComponentsStorage
        {
        public:
            using ComponentPtr = std::unique_ptr< Component >;
            using ComponentsStore = std::unordered_map< uuid, ComponentPtr >;
            using Iterator = typename ComponentsStore::const_iterator;

            index_t nb_components() const
            {
                return components_.size();
            }

            const Component& component( const uuid& id ) const
            {
                return *components_.at( id );
            }

            Component& component( const uuid& id )
            {
                return *components_.at( id );
            }

            Iterator begin() const
            {
                return components_.begin();
            }

            Iterator end() const
            {
                return components_.end();
            }

            void add_component( ComponentPtr component )
            {
                components_.emplace( component->id(), std::move( component ) );
            }

            void save_components( const std::string& filename ) const
            {
                std::ofstream file{ filename, std::ofstream::binary };
                TContext context{};
                register_basic_serialize_pcontext( std::get< 0 >( context ) );
                register_mesh_serialize_pcontext( std::get< 0 >( context ) );
                register_georepresentation_serialize_pcontext(
                    std::get< 0 >( context ) );
                Serializer archive{ file, &context };
                archive.object( *this );
                bitsery::AdapterAccess::getWriter( archive ).flush();
                OPENGEODE_EXCEPTION( std::get< 1 >( context ).isValid(),
                    "Error while writing file: " + filename );
            }

            void delete_component( const uuid& id )
            {
                components_.erase( components_.find( id ) );
            }

            void load_components( const std::string& filename )
            {
                std::ifstream file{ filename, std::ifstream::binary };
                TContext context{};
                register_basic_deserialize_pcontext( std::get< 0 >( context ) );
                register_mesh_deserialize_pcontext( std::get< 0 >( context ) );
                register_georepresentation_deserialize_pcontext(
                    std::get< 0 >( context ) );
                Deserializer archive{ file, &context };
                archive.object( *this );
                auto& reader = bitsery::AdapterAccess::getReader( archive );
                OPENGEODE_EXCEPTION(
                    reader.error() == bitsery::ReaderError::NoError
                        && reader.isCompletedSuccessfully()
                        && std::get< 1 >( context ).isValid(),
                    "Error while reading file: " + filename );
            }

        private:
            friend class bitsery::Access;
            template < typename Archive >
            void serialize( Archive& archive )
            {
                archive.ext( components_,
                    bitsery::ext::StdMap{ components_.max_size() },
                    [&archive]( uuid& id, ComponentPtr& item ) {
                        archive.object( id );
                        archive.ext( item, bitsery::ext::StdSmartPtr{} );
                    } );
            }

        private:
            ComponentsStore components_;
        };
    } // namespace detail
} // namespace geode
