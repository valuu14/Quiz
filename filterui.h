#ifndef FILTERUI_H
#define FILTERUI_H

#include <QMainWindow>
#include <QListWidget>
#include <QDebug>
#include <QPushButton>
#include "controller.h"
#include <vector>

class filterui :  public QMainWindow
{
public slots:
    void filter();

public:
    filterui(Controller* ctrl, QWidget* parent = nullptr);

    std::vector<Question*> getFiltered(){ return m_filtered; }

protected:
    std::vector<Question*> m_filtered;

private:
    QWidget* createCentralWidget();

    Controller* m_controller;

    QLineEdit* m_edit;
};

#endif // FILTERUI_H
