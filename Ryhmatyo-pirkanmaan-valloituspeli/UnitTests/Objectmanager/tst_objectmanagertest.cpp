#include <QString>
#include <QtTest>
#include "objectmanager.hh"
#include "gameeventhandler.hh"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
class ObjectmanagerTest : public QObject
{
    Q_OBJECT

public:
    ObjectmanagerTest();

private Q_SLOTS:
    //Test that getTile gives tile which has right coordinates
    void testTileCoordinate();
    //Test that tile count is same as area of map
    void testTilesCount();
private:
    std::shared_ptr<ObjectManager> manager_;
    std::shared_ptr<GameEventHandler> handler_;
    long unsigned int x_ = 10;
    long unsigned int y_ = 10;
};

ObjectmanagerTest::ObjectmanagerTest()
{
    std::shared_ptr<ObjectManager> manager (new ObjectManager());
    std::shared_ptr<GameEventHandler> handler (new GameEventHandler());
    handler_ = handler;
    manager_ = manager;
    Course::WorldGenerator& world = Course::WorldGenerator::getInstance();
    world.addConstructor<Course::Forest>(1);
    world.generateMap(x_,y_,2,manager_,handler_);
}

void ObjectmanagerTest::testTileCoordinate()
{
    Course::Coordinate coordinate(1,1);
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    QCOMPARE(1, tile->getCoordinate().x());
    QCOMPARE(1, tile->getCoordinate().y());
}

void ObjectmanagerTest::testTilesCount()
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles = manager_->getTilesForMap();
    QCOMPARE(tiles.size(), y_*x_);
}


QTEST_APPLESS_MAIN(ObjectmanagerTest)

#include "tst_objectmanagertest.moc"
