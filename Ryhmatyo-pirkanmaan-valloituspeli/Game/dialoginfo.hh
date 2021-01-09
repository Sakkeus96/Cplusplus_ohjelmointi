#ifndef DIALOGINFO_HH
#define DIALOGINFO_HH

#include <QDialog>

/**
 * @brief Shows information about resource costs and resource produtions
 */
namespace Ui {
class Dialoginfo;
}

class Dialoginfo : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoginfo(QWidget *parent = 0);
    ~Dialoginfo();

private:
    Ui::Dialoginfo *ui;
};

#endif // DIALOGINFO_HH
