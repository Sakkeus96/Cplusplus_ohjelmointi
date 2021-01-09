#include "dialog.hh"
#include "ui_dialog.h"
#include <iostream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->playerCount, SIGNAL(valueChanged(int)), this,
            SLOT(playerCount(int)));
    ui->playerName_2->setVisible(false);
    ui->playerName_3->setVisible(false);
    ui->playerName_4->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->nameFailed->setVisible(false);
    ui->okButton->setDefault(true);
    this->setWindowTitle("Players");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::playerCount(int value)
{
    playerscount_ = value;
    if (playerscount_ == 1)
    {
        ui->playerName_2->setVisible(false);
        ui->playerName_3->setVisible(false);
        ui->playerName_4->setVisible(false);
        ui->playerName_2->clear();
        ui->playerName_3->clear();
        ui->playerName_4->clear();
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
    }
    if (playerscount_ == 2)
    {
        ui->playerName_2->setVisible(true);
        ui->playerName_3->setVisible(false);
        ui->playerName_4->setVisible(false);
        ui->playerName_3->clear();
        ui->playerName_4->clear();
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
    }
    if (playerscount_ == 3)
    {
        ui->playerName_2->setVisible(true);
        ui->playerName_3->setVisible(true);
        ui->playerName_4->setVisible(false);
        ui->playerName_4->clear();
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(false);
    }
    if (playerscount_ == 4)
    {
        ui->playerName_2->setVisible(true);
        ui->playerName_3->setVisible(true);
        ui->playerName_4->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
    }
}

bool Dialog::playersToVector()
{
    std::string playername_1 = ui->playerName_1->text().toStdString();
    std::string playername_2;
    std::string playername_3;
    std::string playername_4;
    if (playerscount_ == 1)
    {
        players_.push_back(playername_1);
    }
    if (playerscount_ == 2)
    {
        playername_2 = ui->playerName_2->text().toStdString();
        players_.push_back(playername_1);
        players_.push_back(playername_2);
    }
    if (playerscount_ == 3)
    {
        playername_2 = ui->playerName_2->text().toStdString();
        playername_3 = ui->playerName_3->text().toStdString();
        players_.push_back(playername_1);
        players_.push_back(playername_2);
        players_.push_back(playername_3);
    }
    if (playerscount_ == 4)
    {
        playername_2 = ui->playerName_2->text().toStdString();
        playername_3 = ui->playerName_3->text().toStdString();
        playername_4 = ui->playerName_4->text().toStdString();
        players_.push_back(playername_1);
        players_.push_back(playername_2);
        players_.push_back(playername_3);
        players_.push_back(playername_4);
    }
    for (auto name : players_)
    {
        if (name.empty())
        {
            ui->nameFailed->setVisible(true);
            players_.clear();
            ui->playerName_1->clear();
            ui->playerName_2->clear();
            ui->playerName_3->clear();
            ui->playerName_4->clear();
            return false;
        }
    }
    return true;
}


void Dialog::on_okButton_clicked()
{
    if (playersToVector())
    {
        emit playerSignal(playerscount_,players_);
        accept();
    }
}
