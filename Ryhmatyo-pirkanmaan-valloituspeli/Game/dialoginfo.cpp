#include "dialoginfo.hh"
#include "ui_dialoginfo.h"

Dialoginfo::Dialoginfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoginfo)
{
    ui->setupUi(this);
    this->setWindowTitle("Resource info");
}

Dialoginfo::~Dialoginfo()
{
    delete ui;
}
