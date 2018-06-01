#include <sempr/sempr.hpp>
#include <sempr/core/IncrementalIDGeneration.hpp>

// include our new and stylish SpecialEntity
#include <SpecialEntity.hpp>
// and since we want to persist it, also the database-code
#include <SpecialEntity_odb.h>

#include <iostream>
#include <vector>

using namespace sempr;

int main(int argc, char** args)
{
    // create a storage-module
    storage::ODBStorage::Ptr storage(new storage::ODBStorage());
    // and a module that updates the storage on changes
    processing::DBUpdateModule::Ptr updater(new processing::DBUpdateModule(storage));

    // connect everything in a core component
    core::Core sempr;
    sempr.addModule(updater);

    // set the id-generator to use a human-readable-incremental-id-strategy.
    // (the default uses prefixed uuids)
    core::IDGenerator::getInstance().setStrategy(
        std::unique_ptr<core::IncrementalIDGeneration>(new core::IncrementalIDGeneration(storage))
    );

    // create a few SpecialEntity-objects
    SpecialEntity::Ptr e1(new SpecialEntity());
    SpecialEntity::Ptr e2(new SpecialEntity());
    SpecialEntity::Ptr e3(new SpecialEntity());

    e1->text_ = "This is SpecialEntity-1";
    e2->text_ = "There are only two rules to succes:";
    e3->text_ = "1. Never share everything you know.";

    // add the the system. (they get persisted by the DBUpdateModule)
    sempr.addEntity(e1);
    sempr.addEntity(e2);
    sempr.addEntity(e3);

    updater->updateDatabase();

    // --- list all entities
    std::vector<entity::Entity::Ptr> all;
    storage->loadAll(all);
    for (auto e : all) {
        std::cout << "Entity: " << e->id() << '\n';
    }

    return 0;
}
