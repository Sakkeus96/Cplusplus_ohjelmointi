#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include "mapwindow.hh"
#include "vector"

/**
 * @brief Dialog saves names of the players and playercount and
 * signal them to mapwindow.
 */
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    /**
     * @brief Saves players to vector if playernames are not empty
     * @post Exception guarantee: Strong
     * @return
     * True - Saving was successful \n
     * False - Saving failed. \n
     */
    bool playersToVector();

signals:

    /**
     * @brief Saves players to vector if playernames are not empty
     * @param Number of players
     * @param Players names
     */
    void playerSignal(int playercount, std::vector<std::string> players);

private slots:

    /**
     * @brief Emit signal and accept dialog if playersToVector returns true
     * @post Exception guarantee: Strong
     */
    void on_okButton_clicked();

    /**
     * @brief Gets playercount from spinbox and opens QlineEdits
     * based on playercount
     * @param Number of players from spinbox
     * @post Exception guarantee: No-throw
     */
    void playerCount(int value);

private:
    Ui::Dialog *ui;
    int playerscount_ = 1;
    std::vector<std::string> players_ = {};
};

#endif // DIALOG_HH
