#include <QString>
#include <QtTest>
#include "gameengine.hh"

class GameengineTest : public QObject
{
    Q_OBJECT

public:
    GameengineTest();

private Q_SLOTS:
    //Test that current player swap when someone is ending round
    void testPlayersName();
    //Test that roundnumber doestn't change when someone is ending round and
    //everybody hasnä't done their turn yet
    void testRoundNumber();
    //Test that current player number is right
    void testPlayerNumber();
private:
    std::shared_ptr<GameEventHandler> handler_pointer_;
    std::shared_ptr<ObjectManager> manager_pointer_;
    std::shared_ptr<Gameengine> gameengine_;
};

GameengineTest::GameengineTest()
{
    std::shared_ptr<GameEventHandler> handler_pointer (new GameEventHandler());
    std::shared_ptr<ObjectManager> manager_pointer (new ObjectManager());
    std::shared_ptr<Gameengine> gameengine (new Gameengine());
    std::vector<std::string> players = {"saku", "henkka", "matti", "joona"};
    handler_pointer_ = handler_pointer;
    manager_pointer_ = manager_pointer;
    gameengine_ = gameengine;
    gameengine_->setHandlerAndManager(handler_pointer_,manager_pointer_);
    gameengine_->setPlayers(players, 4);
}

void GameengineTest::testPlayersName()
{
    std::vector<QString> players = {"saku", "henkka", "matti", "joona"};
    for (auto player : players)
    {
        QCOMPARE(gameengine_->getPlayerName(), player);
        gameengine_->roundHandler();
    }
}

void GameengineTest::testRoundNumber()
{
    for (int i = 1; i <= 4; i++)
    {
        QString round = "2";
        QCOMPARE(gameengine_->getRound(), round);
        gameengine_->roundHandler();
    }
}

void GameengineTest::testPlayerNumber()
{
    for (int i = 1; i <= 4; i++)
    {
        QCOMPARE(gameengine_->getPlayerNumber(), i);
        gameengine_->roundHandler();
    }
}

QTEST_APPLESS_MAIN(GameengineTest)

#include "tst_gameenginetest.moc"
