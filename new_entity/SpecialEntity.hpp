#ifndef SPECIALENTITY_HPP_
#define SPECIALENTITY_HPP_

#include <sempr/entity/Entity.hpp>
#include <memory>

#pragma db object
class SpecialEntity : public sempr::entity::Entity {
    SEMPR_ENTITY
public:
    using Ptr = std::shared_ptr<SpecialEntity>;
    SpecialEntity();
    SpecialEntity(const sempr::core::IDGenBase*);


    // just some random data member to persist.
    std::string text_;
};


#endif
