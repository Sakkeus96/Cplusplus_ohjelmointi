#include "dialogtile.hh"
#include "ui_dialogtile.h"
#include "iostream"

DialogTile::DialogTile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTile)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked(bool)), this,
            SLOT(okButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(cancelButtonClicked()));
    connect(ui->returnButton, SIGNAL(clicked(bool)), this,
            SLOT(returnButtonClicked()));
    connect(ui->outpostButton, SIGNAL(clicked(bool)), this,
            SLOT(outpostButtonClicked()));
    connect(ui->buildButton, SIGNAL(clicked(bool)), this,
            SLOT(buildButtonClicked()));
    connect(ui->farmButton, SIGNAL(clicked(bool)), this,
            SLOT(farmButtonClicked()));
    connect(ui->freeButton, SIGNAL(clicked(bool)), this,
            SLOT(freeButtonClicked()));
    connect(ui->moveButton, SIGNAL(clicked(bool)), this,
            SLOT(moveButtonClicked()));
    connect(ui->oremineButton, SIGNAL(clicked(bool)), this,
            SLOT(oremineButtonClicked()));
    connect(ui->bankButton, SIGNAL(clicked(bool)), this,
            SLOT(bankButtonClicked()));
    connect(ui->sawmillButton, SIGNAL(clicked(bool)), this,
            SLOT(sawmillButtonClicked()));
    connect(ui->removeButton, SIGNAL(clicked(bool)), this,
            SLOT(removeButtonClicked()));
    connect(ui->workerButton, SIGNAL(clicked(bool)), this,
            SLOT(workerButtonClicked()));
    connect(ui->directionText, SIGNAL(editingFinished()), this,
            SLOT(directionTextChanged()));
    connect(ui->minerButton, SIGNAL(clicked(bool)), this,
            SLOT(minerButtonClicked()));
    connect(ui->lumberjackButton, SIGNAL(clicked(bool)), this,
            SLOT(lumberjackButtonClicked()));
    buttons_.append(ui->buildButton);
    buttons_.append(ui->cancelButton);
    buttons_.append(ui->farmButton);
    buttons_.append(ui->freeButton);
    buttons_.append(ui->moveButton);
    buttons_.append(ui->okButton);
    buttons_.append(ui->oremineButton);
    buttons_.append(ui->bankButton);
    buttons_.append(ui->sawmillButton);
    buttons_.append(ui->outpostButton);
    buttons_.append(ui->removeButton);
    buttons_.append(ui->workerButton);
    buttons_.append(ui->minerButton);
    buttons_.append(ui->lumberjackButton);
    ui->directionLabel->setVisible(false);
    ui->helpBrowser->setVisible(false);
    ui->directionText->setVisible(false);
    ui->directionText->setEnabled(false);
}

DialogTile::~DialogTile()
{
    delete ui;
}

void DialogTile::okButtonClicked()
{
    if (direction_ == "N" || direction_ == "NE" || direction_ == "E"
            || direction_ == "SE" || direction_ == "S" || direction_ == "SW"
            || direction_ == "W" || direction_ == "NW")
    {
        emit giveAction(object_, action_, direction_);
        accept();
    }
}

void DialogTile::cancelButtonClicked()
{
    for (auto button : buttons_)
    {
        button->setEnabled(false);
        button->setStyleSheet("background-color: white");
    }
    ui->directionLabel->setVisible(false);
    ui->helpBrowser->setVisible(false);
    ui->directionText->setVisible(false);
    ui->directionText->setEnabled(false);
    pushButtonModifer();
}

void DialogTile::returnButtonClicked()
{
    reject();
}

void DialogTile::saveData(std::pair<int, std::shared_ptr<Course::TileBase>>
                          owner, std::vector<std::string>
                          possible_buildings_vector)
{
    owner_ = owner.first;
    tile_ = owner.second;
    possible_buildings_vector_ = possible_buildings_vector;
    std::string text = "Tile - " + tile_->getType();
    this->setWindowTitle(QString::fromStdString(text));
    setBuildingsAndCitizens();
    pushButtonModifer();
}

void DialogTile::pushButtonModifer()
{
    direction_ = "N";
    int own_tile = 1;
    int empty_tile = 0;
    if (owner_ == own_tile)
    {
        ui->outpostButton->setEnabled(true);
        ui->farmButton->setEnabled(true);
        ui->oremineButton->setEnabled(true);
        ui->bankButton->setEnabled(true);
        ui->sawmillButton->setEnabled(true);
        std::vector<std::shared_ptr<Course::WorkerBase>> citizens =
                tile_->getWorkers();
        if (citizens.size() > 0)
        {
            for (auto citizen : citizens)
            {
                if (citizen->getType() == "BasicWorker")
                {
                    ui->workerButton->setEnabled(true);
                }
                if (citizen->getType() == "Miner")
                {
                    ui->minerButton->setEnabled(true);
                }
                if (citizen->getType() == "Lumberjack")
                {
                    ui->lumberjackButton->setEnabled(true);
                }
            }
        }
    }
    if (owner_ == empty_tile)
    {
        ui->outpostButton->setEnabled(true);
    }
}

void DialogTile::outpostButtonClicked()
{
    object_ = "Outpost";
    cancelButtonClicked();
    ui->outpostButton->setStyleSheet("background-color: red");
    std::vector<std::string>::iterator it = std::find(
                possible_buildings_vector_.begin(),
                possible_buildings_vector_.end(), object_);
    ui->buildButton->setEnabled(true);
    if (it == possible_buildings_vector_.end())
    {
        ui->buildButton->setEnabled(false);
    }
    if (!tile_->hasSpaceForBuildings(1))
    {
        ui->buildButton->setEnabled(false);
    }
    ui->cancelButton->setEnabled(true);
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings =
            tile_->getBuildings();
    if (buildings.size() > 0)
    {
        for (auto building : buildings)
        {
            std::string type = building->getType();
            if (type == "Outpost")
            {
                ui->removeButton->setEnabled(true);
            }
        }
    }
}


void DialogTile::farmButtonClicked()
{
    object_ = "Farm";
    cancelButtonClicked();
    ui->farmButton->setStyleSheet("background-color: red");
    std::vector<std::string>::iterator it = std::find(
                possible_buildings_vector_.begin(),
                possible_buildings_vector_.end(), object_);
    ui->buildButton->setEnabled(true);
    if (it == possible_buildings_vector_.end())
    {
        ui->buildButton->setEnabled(false);
    }
    if (!tile_->hasSpaceForBuildings(1))
    {
        ui->buildButton->setEnabled(false);
    }
    ui->cancelButton->setEnabled(true);
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings =
            tile_->getBuildings();
    if (buildings.size() > 0)
    {
        for (auto building : buildings)
        {
            std::string type = building->getType();
            if (type == "Farm")
            {
                ui->removeButton->setEnabled(true);
            }
        }
    }
}

void DialogTile::buildButtonClicked()
{
    ui->removeButton->setStyleSheet("background-color: white");
    ui->buildButton->setStyleSheet("background-color: red");
    ui->okButton->setEnabled(true);
    ui->okButton->setDefault(true);
    action_ = "build";
}

void DialogTile::removeButtonClicked()
{
    ui->buildButton->setStyleSheet("background-color: white");
    ui->removeButton->setStyleSheet("background-color: red");
    ui->okButton->setEnabled(true);
    ui->okButton->setDefault(true);
    action_ = "remove";
}

void DialogTile::workerButtonClicked()
{
    cancelButtonClicked();
    ui->workerButton->setStyleSheet("background-color: red");
    ui->moveButton->setEnabled(true);
    ui->freeButton->setEnabled(true);
    ui->cancelButton->setEnabled(true);
    object_ = "BasicWorker";
}

void DialogTile::moveButtonClicked()
{
    direction_ = "";
    ui->freeButton->setStyleSheet("background-color: white");
    ui->moveButton->setStyleSheet("background-color: red");
    ui->okButton->setEnabled(true);
    ui->okButton->setDefault(true);
    action_ = "move";
    ui->directionLabel->setVisible(true);
    ui->helpBrowser->setVisible(true);
    ui->directionText->setVisible(true);
    ui->directionText->setEnabled(true);
}

void DialogTile::freeButtonClicked()
{
    direction_ = "N";
    ui->moveButton->setStyleSheet("background-color: white");
    ui->freeButton->setStyleSheet("background-color: red");
    ui->okButton->setEnabled(true);
    ui->okButton->setDefault(true);
    action_ = "free";
    ui->directionLabel->setVisible(false);
    ui->helpBrowser->setVisible(false);
    ui->directionText->setVisible(false);
    ui->directionText->setEnabled(false);
}

void DialogTile::oremineButtonClicked()
{
    object_ = "Oremine";
    cancelButtonClicked();
    ui->oremineButton->setStyleSheet("background-color: red");
    std::vector<std::string>::iterator it = std::find(
                possible_buildings_vector_.begin(),
                possible_buildings_vector_.end(), object_);
    ui->buildButton->setEnabled(true);
    if (it == possible_buildings_vector_.end())
    {
        ui->buildButton->setEnabled(false);
    }
    if (!tile_->hasSpaceForBuildings(1))
    {
        ui->buildButton->setEnabled(false);
    }
    ui->cancelButton->setEnabled(true);

    std::vector<std::shared_ptr<Course::BuildingBase>> buildings =
            tile_->getBuildings();
    if (buildings.size() > 0)
    {
        for (auto building : buildings)
        {
            std::string type = building->getType();
            if (type == "Oremine")
            {
                ui->removeButton->setEnabled(true);
            }
        }
    }
}

void DialogTile::bankButtonClicked()
{
    object_ = "Bank";
    cancelButtonClicked();
    ui->bankButton->setStyleSheet("background-color: red");
    std::vector<std::string>::iterator it = std::find(
                possible_buildings_vector_.begin(),
                possible_buildings_vector_.end(), object_);
    ui->buildButton->setEnabled(true);
    if (it == possible_buildings_vector_.end())
    {
        ui->buildButton->setEnabled(false);
    }
    if (!tile_->hasSpaceForBuildings(1))
    {
        ui->buildButton->setEnabled(false);
    }
    ui->cancelButton->setEnabled(true);

    std::vector<std::shared_ptr<Course::BuildingBase>> buildings =
            tile_->getBuildings();
    if (buildings.size() > 0)
    {
        for (auto building : buildings)
        {
            std::string type = building->getType();
            if (type == "Bank")
            {
                ui->removeButton->setEnabled(true);
            }
        }
    }

}

void DialogTile::sawmillButtonClicked()
{
    object_ = "Sawmill";
    cancelButtonClicked();
    ui->sawmillButton->setStyleSheet("background-color: red");
    std::vector<std::string>::iterator it = std::find(
                possible_buildings_vector_.begin(),
                possible_buildings_vector_.end(), object_);
    ui->buildButton->setEnabled(true);
    if (it == possible_buildings_vector_.end())
    {
        ui->buildButton->setEnabled(false);
    }
    if (!tile_->hasSpaceForBuildings(1))
    {
        ui->buildButton->setEnabled(false);
    }
    ui->cancelButton->setEnabled(true);

    std::vector<std::shared_ptr<Course::BuildingBase>> buildings =
            tile_->getBuildings();
    if (buildings.size() > 0)
    {
        for (auto building : buildings)
        {
            std::string type = building->getType();
            if (type == "Sawmill")
            {
                ui->removeButton->setEnabled(true);
            }
        }
    }
}

void DialogTile::minerButtonClicked()
{
    cancelButtonClicked();
    ui->minerButton->setStyleSheet("background-color: red");
    ui->moveButton->setEnabled(true);
    ui->freeButton->setEnabled(true);
    ui->cancelButton->setEnabled(true);
    object_ = "Miner";
}

void DialogTile::lumberjackButtonClicked()
{
    cancelButtonClicked();
    ui->lumberjackButton->setStyleSheet("background-color: red");
    ui->moveButton->setEnabled(true);
    ui->freeButton->setEnabled(true);
    ui->cancelButton->setEnabled(true);
    object_ = "Lumberjack";
}

void DialogTile::directionTextChanged()
{
    direction_ = ui->directionText->text().toUpper().toStdString();
}

void DialogTile::setBuildingsAndCitizens()
{
    std::string buildings = "Current buildings: ";
    std::string citizens = "Current citizens: ";;
    if (tile_->getBuildingCount() > 0)
    {
        for (auto building : tile_->getBuildings())
        {
            buildings = buildings + building->getType() + ", ";
        }
    }
    if (tile_->getWorkerCount() > 0)
    {
        for (auto citizen : tile_->getWorkers())
        {
            citizens = citizens + citizen->getType() + ", ";
        }
    }
    ui->Citizen->setText(QString::fromStdString(citizens));
    ui->buildings->setText(QString::fromStdString(buildings));
}


