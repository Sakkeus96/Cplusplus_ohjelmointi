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
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: Saku Laitinen, 274957, saku.laitinen@tuni.fi             #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>


/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /* \brief Construct a MainWindow.
     *
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the Snake's bearing when certain keys get pressed.
     *
     * \param[in] event Contains data on pressed and released keys.
     */
    void keyPressEvent(QKeyEvent* event) override;


private slots:

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* \brief Move the Snake by a square and check for collisions.
     *
     * The game ends if a wall or the Snake itself gets in the way.
     * When a food gets eaten a point is gained and the Snake grows.
     */
    void moveSnake();

    /* \ Muuttaa nappien tilaa, pysayttaa ajastimet, tallentaa lcd naytolle
     * huipputuloksen ja poistaa esineita pelikentalta. Kutsutaan myos
     * kaarmeen kuollessa.
     */
    void on_resetButton_clicked();

    /* \ Pysayttaa molemmat ajastimet
     */
    void on_pauseButton_clicked();


private:

    /* \brief Make the play field visible and fit it into the view.
     *
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    /* \ Kaarmeen syodessa ruokaa lisataan vartaloon uusi osa ja nopeutetaan
     * kaarmeen vauhtia. Paivitetaan piste taulua ja tarkistetaan voitto
     */
    void snake_ate_food();

    /* \ Pitaa sekuntikellon ajantasalla
     */
    void timer();

    /* \ Tarkistaa, etta osuuko kaarme seinaan ja palauttaa totuusarvon
     * \ Parametrina on paan seuraava sijainti liikkumisen jalkeen
     */
    bool crashed_in_to_the_wall(const QPointF &new_head_pos);

    /* \ Liikuttaa kaarmeen paata ja muuta vartaloa
     * \ Parametrina paan seuraava sijainti liikkumisen jalkeen
     */
    void move_body(QPointF &new_head_pos);

    /* \ Tarkistaa, etta osuuko kaarmeen paa sen vartaloonsa ja palauttaa
     * totuusarvon
     * \ Parametrina on paan seuraava sijainti liikkumsen jalkeen
     */
    bool snake_ate_his_body(QPointF &new_head_pos);

    /* \ Tarkistaa, onko kaarme kasvanut tayteen mittaansa eli tayttaako
     * kaarme pelialueen. Tulostaa voitto tekstin ja palauttaa totuusarvon
     */
    bool victory();

    /* \ Asettaa ruuan sellaiseen paikkaan missa ei kaarme sijaitse
     */
    void set_food();

    /* \ Tallentaa parhaimman tuloksen
     */
    void save_highscore();

    /* \ Tarkistaa, etta onko kaarme liikkumassa saantojen vastaiseen suuntaan
     */
    void wrong_direction();

    /* \ Tulostaa haviamisesta ilmoittavan tekstin pelaajalle
     */
    void lost_game();


    Ui::MainWindow ui_;                 /**< Accesses the UI widgets. */
    QGraphicsRectItem* food_ = nullptr; /**< The food item in the scene. */
    QGraphicsScene scene_;              /**< Manages drawable objects. */
    QTimer timer_;                      /**< Triggers the Snake to move. */
    std::default_random_engine rng_;    /**< Randomizes food locations. */
    char key_pressed_;                  /**< Kayttajan antama liike suunta. */
    QGraphicsRectItem* head_ = nullptr; /**< Kaarmeen paa. */
    int height_;                        /**< Pelikentan korkeus. */
    int width_;                         /**< Pelikentan leveys. */
    int second_ = 0;                    /**< Sekuntikellon sekuntti. */
    int score_ = 0;                     /**< Pelin pisteet. */
    int high_score_ = 0;                /**< Parhaat pisteet. */
    long unsigned int max_score_;       /**< Pelin maksimipisteet. */
    char previous_direction_;           /**< Kaarmeen edellinen suunta. */
    std::vector<QGraphicsItem*> body_;  /**< Kaarmeen vartalo vectori. */
    bool snake_ate_food_in_the_last_move_ = false;
                                        /**< Totuusarvo kaarmeen syonnista. */
    QTimer second_timer_;               /**< Sekuntikellon ajastin. */
    const int RGB_VALUE_MAX_ = 255;     /**< Vartalon varipaletin maksimi. */
    bool paused_ = false;               /**< Pysahdyksen totuusarvo. */
};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
