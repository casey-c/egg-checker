#ifndef CHECKER_H
#define CHECKER_H

#include <QString>
#include <QVector>

class Checker
{
public:
    Checker(QString line);

    bool isWellFormed() { return wellFormed; }
    void printDepths();

private:
    QString original;
    QVector<int> depths;
    bool wellFormed;

};

#endif // CHECKER_H
