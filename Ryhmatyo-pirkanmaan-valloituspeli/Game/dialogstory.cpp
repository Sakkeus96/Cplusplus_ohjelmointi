#include "dialogstory.hh"
#include "ui_dialogstory.h"

Dialogstory::Dialogstory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogstory)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    timer_ = timer;
    connect(timer, SIGNAL(timeout()), this, SLOT(textChange()));
    connect(ui->continueButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    story_ = "Earth is contaminated with radiation. Because of that, all"
                    " humans live below the surface of the Earth, communicating "
                    "with each other through video screens and never going anywhere. ";
    ui->storyBrowser->setText(story_);
    timer_->start(3000);
    this->setWindowTitle("Story");
}

Dialogstory::~Dialogstory()
{
    delete ui;
}

void Dialogstory::textChange()
{
    if (counter_ == 1)
    {
        story_ = story_ + "This is about to change when some groups decide to go"
                          " up in Northern Europe in a country named Finland. "
                          "The more specific location is in Pirkanmaa province. \n \n";
        ui->storyBrowser->setText(story_);
        ++counter_;
    }
    else if (counter_ == 2)
    {
        story_ = story_ + "At this moment, there are some groups below the "
                          "surface of Pirkanmaa province. All of these groups "
                          "are going to up at the same time. ";
        ui->storyBrowser->setText(story_);
        ++counter_;
    }
    else if (counter_ == 3)
    {
        story_ = story_ + "Because of this, groups need to conquer areas and "
                          "gather resources to survive. Only one group can gain "
                          "control in Pirkanmaa. Control is gained when the group"
                          " has enough resources compared to others. \n \n";
        ui->storyBrowser->setText(story_);
        ++counter_;
    }
    else if (counter_ == 4)
    {
        story_ = story_ + "The leaders of these great groups are named...\n \n";
        ui->storyBrowser->setText(story_);
        ++counter_;
    }
    else
    {
        story_ = story_ + "Please click continue";
        ui->storyBrowser->setText(story_);
        ui->continueButton->setStyleSheet("background-color: green");
        timer_->stop();
    }
}
