#include "mylineedit.h"
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    this->setStyleSheet("background-color:rgb(255, 255, 255);");

    connect(this, SIGNAL(showSuggestion()), this->parent(), SLOT(showSuggestion()));
    connect(this, SIGNAL(hideSuggestion()), this->parent(), SLOT(hideSuggestion()));
    connect(this, SIGNAL(changePrevious()), this->parent(), SLOT(changePrevious()));
    connect(this, SIGNAL(changeNext()), this->parent(), SLOT(changeNext()));
    connect(this, SIGNAL(back()), this->parent(), SLOT(back()));
    connect(this, SIGNAL(changeContent(QKeyEvent *)), this->parent(), SLOT(changeContent(QKeyEvent *)));
};

MyLineEdit::~MyLineEdit() {

}

void MyLineEdit::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Up:
        emit changePrevious();
        return;
    case Qt::Key_Down:
        emit changeNext();
        return;
    case Qt::Key_Return:
        emit back();
        return;
    }
    emit changeContent(event);

}

void MyLineEdit::setPreNext(QList<MyLineEdit *> pre_next) {
    this->pre_next = pre_next;
}

void MyLineEdit::focusInEvent(QFocusEvent *e) {
    this->isClear = true;
    emit showSuggestion();
}

void MyLineEdit::focusOutEvent(QFocusEvent *e) {
    emit hideSuggestion();
}

QString MyLineEdit::getSuggestions() const
{
    return suggestions;
}

void MyLineEdit::setSuggestions(const QString &value)
{
    suggestions = value;
}

QString MyLineEdit::getSuggestion() {
    return this->suggestions;
}

QList<MyLineEdit*> MyLineEdit::getPreNext() {
    return this->pre_next;
}
