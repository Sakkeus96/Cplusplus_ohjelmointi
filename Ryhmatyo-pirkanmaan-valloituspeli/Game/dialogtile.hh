#ifndef DIALOGTILE_HH
#define DIALOGTILE_HH

#include <QDialog>
#include "vector"
#include "QPushButton"
#include "tiles/tilebase.h"
#include "core/coordinate.h"
/**
 * @brief DialogTile allows the player to build and remove buildings
 * and move and free citizens.
 */
namespace Ui {
class DialogTile;
}

class DialogTile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTile(QWidget *parent = 0);
    ~DialogTile();

private slots:

    /**
     * @brief Emits signal and accept dialog if moving direction is right
     * @post Exception guarantee: No-throw
     */
    void okButtonClicked();

    /**
     * @brief Enables all buttons except return button and returns dialog
     * to the original state
     * @post Exception guarantee: Basic
     */
    void cancelButtonClicked();

    /**
     * @brief Rejects dialog
     * @post Exception guarantee: No-throw
     */
    void returnButtonClicked();

    /**
     * @brief Saves number that tells tile's owner and tile and
     * buildings you can build. Changes the title to match the tile type and
     * shows current buildings and citizens and initializes the dialog buttons
     * @param Pair which have number that tells tile's owner and tile
     * @param Buildings you can build
     * @post Exception guarantee: Basic
     */
    void saveData(std::pair<int, std::shared_ptr<Course::TileBase> > owner,
                  std::vector<std::string> possible_buildings_vector);

    /**
     * @brief Initializes the dialog buttons based on who owns the tile and
     * which citizens are in the tile
     * @post Exception guarantee: No-throw
     */
    void pushButtonModifer();

    /**
     * @brief Enables remove button if tile has outpost and enables
     * build button if you have resources to build it and saves object
     * @post Exception guarantee: Basic
     */
    void outpostButtonClicked();

    /**
     * @brief Enables remove button if tile has farm and enables
     * build button if you have resources to build it and saves object
     * @post Exception guarantee: Basic
     */
    void farmButtonClicked();

    /**
     * @brief Enables ok button and saves action
     * @post Exception guarantee: No-throw
     */
    void buildButtonClicked();

    /**
     * @brief Enables ok button and saves action
     * @post Exception guarantee: No-throw
     */
    void removeButtonClicked();

    /**
     * @brief Enables free button and move button saves action
     * @post Exception guarantee: No-throw
     */
    void workerButtonClicked();

    /**
     * @brief Enables ok button and saves action and opens label where
     * player can write direction
     * @post Exception guarantee: No-throw
     */
    void moveButtonClicked();

    /**
     * @brief Enables ok button and saves action
     * @post Exception guarantee: No-throw
     */
    void freeButtonClicked();

    /**
     * @brief Enables remove button if tile has oremine and enables
     * build button if you have resources to build it and saves object
     * @post Exception guarantee: Basic
     */
    void oremineButtonClicked();

    /**
     * @brief Enables remove button if tile has bank and enables
     * build button if you have resources to build it and saves object
     * @post Exception guarantee: Basic
     */
    void bankButtonClicked();

    /**
     * @brief Enables remove button if tile has sawmill and enables
     * build button if you have resources to build it and saves object
     * @post Exception guarantee: Basic
     */
    void sawmillButtonClicked();

    /**
     * @brief Enables free button and move button saves action
     * @post Exception guarantee: No-throw
     */
    void minerButtonClicked();

    /**
     * @brief Enables free button and move button saves action
     * @post Exception guarantee: No-throw
     */
    void lumberjackButtonClicked();

    /**
     * @brief Saves direction from label and uppers it.
     * @post Exception guarantee: No-throw
     */
    void directionTextChanged();

    /**
     * @brief Shows current buildings and citizens and saves them to labels
     * @post Exception guarantee: No-throw
     */
    void setBuildingsAndCitizens();

signals:

    /**
     * @brief Signals object, action  and direction of move.
     * @param Object which is building or citizen
     * @param Action which is remove, build,
     * move or free
     * @param Direction of move which is N,NW,W,SW,S,SE,E or NE
     */
    void giveAction(std::string object, std::string action, std::string direction);

private:
    Ui::DialogTile *ui;
    int owner_;
    std::shared_ptr<Course::TileBase> tile_;
    QVector<QPushButton *> buttons_;
    std::string object_;
    std::string action_;
    std::string direction_;
    std::vector<std::string> possible_buildings_vector_;

};

#endif // DIALOGTILE_HH
