#ifndef LUMBERJACK_H
#define LUMBERJACK_H

#include "workers/workerbase.h"
#include "core/resourcemaps.h"
#include "objectmanager.hh"
#include "gameeventhandler.hh"
#include "customresourcemap.hh"
#include "tiles/tilebase.h"


/**
 * @brief The Lumberjack class represents a wood-specified worker in the game.
 *
 * Worker has following production-efficiency: \n
 * * Money - 0.95 \n
 * * Food - 0.96 \n
 * * Wood - 1.30 \n
 * * Stone - 1.00 \n
 * * Ore - 1.00 \n
 *
 * Lumberjack consume Food and money. \n
 * * 1 Food - Or BasicWorker refuses to work. \n
 * * 1 Money - Or BasicWorker works at 25% efficiency. \n

 */
class Lumberjack : public Course::WorkerBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Lumberjack() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param descriptions contains descriptions and flavor texts.
     */
    Lumberjack(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<ObjectManager>& objectmanager,
                const std::shared_ptr<Course::PlayerBase>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    LUMBERJACK_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    LUMBERJACK_WORKER_EFFICIENCY
                );

    /**
     * @brief Default destructor.
     */
    virtual ~Lumberjack() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Check if the worker can be placed on the Tile according to
     * it's placement rule. Only rule is that the Tile must have same owner
     * as the worker.
     * @param target is the Tile that worker is being placed on.
     * @return
     * True - If baseclass' method return true and target Tile has space
     * for worker.
     * False - If both conditions aren't met.
     * @note Override to change placement rules for derived worker.
     * @post Exception guarantee: Basic
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

    /**
     * @brief Performs the Lumberjack's default action.
     */
    virtual void doSpecialAction() override;

    /**
     * @brief Returns Lumberjack's efficiency at resource production.
     * Worker consumes FOOD and MONEY. Resource consumption and resource
     * focus determine final multiplier that is based on WORKER_EFFICIENCY.
     *
     * @return
     */
    virtual const Course::ResourceMapDouble tileWorkAction() override;

private:

}; // class Lumberjack




#endif // LUMBERJACK_H
