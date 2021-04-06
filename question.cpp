#include "question.h"

Question::Question(std::string id, std::string txt, std::string sub, std::string type, std::string *p_a, std::string c_a){
    this->id = id;
    this->text = txt;
    this->subject = sub;
    this->type = type;
    this->possible_answers[0] = p_a[0];
    this->possible_answers[1] = p_a[1];
    this->possible_answers[2] = p_a[2];
    this->correct_answer = c_a;
}

void Question::toString(std::string& str) {
    str += "Question " + this->id;
    str += "\n";
    str += this->text;
    if (this->type == "MultipleChoice"){
        str += "\na) " + this->possible_answers[0];
        str += "\nb) " + this->possible_answers[1];
        str += "\nc) " + this->possible_answers[2];
        str += "\nd) " + this->correct_answer;
    } else if (this->type == "MatchingContent"){
        str += "\na) " + this->possible_answers[0];
        str += "\nb) " + this->possible_answers[1];
        str += "\nc) " + this->possible_answers[2];
        str += "\nd) " + this->correct_answer;
    } else {
        str += "\na) True";
        str += "\nb) False";
    }
    str += "\n";
}
