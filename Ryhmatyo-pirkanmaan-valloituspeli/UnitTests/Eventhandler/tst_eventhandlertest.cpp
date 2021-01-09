#include <QString>
#include <QtTest>
#include "gameeventhandler.hh"

class EventhandlerTest : public QObject
{
    Q_OBJECT

public:
    EventhandlerTest();

private Q_SLOTS:
    //Test that players objects have right names
    void testPlayersName();
    //Test that resources at the begin are same as starting resources
    void testResources();
    //Test that modifyResources works right
    void testModifyResources();
    //Test that checkIfEnoughResources works right
    void testCheckIfEnoughResources();
private:
    std::shared_ptr<GameEventHandler> handler_;
};

EventhandlerTest::EventhandlerTest()
{
    std::shared_ptr<GameEventHandler> handler (new GameEventHandler());
    handler_ = handler;
}

void EventhandlerTest::testPlayersName()
{
    std::vector<std::string> players = {"matti", "saku"};
    handler_->addPlayers(2, players);
    for (int i = 1; i <= 2; ++i)
    {
        std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(i);
        QCOMPARE(player->getName(), players.at(i-1));
    }
}

void EventhandlerTest::testResources()
{
    std::vector<int> starting_resourcevector = {25,25,25,25,25};
    for (int i = 1; i <= 2; ++i)
    {
        std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(i);
        std::vector<int> player_resources = handler_->getResourceVector(player);
        for (int j = 0; j < 5 ; ++j)
        {
            QCOMPARE(player_resources.at(j), starting_resourcevector.at(j));
        }
    }

}

void EventhandlerTest::testModifyResources()
{
    std::map<Course::BasicResource, int> resource = {
        {Course::BasicResource::MONEY, 10},
        {Course::BasicResource::FOOD, 10},
        {Course::BasicResource::WOOD, 10},
        {Course::BasicResource::STONE, 10},
        {Course::BasicResource::ORE, 10}
    };
    std::vector<int> starting_resources_plus_resurces_vector = {35,35,35,35,35};
    for (int i = 1; i <= 2; ++i)
    {
        std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(i);
        handler_->modifyResources(player,resource);
        std::vector<int> player_resources = handler_->getResourceVector(player);
        for (int j = 0; j < 5 ; ++j)
        {
            QCOMPARE(player_resources.at(j),
                     starting_resources_plus_resurces_vector.at(j));
        }
    }
}

void EventhandlerTest::testCheckIfEnoughResources()
{
    std::map<Course::BasicResource, int> resource = {
        {Course::BasicResource::MONEY, 1},
        {Course::BasicResource::FOOD, 1},
        {Course::BasicResource::WOOD, 1},
        {Course::BasicResource::STONE, 1},
        {Course::BasicResource::ORE, 1}
    };
    for (int i = 1; i <= 2; ++i)
    {
        std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(i);
        QVERIFY(handler_->checkIfEnoughResources(player,resource));
    }
}

QTEST_APPLESS_MAIN(EventhandlerTest)

#include "tst_eventhandlertest.moc"
