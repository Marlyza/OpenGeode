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

#include <geode/georepresentation/core/relationship_manager.h>

std::vector< geode::uuid > create_uuids(
    geode::RelationshipManager& relationships )
{
    geode::index_t nb{ 6 };
    std::vector< geode::uuid > uuids;
    for( auto unused : geode::Range{ nb } )
    {
        geode_unused( unused );
        geode::uuid cur_uuid;
        relationships.add_component( cur_uuid );
        uuids.push_back( cur_uuid );
    }
    return uuids;
}

void add_boundary_relations( geode::RelationshipManager& relations,
    const std::vector< geode::uuid >& uuids )
{
    relations.add_boundary_relation( uuids[0], uuids[1] );
    relations.add_boundary_relation( uuids[0], uuids[2] );
    relations.add_boundary_relation( uuids[0], uuids[3] );
    relations.add_boundary_relation( uuids[1], uuids[2] );
    relations.add_boundary_relation( uuids[1], uuids[3] );
    relations.add_boundary_relation( uuids[2], uuids[3] );
    relations.add_boundary_relation( uuids[4], uuids[0] );
    relations.add_boundary_relation( uuids[4], uuids[5] );
    relations.add_boundary_relation( uuids[5], uuids[0] );
    // Repete last relation to test duplications
    relations.add_boundary_relation( uuids[5], uuids[0] );
}

void add_items_in_collections( geode::RelationshipManager& relations,
    const std::vector< geode::uuid >& uuids )
{
    relations.add_item_in_collection( uuids[1], uuids[5] );
    relations.add_item_in_collection( uuids[2], uuids[5] );
    relations.add_item_in_collection( uuids[3], uuids[5] );
    relations.add_item_in_collection( uuids[5], uuids[4] );
    relations.add_item_in_collection( uuids[0], uuids[4] );
    // Repete last relation to test duplications
    relations.add_item_in_collection( uuids[0], uuids[4] );
}

void test_uuid( const geode::RelationshipManager& relations,
    const geode::uuid& uuid,
    geode::index_t nb_boundaries,
    geode::index_t nb_incidences,
    geode::index_t nb_items,
    geode::index_t nb_collections )
{
    std::string message_boundary = uuid.string() + " should have "
                                   + std::to_string( nb_boundaries )
                                   + " boundary(ies)";
    OPENGEODE_EXCEPTION(
        relations.nb_boundaries( uuid ) == nb_boundaries, message_boundary );

    std::string message_incidence = uuid.string() + " should have "
                                    + std::to_string( nb_incidences )
                                    + " incidence(s)";
    OPENGEODE_EXCEPTION(
        relations.nb_incidences( uuid ) == nb_incidences, message_incidence );

    std::string message_item = uuid.string() + " should have "
                               + std::to_string( nb_boundaries ) + " item(s)";
    OPENGEODE_EXCEPTION( relations.nb_items( uuid ) == nb_items, message_item );

    std::string message_collection = uuid.string() + " should have "
                                     + std::to_string( nb_collections )
                                     + " collection(s)";
    OPENGEODE_EXCEPTION( relations.nb_collections( uuid ) == nb_collections,
        message_collection );
}

void test_relations( const geode::RelationshipManager& relations,
    const std::vector< geode::uuid >& uuids )
{
    test_uuid( relations, uuids[0], 2, 3, 0, 1 );
    test_uuid( relations, uuids[1], 1, 2, 0, 1 );
    test_uuid( relations, uuids[2], 2, 1, 0, 1 );
    test_uuid( relations, uuids[3], 3, 0, 0, 1 );
    test_uuid( relations, uuids[4], 0, 2, 2, 0 );
    test_uuid( relations, uuids[5], 1, 1, 3, 1 );
}

int main()
{
    using namespace geode;

    try
    {
        RelationshipManager relationships;
        auto uuids = create_uuids( relationships );

        // This Relationships do not represent anything.
        add_boundary_relations( relationships, uuids );
        add_items_in_collections( relationships, uuids );
        test_relations( relationships, uuids );

        relationships.save_relationships( "." );
        RelationshipManager reloaded_relationships;
        reloaded_relationships.load_relationships( "." );
        test_relations( reloaded_relationships, uuids );

        Logger::info( "TEST SUCCESS" );
        return 0;
    }
    catch( ... )
    {
        return geode_lippincott();
    }
}
