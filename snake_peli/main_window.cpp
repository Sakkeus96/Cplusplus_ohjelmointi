/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Saku Laitinen, 274957, saku.laitinen@tuni.fi             #
####################################################################
*/

#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent)
{
    // Pelikentan leveys ja korkeus
    height_ = 6;
    width_ = 6;
    max_score_ = height_*width_;
    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);
    rng_.seed(time(NULL));

    // Laittaa pelin aloituksen kannalta tarpeettomat
    // napit ja teksti alueen piiloon tai pois toiminnasta
    ui_.pauseButton->setVisible(false);
    ui_.winOrLoseText->setVisible(false);
    ui_.resetButton->setDisabled(true);
    ui_.pauseButton->setDisabled(true);

    // Varjataan lcd numerot
    ui_.lcdNumberScore->setAutoFillBackground(true);
    ui_.lcdNumberSec->setAutoFillBackground(true);
    ui_.lcdNumberHighscore->setAutoFillBackground(true);
    QPalette pal = ui_.lcdNumberScore->palette();
    pal.setColor(QPalette::Normal, QPalette::Window, Qt::green);
    ui_.lcdNumberScore->setPalette(pal);
    pal.setColor(QPalette::Normal, QPalette::Window, Qt::blue);
    ui_.lcdNumberSec->setPalette(pal);
    pal.setColor(QPalette::Normal, QPalette::Window, Qt::yellow);
    ui_.lcdNumberHighscore->setPalette(pal);

    // Annetaan vaikeustasolle maksimi- ja minimiarvot
    ui_.levelSelecter->setMinimum(1);
    ui_.levelSelecter->setMaximum(5);

    connect(&second_timer_, &QTimer::timeout, this, &MainWindow::timer);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    char key = static_cast<char>(event->key());
    // Jos peli on tauolla, niin se kaynnistyy uudelleen alla olevilla
    // kirjaimilla
    if (paused_ && (key == 'A' || key == 'S' || key == 'D' || key == 'W'))
    {
        // Ajastimen nopeus riippuu seka vaikeustasosta etta jo saaduista
        // pisteista
        timer_.start(1000/ui_.levelSelecter->value()
                     -15/ui_.levelSelecter->value()*score_);
        second_timer_.start(1000);
        ui_.pauseButton->setEnabled(true);
        paused_ = false;
    }
    // Hyvaksytaan vain A,S,D ja W liikesuunnat
    if (key == 'A' || key == 'S' || key == 'D' || key == 'W')
    {
        key_pressed_ = key;
    }
}

void MainWindow::on_playButton_clicked()
{
    ui_.winOrLoseText->setVisible(false);
    ui_.pauseButton->setVisible(true);
    ui_.playButton->setVisible(false);
    ui_.resetButton->setEnabled(true);
    ui_.pauseButton->setEnabled(true);
    ui_.levelSelecter->setDisabled(true);
    ui_.playButton->setDisabled(true);

    second_ = 0;
    ui_.lcdNumberSec->display(second_);
    ui_.lcdNumberScore->display(score_);
    ui_.lcdNumberHighscore->display(high_score_);

    // Luodaan madon paa ja ruoka
    const QRectF food_rect(0, 0, 1, 1);
    const QPen food_contours(Qt::green, 0);
    const QBrush food_filler(Qt::green);
    food_ = scene_.addRect(food_rect, food_contours, food_filler);
    const QRectF head_rect(0, 0, 1, 1);
    const QPen head_contours(Qt::white, 0);
    QColor selectedColor(0,0,RGB_VALUE_MAX_);
    const QBrush head_filler(selectedColor);
    head_ = scene_.addRect(head_rect, head_contours, head_filler);
    head_->setPos(width_/2, height_/2);

    set_food();
    adjustSceneArea();

    timer_.start(1000/ui_.levelSelecter->value());
    second_timer_.start(1000);

    // Nollataan edelliset liikesuunnat, jos sellaisia on
    key_pressed_ = ' ';
    previous_direction_ = ' ';
}

void MainWindow::moveSnake()
{
    QPointF old_head_pos = head_->scenePos();
    QPointF new_head_pos = old_head_pos;
    wrong_direction();

    if (key_pressed_ == 'A')
    {
        new_head_pos  = new_head_pos + QPoint(-1, 0);
    }
    if (key_pressed_ == 'S')
    {
        new_head_pos = new_head_pos + QPoint(0, +1);
    }
    if (key_pressed_ == 'D')
    {
        new_head_pos = new_head_pos + QPoint(+1, 0);
    }
    if (key_pressed_ == 'W')
    {       
        new_head_pos = new_head_pos + QPoint(0, -1);
    }
    if (crashed_in_to_the_wall(new_head_pos))
    {
        ui_.winOrLoseText->setVisible(true);
    }
    else if (snake_ate_his_body(new_head_pos))
    {
        ui_.winOrLoseText->setVisible(true);
    }
    else
    {
        move_body(new_head_pos);
        previous_direction_ = key_pressed_;
        if (head_->scenePos() == food_->scenePos())
        {
            snake_ate_food();
        }
    }
}

void MainWindow::adjustSceneArea()
{
    const QRectF area(0, 0, width_, height_);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

void MainWindow::snake_ate_food()
{
    ++score_;
    ui_.lcdNumberScore->display(score_);

    // Ajastimen nopeus riippuu seka vaikeustasosta etta jo saaduista
    // pisteista
    timer_.start(1000/ui_.levelSelecter->value()-
                 15/ui_.levelSelecter->value()*score_);
    QGraphicsRectItem* body = nullptr;

    // Muuttuja on kerroin varinvaihtumiselle ja kerroin riippuu pelin koosta
    // eli pelin maksimipisteista
    int color_changer = RGB_VALUE_MAX_/max_score_;
    const QRectF body_rect(0, 0, 1, 1);
    const QPen body_contours(Qt::white, 0);

    // Vari savyttyy saatujen pisteiden mukaan. Lahella maksimipisteita
    // vartalon vari lahenee paan varia
    QColor selectedColor(0,RGB_VALUE_MAX_-color_changer*score_,RGB_VALUE_MAX_);
    const QBrush body_filler(selectedColor);
    body = scene_.addRect(body_rect, body_contours, body_filler);
    body->setX(head_->x());
    body->setY(head_->y());
    body->setVisible(false);
    body_.push_back(body);
    if (!victory())
    {
        set_food();
    }
    snake_ate_food_in_the_last_move_ = true;
}

void MainWindow::timer()
{
    ++second_;
    ui_.lcdNumberSec->display(second_);
}

bool MainWindow::crashed_in_to_the_wall(const QPointF &new_head_pos)
{
    qreal x =new_head_pos.x();
    qreal y = new_head_pos.y();
    if (x == -1 || x == width_ || y == -1 || y == height_)
    {
        lost_game();
        on_resetButton_clicked();
        return true;
    }
    return false;
}

void MainWindow::move_body(QPointF &new_head_pos)
{
    head_->setPos(new_head_pos);

    // Liikutetaan kaarmeen vartaloo, jos sellainen loytyy
    if (body_.size() > 0)
    {
        // Etsitaan kaarmeen paan aikaisempi sijainti
        QPointF previous_head_location = QPoint(0,0);
        if (key_pressed_ == 'A')
        {
            previous_head_location = QPoint(new_head_pos.x()+1,
                                            new_head_pos.y());
        }
        if (key_pressed_ == 'S')
        {
            previous_head_location = QPoint(new_head_pos.x(),
                                            new_head_pos.y()-1);
        }
        if (key_pressed_ == 'D')
        {
            previous_head_location = QPoint(new_head_pos.x()-1,
                                            new_head_pos.y());
        }
        if (key_pressed_ == 'W')
        {
            previous_head_location = QPoint(new_head_pos.x(),
                                            new_head_pos.y()+1);
        }
        int indeks = 0;
        indeks = body_.size() - 1;

        // Jos kaarme ei syonyt viime liikkeellaan, niin liikutetaan kaarmeen
        // jokaista osaa yhden eteenpain
        if (snake_ate_food_in_the_last_move_ == false)
        {
            QPointF previous_part = previous_head_location;
            // Muuttujan memory tarkoitus on tallentaa edellisen osan
            // alkuperainen paikka muistiin, johon seuraava osa sitten liikkuu
            QPointF memory = QPoint(0,0);

            // Kaydaan kaarmeen ruumis siina jarjestyksessa lavitse, etta
            // viimeisin lisays tulee ensin.
            while (indeks >= 0)
            {
                memory = body_.at(indeks)->scenePos();
                body_.at(indeks)->setVisible(true);
                body_.at(indeks)->setPos(previous_part);
                previous_part = memory;
                --indeks;
            }
        }
        // Jos kaarme soi viime liikkeellaan, niin paan liikkumisen lisaksi
        // tuodaan uusi osa kaarmeesta nakyviin. Muu vartalo ei liiku
        else
        {
            body_.at(indeks)->setVisible(true);
            snake_ate_food_in_the_last_move_ = false;
        }

    }
}

bool MainWindow::snake_ate_his_body(QPointF &new_head_pos)
{
    for (uint i = 1; i < body_.size(); ++i)
    {
        if (body_.at(i)->x() == new_head_pos.x() &&
                body_.at(i)->y() == new_head_pos.y())
        {
            lost_game();
            on_resetButton_clicked();
            return true;
        }
    }
    return false;
}

bool MainWindow::victory()
{
    if (body_.size() == max_score_)
    {
        ui_.winOrLoseText->setVisible(true);
        QString win_text = "You won! Congratulations! Time spend: ";
        std::string seconds_string = std::to_string(second_);
        QString seconds_qstring = QString::fromStdString(seconds_string);
        win_text = win_text + seconds_qstring;
        ui_.winOrLoseText->setText(win_text);
        on_resetButton_clicked();
        return true;
    }
    return false;
}

void MainWindow::set_food()
{
    std::uniform_int_distribution<int> game_size(0, height_-1);
    int x = 0;
    int y = 0;

    // Etsii ruualle paikan, missa kaarme ei sijaitse
    while(true)
    {
        x = game_size(rng_);
        y = game_size(rng_);
        bool empty_space_found = true;
        if (head_->x() == x && head_->y() == y)
        {
            empty_space_found = false;
        }
        for (auto s : body_)
        {
            if (s->x() == x && s->y() == y)
            {
                empty_space_found = false;
            }
        }
        if (empty_space_found)
        {
            break;
        }
    }
    food_->setPos(x,y);
}

void MainWindow::save_highscore()
{
    if (score_ > high_score_)
    {
        high_score_ = score_;
    }
}

void MainWindow::wrong_direction()
{
    if (previous_direction_ == 'A' && key_pressed_ == 'D')
    {
        key_pressed_ = previous_direction_;
    }
    if (previous_direction_ == 'D' && key_pressed_ == 'A')
    {
        key_pressed_ = previous_direction_;
    }
    if (previous_direction_ == 'W' && key_pressed_ == 'S')
    {
        key_pressed_ = previous_direction_;
    }
    if (previous_direction_ == 'S' && key_pressed_ == 'W')
    {
        key_pressed_ = previous_direction_;
    }
}

void MainWindow::lost_game()
{
    QString lose_text = "Game Over, You lose! Time spend: ";
    std::string seconds_string = std::to_string(second_);
    QString seconds_qstring = QString::fromStdString(seconds_string);
    lose_text = lose_text + seconds_qstring;
    ui_.winOrLoseText->setText(lose_text);
}

void MainWindow::on_resetButton_clicked()
{
    ui_.playButton->setEnabled(true);
    ui_.levelSelecter->setEnabled(true);
    ui_.resetButton->setDisabled(true);
    ui_.pauseButton->setDisabled(true);
    ui_.pauseButton->setVisible(false);
    ui_.playButton->setVisible(true);

    save_highscore();
    ui_.lcdNumberHighscore->display(high_score_);
    score_ = 0;

    second_timer_.stop();
    timer_.stop();

    delete head_;
    delete food_;
    for (auto s : body_)
    {
        delete s;
    }
    body_.clear();
}

void MainWindow::on_pauseButton_clicked()
{
    timer_.stop();
    second_timer_.stop();
    ui_.pauseButton->setDisabled(true);
    paused_ = true;
}


