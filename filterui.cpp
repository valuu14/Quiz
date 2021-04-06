#include "filterui.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QListWidget>
#include <QLineEdit>
#include <string>

filterui::filterui(Controller* ctrl, QWidget* parent) : QMainWindow(parent){
    m_controller = ctrl;
    this->setWindowTitle("Filter");
    this->setMinimumSize(400, 200);

    QWidget* centralW = createCentralWidget();
    this->setCentralWidget(centralW);
}

void filterui::filter()
{
    std::string str = m_edit->text().toStdString();
    m_controller->filterQuestions(str, m_filtered);
    close();
}

QWidget *filterui::createCentralWidget()
{
    QWidget* widget = new QWidget(this);
    QGridLayout* grid = new QGridLayout;
    QPushButton* filter = new QPushButton("Filter", this);
    m_edit = new QLineEdit(this);

    grid->addWidget(m_edit, 0, 1, 1, 2);
    grid->addWidget(filter, 0 ,3);

    widget->setLayout(grid);

    connect(filter, &QPushButton::clicked, this, &filterui::filter);

    return widget;





























//    QWidget* topWidget = new QWidget(this);
//    QWidget* bottomWidget = new QWidget(this);
//    QVBoxLayout* vLayout = new QVBoxLayout;
//    QGridLayout* gridQuizButtons = new QGridLayout;
//    QGridLayout* gridFilterButtons = new QGridLayout;
//    m_copy = new QListWidget();
//    m_quizList = new QListWidget(this);
//    m_reviewList = new QListWidget(this);

//    listPopulate();

//    addBtn = new QPushButton("Add question to review list", this);
//    startBtn = new QPushButton("Start Quiz", this);
//    deleteBtn = new QPushButton("Answer question from review list", this);
//    nextBtn = new QPushButton("Next question", this);
//    addBtn->setEnabled(false);
//    deleteBtn->setEnabled(false);
//    nextBtn->setEnabled(false);

//    QLabel* quizLabel = new QLabel("Quiz Window", this);
//    QLabel* filterLabel = new QLabel("Review List", this);

//    QFrame *line1 =  new QFrame(this);
//    line1->setFrameShape(QFrame::HLine);
//    line1->setFrameShadow(QFrame::Sunken);

//    QFrame *line2 =  new QFrame(this);
//    line2->setFrameShape(QFrame::HLine);
//    line2->setFrameShadow(QFrame::Sunken);

//    gridFilterButtons->addWidget(addBtn, 0, 0);
//    gridFilterButtons->addWidget(nextBtn, 0, 2);

//    gridQuizButtons->addWidget(startBtn, 0, 0);
//    gridQuizButtons->addWidget(deleteBtn, 0, 3);

//    vLayout->addWidget(quizLabel);
//    vLayout->addWidget(line1);
//    vLayout->addWidget(m_quizList);
//    //adding the add and the delete question buttons to a grid layout
//    topWidget->setLayout(gridFilterButtons);
//    //adding the grid layout to the main vertical layout
//    vLayout->addWidget(topWidget);
//    vLayout->addWidget(filterLabel);
//    vLayout->addWidget(line2);
//    vLayout->addWidget(m_reviewList);
//    //adding the start and filter buttons to a grid layout
//    bottomWidget->setLayout(gridQuizButtons);
//    //adding the grid layout to the main vertical layout
//    vLayout->addWidget(bottomWidget);

//    widget->setLayout(vLayout);

//    score = 0;

//    connect(startBtn, &QPushButton::pressed, this, &filterui::onClickStart);
//    connect(nextBtn, &QPushButton::clicked, this, &filterui::nextEvent);
//    connect(addBtn, &QPushButton::pressed, this, &filterui::onClickAdd);
//    connect(deleteBtn, &QPushButton::pressed, this, &filterui::onClickAnswer);

//    return widget;
}
