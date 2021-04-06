#include "ui.h"

TeacherUI::TeacherUI(Controller *c) {
    this->c = c;
}

void TeacherUI::printMenu() {
    std::cout << "You entered the 'Teacher mode'.\n";
    std::cout << "Press a to add a new question to the quiz.\n";
    std::cout << "Press d to delete a question from the quiz.\n";
    std::cout << "Press s to show all the question from the quiz.\n";
    std::cout << "Press u to update a question from the quiz.\n";
    std::cout << "Press e to exit the console.\n";
}

void TeacherUI::menu() {
    char op;
    while (true){
        printMenu();
        std::cin >> op; cin.get();
        switch (op) {
            case 'a':
                addQuestion();
                break;
            case 'd':
                deleteQuestion();
                break;
            case 's':
                showAll();
                break;
            case 'u':
                updateQuestion();
                break;
            case 'e':
                std::cout << "Exiting 'Teacher mode'...";
                this->c->saveData();
                exit(0);
            default:
                std::cout << "Unknown command.";
                break;
        }
    }
}

void TeacherUI::addQuestion() {
    std::string id, txt, sub, type, p_a[3], c_a;
    while (true){
        std::cout << "Give the id of the question: ";
        getline(cin, id);
        std::cout << "Enter the question: ";
        getline(cin, txt);
        std::cout << "Give the subject of the question: ";
        getline(cin, sub);
        std::cout << "Give the type of the question(MultipleChoice, MatchingContent, T/F): ";
        getline(cin, type);
        if (type == "MultipleChoice" or type == "MatchingContent"){
            std::cout << "Give the 3 possible answers for the question: ";
            getline(cin, p_a[0]);
            getline(cin, p_a[1]);
            getline(cin, p_a[2]);
            std::cout << "Give the correct answer: ";
            getline(cin, c_a);
            break;
        } else if (type == "T/F"){
            p_a[0] = "True";
            p_a[1] = "False";
            std::cout << "Give the correct answer: ";
            getline(cin, c_a);
            break;
        } else {
            std::cout << "Invalid question type, try again...";
        }
    }
    auto *q = new Question{id, txt, sub, type, p_a, c_a};
    if (this->c->addQuestion(q, 1)) std::cout << "Question has been added successfully.\n";
    else cout << "The question has not been added.\n";
}

void TeacherUI::deleteQuestion() {
    std::string id;
    std::cout << "Give the id of the question you want to delete: ";
    getline(cin, id);
    if (this->c->removeQuestion(id, 1)) std::cout << "Question " << id << " has been removed successfully.\n";
    else std::cout << "The question has not been removed.\n";
}

void TeacherUI::showAll() {
    std::string str;
    this->c->printAll(str);
    std::cout << str;
}

void TeacherUI::updateQuestion() {
    std::string id, sub, type, p_a[3], c_a;
    std::cout << "Here you can change the subject, type, possible answers or correct answer of a question.\n";
    std::cout << "If you do not want to change a field, just leave it blank and press ENTER.\n";
    std::cout << "Note that if you change the type of a question, be sure that the answers match the type.\n";
    std::cout << "Give the id of the question you want to update: ";
    getline(cin, id);
    std::cout << "Give the new subject: ";
    getline(cin, sub);
    std::cout << "Give the new type: ";
    getline(cin, type);
    if (type == "MultipleChoice" or type == "MatchingContent"){
        std::cout << "Give the 3 possible answers for the question: ";
        getline(cin, p_a[0]);
        getline(cin, p_a[1]);
        getline(cin, p_a[2]);
        std::cout << "Give the correct answer: ";
        getline(cin, c_a);
    }else if (type == "T/F"){
        p_a[0] = "True";
        p_a[1] = "False";
        std::cout << "Give the correct answer: ";
        getline(cin, c_a);
    }else if (type.empty()){
        std::cout << "Give the 3 possible answers for the question: ";
        getline(cin, p_a[0]);
        getline(cin, p_a[1]);
        getline(cin, p_a[2]);
        std::cout << "Give the correct answer: ";
        getline(cin, c_a);
    }
    if (this->c->updateQuestion(id, sub, type, p_a, c_a)) std::cout << "The question has been updated successfully.\n";
    else std::cout << "The question has not been updated.\n";
}

StudentUI::StudentUI(Controller *c) {
    this->c = c;
}

void StudentUI::addQuestion(Question* q) {
    if (this->c->addQuestion(q, 2)) std::cout << "Question added to the 'review' list.\n";
    else std::cout << "Question has not been added to the 'review' list.\n";
}

void StudentUI::deleteQuestion() {
    std::string id;
    std::cout << "Give the id of the question you want to delete:";
    std::cin >> id; cin.get();
    if (this->c->removeQuestion(id, 2)) std::cout << "Question deleted successfully.\n";
    else std::cout << "Question has not been deleted.\n";
}

bool StudentUI::uiFilterQuestions() {
    std::string sub, str;
    std::vector<Question*> filtered, reviewList;
    char choice;
    int grade;
    std::cout << "Give the subject: ";
    getline(cin, sub);
    if (sub.empty()) return false;
    this->c->filterQuestions(sub, filtered);
    if (filtered.empty()){
        std::cout << "There are no question having '" << sub << "' as subject. The quiz will show all the questions now.\n";
        return false;
    }
    std::cout << "The quiz started.\n";
    std::cout << "Press a, b, c or d when choosing the answer.\n";
    while (true){
        grade = 0;
        for (auto &q : filtered){
            str = "";
            (*q).toString(str);
            std::cout << str;
            secondMenu(q, grade);
        }
        std::cout << "Do you want to see the questions again?(y/n) Careful!!! If you press y, you must answer again the questions";
        std::cin >> choice; cin.get();
        if (choice == 'n') break;
    }
    this->c->getAllShuffled(reviewList, 2);
    if (reviewList.empty()) std::cout << "Your score is: " << grade << ".\n";
    else {
        for (auto &q : reviewList){
            str = "";
            (*q).toString(str);
            std::cout << str;
            chooseAnswer(q, grade);
        }
        std::cout << "Your score is: " << grade << ".\n";
    }
    return true;
}

void StudentUI::printMenu() {
    std::cout << "Press a to add a question to the 'review' list.\n";
    std::cout << "Press d to delete a question from the 'review' list.\n";
    std::cout << "Press x to answer to the question.\n";
}

void StudentUI::printSecondMenu() {
    std::cout << "Press s to start the quiz.\n";
    std::cout << "Press f to search for question having a specific subject.\n";
    std::cout << "Press e to exit.\n";
}

void StudentUI::menu() {
    char op;
    std::cout << "You entered the 'Student mode'.\n";
    while(true){
        printSecondMenu();
        std::cin >> op; cin.get();
        switch (op) {
            case 'f':
                if (!uiFilterQuestions()) app();
                exit(0);
            case 's':
                app();
                exit(0);
            case 'e':
                std::cout << "Exiting...\n";
                exit(0);
            default:
                std::cout << "Unknown command.\n";
                break;
        }
    }
}

void StudentUI::secondMenu(Question* q, int &grade) {
    char op;
    while (true){
        printMenu();
        std::cin >> op; cin.get();
        switch (op) {
            case 'a':
                addQuestion(q);
                break;
            case 'd':
                deleteQuestion();
                break;
            case 'x':
                chooseAnswer(q, grade);
                break;
            default:
                std::cout << "Unknown command.\n";
                break;
        }
        break;
    }
}

void StudentUI::chooseAnswer(Question* q, int &grade) {
    char choice;
    if (q->getType() == "MultipleChoice" or q->getType() == "MatchingContent"){
        while (true){
            std::cout << "Choose the answer: ";
            std::cin >> choice; cin.get();
            if (choice > 'd' or choice < 'a') std::cout << "Unknown command.\n";
            else if (choice == 'd') {
                grade++;
                break;
            } else break;
        }
    }
    else {
        while (true){
            std::cout << "Choose the answer: ";
            std::cin >> choice; cin.get();
            if (choice > 'b' or choice < 'a') std::cout << "Unknown command.\n";
            else if (choice == 'a' and q->getCorrectAnswer() == "True"){
                grade++;
                break;
            }
            else if (choice == 'b' and q->getCorrectAnswer() == "False"){
                grade++;
                break;
            } else break;
        }
    }
}

void StudentUI::app() {
    std::vector<Question*> v, reviewList;
    std::string str;
    char choice;
    int grade;
    std::cout << "The quiz started.\n";
    std::cout << "Press a, b, c or d when choosing the answer.\n";
    this->c->getAllShuffled(v, 1);
    while (true){
        grade = 0;
        for (auto &q : v){
            str = "";
            (*q).toString(str);
            std::cout << str;
            secondMenu(q, grade);
        }
        std::cout << "Do you want to see the questions again?(y/n) Careful!!! If you press y, you must answer again the questions";
        std::cin >> choice; cin.get();
        if (choice == 'n') break;
    }
    this->c->getAllShuffled(reviewList, 2);
    if (reviewList.empty()) std::cout << "Your score is: " << grade << ".\n";
    else {
        for (auto &q : reviewList){
            str = "";
            (*q).toString(str);
            std::cout << str;
            chooseAnswer(q, grade);
        }
        std::cout << "Your score is: " << grade << ".\n";
    }
}
