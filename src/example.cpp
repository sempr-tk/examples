#include <sempr/sempr.hpp>
#include <sempr/entity/spatial/Point.hpp>
#include <sempr/core/IncrementalIDGeneration.hpp>
#include <Point_odb.h>
#include <iostream>
#include <vector>

using namespace sempr;

int main(int argc, char** args)
{
    storage::ODBStorage::Ptr storage(new storage::ODBStorage());
    processing::DBUpdateModule::Ptr updater(new processing::DBUpdateModule(storage));

    core::Core sempr(storage);
    sempr.addModule(updater);

    core::IDGenerator::getInstance().setStrategy(
        std::unique_ptr<core::IncrementalIDGeneration>(new core::IncrementalIDGeneration(storage))
    );

    // add a point
    entity::Point::Ptr p1(new entity::Point());
    entity::Point::Ptr p2(new entity::Point());

    char* wkt1 = (char*) "POINT (0 0)";
    char* wkt2 = (char*) "POINT (3 4)";
    p1->geometry()->importFromWkt(&wkt1);
    p2->geometry()->importFromWkt(&wkt2);

    sempr.addEntity(p1);
    sempr.addEntity(p2);

    std::cout << "distance: " << p1->geometry()->Distance(p2->geometry()) << '\n';

    // --- list all geometries:
    std::vector<entity::Geometry::Ptr> all;
    storage->loadAll(all);
    for (auto geo : all) {
        std::cout << "Geometry: " << geo->id() << '\n';
    }

    return 0;
}
