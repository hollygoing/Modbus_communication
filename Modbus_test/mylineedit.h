#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include <QKeyEvent>
#include <QList>
#include <QLabel>
class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget *parent = nullptr);
    ~MyLineEdit();
    void setPreNext(QList<MyLineEdit*> pre_next);
    QString getSuggestion();
    QList<MyLineEdit*> getPreNext();
    int no;
    bool isClear;
    bool isEnable = true;

    QString getSuggestions() const;
    void setSuggestions(const QString &value);

protected:
    void keyPressEvent(QKeyEvent *event);
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

private:
    QString suggestions;
    QList<MyLineEdit*> pre_next = {nullptr, nullptr};


signals:
    void showSuggestion();
    void hideSuggestion();
    void changePrevious();
    void changeNext();
    void back();
    void changeContent(QKeyEvent* event);
};
#endif // MYLINEEDIT_H
