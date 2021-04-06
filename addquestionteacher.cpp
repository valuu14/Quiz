#include "addquestionteacher.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <string>
#include <QDebug>

void addQuestionTeacher::add()
{
    Question* q = new Question;
    q->setId(id->text().toStdString());
    q->setText(text->text().toStdString());
    q->setSubject(subject->text().toStdString());
    q->setType(type->text().toStdString());
    std::string p_a[3];
    p_a[0] = p_a0->text().toStdString();
    p_a[1] = p_a1->text().toStdString();
    p_a[2] = p_a2->text().toStdString();
    q->setPossibleAnswers(p_a);
    q->setCorrectAnswer(c_a->text().toStdString());

    bool added = m_controller->addQuestion(q, 1);
    if (added){
        //m_list
        qDebug() << "Question added";
    }
    else qDebug() << "Question not added";
    close();
}

addQuestionTeacher::addQuestionTeacher(Controller* ctrl, QMainWindow* parent) : QMainWindow(parent)
{
    m_controller = ctrl;
    this->setWindowTitle("Add Question");
    this->setMinimumSize(600, 300);

    QWidget* centralW = createCentralWidget();
    this->setCentralWidget(centralW);
}

QWidget *addQuestionTeacher::createCentralWidget()
{
    QWidget* widget = new QWidget(this);
    QGridLayout* grid = new QGridLayout;
    QLabel* idLabel = new QLabel("ID", this);
    QLabel* textLabel = new QLabel("Question", this);
    QLabel* subLabel = new QLabel("Subject", this);
    QLabel* typeLabel = new QLabel("Type", this);
    QLabel* possAnswers = new QLabel("Possible answers", this);
    QLabel* corrAnswer = new QLabel("Correct answer", this);
    id = new QLineEdit(this);
    text = new QLineEdit(this);
    subject = new QLineEdit(this);
    type = new QLineEdit(this);
    p_a0 = new QLineEdit(this);
    p_a1 = new QLineEdit(this);
    p_a2 = new QLineEdit(this);
    c_a = new QLineEdit(this);
    grid->addWidget(idLabel, 0, 0);
    grid->addWidget(id, 0, 1, 1, 2);
    grid->addWidget(textLabel, 1, 0);
    grid->addWidget(text, 1, 1, 1, 2);
    grid->addWidget(subLabel, 2, 0);
    grid->addWidget(subject, 2, 1, 1, 2);
    grid->addWidget(typeLabel, 3, 0);
    grid->addWidget(type, 3, 1, 1, 2);
    grid->addWidget(possAnswers, 4, 0);
    grid->addWidget(p_a0, 4, 1, 1, 2);
    grid->addWidget(p_a1, 5, 1, 1, 2);
    grid->addWidget(p_a2, 6, 1, 1, 2);
    grid->addWidget(corrAnswer, 7, 0);
    grid->addWidget(c_a, 7, 1, 1, 2);

    QPushButton* addButton = new QPushButton("Add question", this);
    grid->addWidget(addButton, 8, 1, 1, 2);
    connect(addButton, &QPushButton::pressed, this, &addQuestionTeacher::add);

    widget->setLayout(grid);
    return widget;
}
