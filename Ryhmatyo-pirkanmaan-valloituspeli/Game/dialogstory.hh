#ifndef DIALOGSTORY_HH
#define DIALOGSTORY_HH

#include <QDialog>
#include "QTimer"

/**
 * @brief Shows the background story of the game
 */
namespace Ui {
class Dialogstory;
}

class Dialogstory : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogstory(QWidget *parent = 0);
    ~Dialogstory();
public slots:

    /**
     * @brief Change text after every 2 seconds.
     * @post Exception guarantee: No-throw
     */
    void textChange();

private:
    Ui::Dialogstory *ui;
    int counter_ = 1;
    QString story_;
    QTimer* timer_;
};

#endif // DIALOGSTORY_HH
