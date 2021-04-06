#ifndef PERSISTENCEENGINE_H
#define PERSISTENCEENGINE_H

#include <iostream>
#include "question.h"
#include "controller.h"
#include <vector>
#include <string>
#include <QString>
#include <QFile>
#include <customexception.h>
#include<QTextStream>
#include <fstream>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class PersistenceEngine
{
public:
    PersistenceEngine();
    virtual bool save(std::vector<Question*> v, QString filePath) = 0;
    virtual bool load(QString filePath, Controller* c) = 0;
//protected:
//    std::vector<Question*> m_array;
};

class PersistenceEngineJSON : public PersistenceEngine{
public:
    bool save(std::vector<Question *> v, QString filePath) override{
        QJsonObject obj;
        QJsonArray elemsJson;
        for(auto elem: v){
            elemsJson.append(elem->toJsonObject());
        }
        obj["elements"] = elemsJson;

        QFile file{filePath};

        QJsonDocument jsonDoc{obj};
        bool opened = file.open(QFile::WriteOnly | QFile::Text);
        if(!opened)
            return false;
        file.write(jsonDoc.toJson());
        file.close();

        return true;
    }

    bool load(QString filePath, Controller *c) override{
        QFile inFile(filePath);
        inFile.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray data = inFile.readAll();
        inFile.close();

        QJsonParseError errorPtr;
        QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
        if (doc.isNull()) {
            IOException e;
            throw e;
            qDebug() << "Parse failed";
            return false;
        }
        QJsonObject rootObj = doc.object();
        QJsonArray array = rootObj.value("elements").toArray();
        qDebug() << "There are " << array.size() << "questions in the json file";
        foreach(const QJsonValue & val, array){
            std::string id = val.toObject().value("id").toString().toStdString();
            std::string text = val.toObject().value("text").toString().toStdString();
            std::string subject = val.toObject().value("subject").toString().toStdString();
            std::string type = val.toObject().value("type").toString().toStdString();
            std::string p_a[3];
            p_a[0] = val.toObject().value("p_a")[0].toString().toStdString();
            p_a[1] = val.toObject().value("p_a")[1].toString().toStdString();
            p_a[2] = val.toObject().value("p_a")[2].toString().toStdString();
            std::string c_a = val.toObject().value("c_a").toString().toStdString();
            Question* q = new Question;
            q->setId(id);
            q->setText(text);
            q->setSubject(subject);
            q->setType(type);
            q->setPossibleAnswers(p_a);
            q->setCorrectAnswer(c_a);
            c->addQuestion(q,1);
        }

        qDebug() << "Finished parsing...";
        return true;
    }
};

#endif // PERSISTENCEENGINE_H
