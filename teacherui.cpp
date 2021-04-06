#include "teacherui.h"
#include "addquestionteacher.h"
#include <QLayout>
#include <QPushButton>
#include <vector>
#include <string>
#include <QDebug>
#include <QStringList>

void teacherUI::onPushButtonAdd()
{
    addWindow = new addQuestionTeacher(m_controller, this);
    addWindow->show();
}

void teacherUI::onPushButtonDelete()
{
    int selectedRow = m_list->currentRow();
    std::vector<Question*> v = m_controller->getQuestions();
    std::string id = v[selectedRow]->getId();
    if(m_controller->removeQuestion(id, 1)){
        m_list->takeItem(selectedRow);
        //m_list->clear();
        //listPopulate();
        qDebug() << "Question deleted";
    }
    else qDebug() << "Question not deleted";
}

teacherUI::teacherUI(QWidget *parent, Controller *ctrl) : QMainWindow(parent)
{
    m_controller = ctrl;
    this->setWindowTitle("Teacher Mode");
    this->setMinimumSize(1080, 720);

    QWidget* centralW = createCentralWidget();
    this->setCentralWidget(centralW);
}

void teacherUI::listPopulate()
{
    std::vector<Question*> v;
    v = m_controller->getQuestions();
    for (auto q : v){
        std::string str;
        (*q).toString(str);
        m_list->addItem(QString::fromStdString(str));
    }
}

void teacherUI::keyPressEvent(QKeyEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        if(event->matches(QKeySequence::Undo)){
            qDebug()<<"pressed ctrl+z";
            int res = m_controller->undoOp();
            if (res == 1) m_list->takeItem(m_list->count());
            else{
                m_list->clear();
                listPopulate();
            }
        }
        if (event->matches(QKeySequence::Redo)){
            qDebug()<<"pressed ctrl+y";
            int res = m_controller->redoOp();
            if (res == 1){
                m_list->clear();
                listPopulate();
            }
            else
                m_list->takeItem(m_list->count());
        }
    }
}

QWidget *teacherUI::createCentralWidget()
{
    QWidget* widget = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout;
    m_list = new QListWidget(this);

    listPopulate();

    vLayout->addWidget(m_list);
    QWidget* bottomWidget = new QWidget(this);
    QHBoxLayout* hLayout = new QHBoxLayout;
    QPushButton* addButton = new QPushButton("Add Question", this);
    QPushButton* updateButton = new QPushButton("Update Question", this);
    QPushButton* deleteButton = new QPushButton("Delete Question", this);
    hLayout->addWidget(addButton);
    hLayout->addWidget(updateButton);
    hLayout->addWidget(deleteButton);
    bottomWidget->setLayout(hLayout);

    vLayout->addWidget(bottomWidget);
    widget->setLayout(vLayout);

    connect(addButton, &QPushButton::clicked, this, &teacherUI::onPushButtonAdd);
    connect(deleteButton, &QPushButton::clicked, this, &teacherUI::onPushButtonDelete);
    m_controller->saveData();

    return widget;
}
