#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QVector>
#include <QList>

enum LineType
{
    premise,
    insertion,
    deletion,
    iteration,
    deiteration,
    dcAdd,
    dcRem,
    dcSurr,
    goal
};

/*
 * A Line is the data structure that stores a specific line in the proof. Lines
 * are created by passing a QString of the line itself. This object will then
 * parse for well-formedness and construct an array of all the depths of the
 * nodes in the line.
 */
class Line
{
public:
    Line(const QString &line);

    void print();

    /* Identifiers */
    bool isWellFormed() { return wellFormed; }

    bool isPremise() { return type == premise; }
    bool isInsertion() { return type == insertion; }
    bool isDeletion() { return type == deletion; }
    bool isIteration() { return type == iteration; }
    bool isDeiteration() { return type == deiteration; }
    bool isDCAdd() { return type == dcAdd; }
    bool isDCRem() { return type == dcRem; }
    bool isDCSurr() { return type == dcSurr; }
    bool isGoal() { return type == goal; }

    QString typeToString();

private:
    QString originalLine;
    QString strippedLine;

    QVector<int> depths;

    // Transitions
    int parentPos;
    QList<int> targetPos;
    bool wellFormed;

    LineType type;
};

#endif // LINE_H
