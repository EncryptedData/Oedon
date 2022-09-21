
#include "DataVariant.h"

namespace Oedon
{

    DataVariant::DataVariant() :
        type{DataVariantType::Empty}
    {
    }

    DataVariant::DataVariant(const DataVariant & other)
    {
        type = other.type;

        switch (type)
        {
            case DataVariantType::Mesh:
                mesh = other.mesh;
                break;
            case DataVariantType::Points:
                points = std::vector<glm::vec3>(other.points);
                break;
            default:
                break;
        }
    }

    DataVariant::~DataVariant()
    {
        DestroyCurrentType();
    }

    void DataVariant::SetType(DataVariantType dataVariantType)
    {
        DestroyCurrentType();

        switch(dataVariantType)
        {
            case DataVariantType::Mesh:
                new (&mesh) Mesh;
                break;
            case DataVariantType::Points:
                new (&points) std::vector<Point>();
                break;
            default:
                break;
        }

        type = dataVariantType;
    }

    void DataVariant::DestroyCurrentType()
    {
        switch (type)
        {
            case DataVariantType::Mesh:
                mesh.~Mesh();
                break;
            case DataVariantType::Points:
                points.~vector();
                break;
            default:
                break;
        }
    }
}
