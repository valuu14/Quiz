#include "studentui.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QListWidget>
#include <string>
#include "filterui.h"

studentui::studentui(QWidget *parent, Controller *ctrl) : QMainWindow(parent)
{
    m_controller = ctrl;
    this->setWindowTitle("Student Mode");
    this->setMinimumSize(800, 400);

    QWidget* centralW = createCentralWidget();
    this->setCentralWidget(centralW);
}

void studentui::prepQuestion()
{
    if (m_copy->count() == 0) return;
    int count = 0;
    char str2[256];
    QListWidgetItem* item = m_copy->takeItem(0);
    QString qstr = item->text();
    QString items[6];
    std::string str = qstr.toStdString();
    m_quizList->clear();
    while(true){
        int i = str.find('\n');
        if (str.find('\n') !=std::string::npos){
            str.copy(str2, i, 0); //copy the first i elements from str to str2
            str2[i] = NULL; //setting the last character null just in case ¯\_(ツ)_/¯
            str.erase(0, i+1); // delete the copied characters so we can start searching again
            items[count++] = QString::fromStdString(str2); //add to an array the copied strings
        }
        else break;
    }

    for(auto elem : items){
        m_quizList->addItem(elem);
    }
    m_quizList->item(0)->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    m_quizList->item(1)->setFlags(item->flags() & ~Qt::ItemIsSelectable);
}

void studentui::onClickStart()
{
    if (score == -1){
        m_copy->clear();
        m_filtered = m_filter->getFiltered();
       // qDebug() << "hello";
        listPopulate(m_filtered);
        score = 0;
    }
   prepQuestion();
   startBtn->setEnabled(false);
   filterBtn->setEnabled(false);
   addBtn->setEnabled(true);
   deleteBtn->setEnabled(true);
   nextBtn->setEnabled(true);
}

void studentui::nextEvent()
{

    int selected = m_quizList->currentRow();
    if ((selected == -1 or selected == 0) and m_quizList->count() > 6) {
        prepQuestion();
        addBtn->setEnabled(true);
        return;
    }
    else if (selected == -1 or selected == 0){
        qDebug() << "No answer selected";
        return;
    }
    QString qId = m_quizList->item(0)->text();
    if (qId.length() <= 10) qId.remove(0, qId.length() - 1);
    else qId.remove(0, qId.length() - 2);
    QString answer = m_quizList->item(selected)->text().remove(0, 3);
    int i = 0;
    while(true){
        if (correctAnswers.value(i) == qId and correctAnswers.value(i+1) == answer){
            increaseScore();
            //qDebug() << score;
            break;
        }
        i+=2;
        if (i > correctAnswers.length()) break;
    }
    if (m_copy->count() == 0 and m_reviewList->count() == 0){
        QString qstr = "Your score is ";
        qstr.append(QString::number(score));
        m_quizList->clear();
        m_quizList->addItem(qstr);
        return;
    }
    else if (m_copy->count() == 0 and m_reviewList->count() > 0){
        QString qstr = "Answer the question from review list.";
        m_quizList->clear();
        m_quizList->addItem(qstr);
        return;
    }
    prepQuestion();
    addBtn->setEnabled(true);
}

void studentui::onClickAdd()
{
    int n = m_reviewList->count();
    while (true){
        QString item = m_quizList->item(n % 6)->text();
        if (item == nullptr) qDebug() << "nullptr";
        m_reviewList->addItem(item);
        if (n % 6 == 0 or n % 6 == 1){
            m_reviewList->item(n)->setFlags(m_reviewList->item(n)->flags() & ~Qt::ItemIsSelectable);
        }
        n = m_reviewList->count();
        if (n % 6 == 0) break;
    }
    //qDebug() << m_reviewList->count();
    if (m_copy->count() == 0 and m_reviewList->count() > 0){
            QString qstr = "Answer the question from review list.";
            m_quizList->clear();
            m_quizList->addItem(qstr);
            addBtn->setEnabled(false);
            nextBtn->setEnabled(false);
            return;
    }
    else{
        QString qstr = "\nQuestion added to review list.";
        m_quizList->addItem(qstr);
    }
    addBtn->setEnabled(false);
    nextEvent();
}

void studentui::onClickAnswer()
{
    int selectedRow = m_reviewList->currentRow();
    if (m_reviewList->count() == 6) {
        QString qId = m_reviewList->item(0)->text();
        if (qId.length() <= 10) qId.remove(0, qId.length() - 1);
        else qId.remove(0, qId.length() - 2);
        QString answer = m_reviewList->item(selectedRow)->text().remove(0, 3);
        int i = 0;
        while(true){
            if (correctAnswers.value(i) == qId and correctAnswers.value(i+1) == answer){
                increaseScore();
                //qDebug() << score;
                break;
            }
            i+=2;
            if (i > correctAnswers.length()) break;
        }
        if (m_copy->count() == 0){
            QString qstr = "Your score is ";
            qstr.append(QString::number(score));
            m_reviewList->clear();
            m_reviewList->addItem(qstr);
            deleteBtn->setEnabled(false);
            return;
        }
        m_reviewList->clear();
    }
    else{
        int n = selectedRow / 6;
        QString qId = m_reviewList->item(n * 6)->text();

        if (qId.length() <= 10) qId.remove(0, qId.length() - 1);
        else qId.remove(0, qId.length() - 2);

        QString answer = m_reviewList->item(selectedRow)->text().remove(0, 3);
        int  i = 0;
        while(true){
            if (correctAnswers.value(i) == qId and correctAnswers.value(i+1) == answer){
                increaseScore();
                //qDebug() << score;
                break;
            }
            i+=2;
            if (i > correctAnswers.length()) break;
        }
        if (m_reviewList->count() == 0){
            QString qstr = "Your score is ";
            qstr.append(QString::number(score));
            m_quizList->clear();
            m_quizList->addItem(qstr);
            return;
        }
        n = selectedRow / 6;
        i = 0;
        while(i < 6){
            m_reviewList->takeItem(n * 6);
            i++;
        }
        for (int i = 0; i < m_reviewList->count(); i++){
            if (i % 6 == 0 or i % 6 == 1)  m_reviewList->item(i)->setFlags(m_reviewList->item(i)->flags() & ~Qt::ItemIsSelectable);
        }

    }
}

void studentui::onClickFilter(){
    m_filter = new filterui(m_controller, this);
    m_filter->show();
    score = -1;
}

QWidget *studentui::createCentralWidget()
{
    QWidget* widget = new QWidget(this);
    QWidget* topWidget = new QWidget(this);
    QWidget* bottomWidget = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout;
    QGridLayout* gridQuizButtons = new QGridLayout;
    QGridLayout* gridFilterButtons = new QGridLayout;
    m_copy = new QListWidget();
    m_quizList = new QListWidget(this);
    m_reviewList = new QListWidget(this);

    std::vector<Question*> v = m_controller->getQuestions();
    listPopulate(v);

    addBtn = new QPushButton("Add question to review list", this);
    startBtn = new QPushButton("Start Quiz", this);
    filterBtn = new QPushButton("Filter questions", this);
    deleteBtn = new QPushButton("Answer question from review list", this);
    nextBtn = new QPushButton("Next question", this);
    addBtn->setEnabled(false);
    deleteBtn->setEnabled(false);
    nextBtn->setEnabled(false);

    QLabel* quizLabel = new QLabel("Quiz Window", this);
    QLabel* filterLabel = new QLabel("Review List", this);

    QFrame *line1 =  new QFrame(this);
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    QFrame *line2 =  new QFrame(this);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    gridFilterButtons->addWidget(addBtn, 0, 0);
    gridFilterButtons->addWidget(filterBtn, 0, 1);
    gridFilterButtons->addWidget(nextBtn, 0, 2);

    gridQuizButtons->addWidget(startBtn, 0, 0);
    gridQuizButtons->addWidget(deleteBtn, 0, 3);

    vLayout->addWidget(quizLabel);
    vLayout->addWidget(line1);
    vLayout->addWidget(m_quizList);
    //adding the add and the delete question buttons to a grid layout
    topWidget->setLayout(gridFilterButtons);
    //adding the grid layout to the main vertical layout
    vLayout->addWidget(topWidget);
    vLayout->addWidget(filterLabel);
    vLayout->addWidget(line2);
    vLayout->addWidget(m_reviewList);
    //adding the start and filter buttons to a grid layout
    bottomWidget->setLayout(gridQuizButtons);
    //adding the grid layout to the main vertical layout
    vLayout->addWidget(bottomWidget);

    widget->setLayout(vLayout);

    score = 0;

    connect(startBtn, &QPushButton::pressed, this, &studentui::onClickStart);
    connect(nextBtn, &QPushButton::clicked, this, &studentui::nextEvent);
    connect(addBtn, &QPushButton::pressed, this, &studentui::onClickAdd);
    connect(deleteBtn, &QPushButton::pressed, this, &studentui::onClickAnswer);
    connect(filterBtn, &QPushButton::clicked, this, &studentui::onClickFilter);

    return widget;
}
