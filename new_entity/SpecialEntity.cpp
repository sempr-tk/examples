#include <SpecialEntity.hpp>
#include <SpecialEntity_odb.h>

SEMPR_ENTITY_SOURCE(SpecialEntity);

SpecialEntity::SpecialEntity()
    : SpecialEntity(new sempr::core::IDGen<SpecialEntity>())
{
}

SpecialEntity::SpecialEntity(const sempr::core::IDGenBase* idgen)
    : sempr::entity::Entity(idgen)
{
    text_ = "Hello World!";
}
