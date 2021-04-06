#ifndef LAB7_QUESTION_H
#define LAB7_QUESTION_H

#include <string>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>

class Question {
public:
    Question(std::string id, std::string txt, std::string sub, std::string type, std::string p_a[], std::string c_a);
    Question() = default;

    ~Question() = default;

    std::string getId() { return this->id; }
    std::string getText() {return this->text; }
    std::string getType() { return this->type; }
    std::string getSubject() { return this->subject; }
    std::string* getPossibleAnswers() {return this->possible_answers; }
    std::string getCorrectAnswer() { return this->correct_answer; }
    void setId(std::string new_id) { this->id = new_id; }
    void setText(std::string new_txt) { this->text = new_txt; }
    void setSubject(std::string new_s) { this->subject = new_s; }
    void setType(std::string new_t) { this->type = new_t; }
    void setCorrectAnswer(std::string new_c_a) { this->correct_answer = new_c_a; }
    void setPossibleAnswers(std::string new_p_a[3]) {
        this->possible_answers[0] = new_p_a[0];
        this->possible_answers[1] = new_p_a[1];
        this->possible_answers[2] = new_p_a[2];
    }

    /**
     * @brief creates the string representation of an object of type question
     * @param str
     */
    void toString(std::string& str);

    QJsonObject toJsonObject(){
        QJsonObject obj;
        QString p_a[3];
        QJsonArray array;
        p_a[0] = QString::fromStdString(possible_answers[0]);
        p_a[1] = QString::fromStdString(possible_answers[1]);
        p_a[2] = QString::fromStdString(possible_answers[2]);
        obj["id"] = QString::fromStdString(id);
        obj["text"] = QString::fromStdString(text);
        obj["subject"] = QString::fromStdString(subject);
        obj["type"] = QString::fromStdString(type);
        for (int i =0; i < 3; i++)
            array.append(p_a[i]);
        obj["p_a"] = array;
        obj["c_a"] = QString::fromStdString(correct_answer);
        return obj;
    }

private:
    std::string id, text, subject, type, possible_answers[3], correct_answer;
};


#endif //LAB7_QUESTION_H

