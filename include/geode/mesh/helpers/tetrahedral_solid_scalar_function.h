/*
 * Copyright (c) 2019 - 2022 Geode-solutions. All rights reserved.
 */

#pragma once

#include <geode/basic/pimpl.h>

#include <geode/mesh/common.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
    FORWARD_DECLARATION_DIMENSION_CLASS( TetrahedralSolid );
} // namespace geode

namespace geode
{
    template < index_t dimension >
    class TetrahedralSolidScalarFunction
    {
        OPENGEODE_TEMPLATE_ASSERT_3D( dimension );

    public:
        TetrahedralSolidScalarFunction(
            TetrahedralSolidScalarFunction< dimension >&& other );
        ~TetrahedralSolidScalarFunction();

        /*!
         * Create a new object function from a TetrahedralSolid, a name, and a
         * value.
         * Throws an exception if an attribute with the same name exists.
         */
        static TetrahedralSolidScalarFunction< dimension > create(
            const TetrahedralSolid< dimension >& solid,
            absl::string_view function_name,
            double value );

        /*!
         * Finds an object function that already exists in the given
         * TetrahedralSolid, from its given name.
         * Throws an exception if no attribute with the same name exists.
         */
        static TetrahedralSolidScalarFunction< dimension > find(
            const TetrahedralSolid< dimension >& solid,
            absl::string_view function_name );

        void set_value( index_t vertex_index, double value );

        double value( index_t vertex_index ) const;

        double value(
            const Point< dimension >& point, index_t tetrahedron_id ) const;

    private:
        TetrahedralSolidScalarFunction(
            const TetrahedralSolid< dimension >& solid,
            absl::string_view function_name );

        TetrahedralSolidScalarFunction(
            const TetrahedralSolid< dimension >& solid,
            absl::string_view function_name,
            double value );

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
    ALIAS_3D( TetrahedralSolidScalarFunction );
} // namespace geode