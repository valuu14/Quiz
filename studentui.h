#ifndef STUDENTUI_H
#define STUDENTUI_H
#include <QMainWindow>
#include <QListWidget>
#include <QDebug>
#include <QPushButton>
#include <vector>
#include "controller.h"
#include "filterui.h"

class studentui : public QMainWindow
{
public slots:
    void onClickStart();
    void nextEvent();
    void onClickAdd();
    void onClickAnswer();
    void onClickFilter();
public:
    studentui(QWidget* parent = nullptr, Controller* ctrl = nullptr);
    void listPopulate(std::vector<Question*> v){
        for (auto q : v){
            std::string str;
            (*q).toString(str);
            correctAnswers.push_back(QString::fromStdString(q->getId()));
            correctAnswers.push_back(QString::fromStdString(q->getCorrectAnswer()));
            m_copy->addItem(QString::fromStdString(str));
        }
        QString qstr =
                "Press 'Start quiz' to start the quiz!\n"
                "Press 'Filter question' to filter by subject and then press 'Start quiz'.\n"
                "Select an answer from each question.\n"
                "Press 'Next question' to go to the next question and to answer to the current question.\n"
                "You can add a question to the review list by simply pressing the button 'Add to review list'.";
        m_quizList->addItem(qstr);
    }

    void prepQuestion();
    void increaseScore(){
        score++;
    }

private:
    QWidget *createCentralWidget();

    Controller* m_controller;
    QListWidget* m_quizList, *m_reviewList, *m_copy;
    QPushButton* startBtn;
    QPushButton* filterBtn;
    QPushButton* addBtn;
    QPushButton* deleteBtn;
    QPushButton* nextBtn;
    int score;
    QVector<QString> correctAnswers;
    filterui* m_filter;
    std::vector<Question*> m_filtered;
};

#endif // STUDENTUI_H
