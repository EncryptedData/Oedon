#pragma once

#include "FatVertex.h"
#include "Points.h"
#include "Mesh.h"
#include <vector>

namespace Oedon
{
    enum class DataVariantType
    {
        Empty,
        Mesh,
        Points,
    };

    struct DataVariant
    {
        explicit DataVariant();

        DataVariant(const DataVariant& other);

        ~DataVariant();

        void SetType(DataVariantType dataVariantType);

        DataVariantType type;
        union
        {
           Mesh mesh;
           std::vector<Point> points;
        };

    private:
        void DestroyCurrentType();
    };
}
