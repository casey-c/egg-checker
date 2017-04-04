#include "line.h"
#include <QDebug>

QString setBrackets(QString in, int &l, int &r)
{
    l = in.indexOf('[');
    r = in.indexOf(']');
    return in.mid(l + 1, r - l - 1);
}

/*
 * Constructor param assumes line is not-empty
 */
Line::Line(const QString &line)
    : originalLine(line), parentPos(-1), wellFormed(true)
{
    /// Deal with the header ///
    // First, determine the type of line
    QChar firstChar = line[0];
    if (firstChar == '0')
        type = premise;
    else if (firstChar == '1')
        type = insertion;
    else if (firstChar == '2')
        type = deletion;
    else if (firstChar == '3')
        type = iteration;
    else if (firstChar == '4')
        type = deiteration;
    else if (firstChar == '5')
        type = dcAdd;
    else if (firstChar == '6')
        type = dcRem;
    else if (firstChar == '7')
        type = dcSurr;
    else if (firstChar == '*')
        type = goal;

    // Set the proper information
    if (type == premise || type == goal)
        strippedLine = originalLine.right(originalLine.length() - 1);
    else // Non premise/goal lines need more stuff
    {
        int left, right;
        QString bracket = setBrackets(originalLine, left, right);
        qDebug() << "bracket is " << bracket;

        // Strip the header info out
        strippedLine = originalLine.right(originalLine.length() - right - 1);

        // Do the type specific work here
        if (   type == insertion // Insertion (only on odd)
            || type == deletion  // Deletion (only on even)
            || type == dcAdd )   // Double cut addition
        {
            bool ok;
            int potential = bracket.toInt(&ok);
            if (ok)
                parentPos = potential;
            else // SOMETHING WENT WRONG, not a valid int inside the bracket
                wellFormed = false;
        }
        else if (   type == iteration   // Iteration
                 || type == deiteration // Deiteration
                 || type == dcRem       // Double cut removal
                 || type == dcSurr )    // Double cut surround
        {
            QStringList list = bracket.split(":");
            parentPos = ((QString)list.first()).toInt();
            QStringList targets = ((QString) list.last()).split(",");
            for (QString s : targets)
                targetPos.append(s.toInt());
        }
        else
        {
            qDebug() << "Unknown type!";
        }
    }

    /// Parse the stripped, headerless string ///
    int count = 1;
    int depth = -1;

    for (int i = 0; i < strippedLine.length(); ++i)
    {
        QChar curr = strippedLine[i];

        if (curr.isDigit())
        {
            count += (curr.digitValue() - 1);
            depths.push_back(depth++);
        }
        else
        {
            --count;
            depths.push_back(depth--);
        }
    }

    wellFormed = wellFormed && (count == 0);
}

void Line::print()
{
    qDebug() << "Original line was " << originalLine;
    qDebug() << "Stripped line is " << strippedLine;
    qDebug() << "Type is " << typeToString();
    qDebug() << "Well-formed?: " << wellFormed << "\n";

    qDebug() << "Parent pos is " << parentPos;
    qDebug() << "# targets is " << targetPos.size();
    for (int x : targetPos)
        qDebug() << "\ta target is " << x;

    qDebug() << "\n---\n";
}

QString Line::typeToString()
{
    if (isPremise())
        return "Premise";
    else if (isInsertion())
        return "Insertion";
    else if (isDeletion())
        return "Deletion";
    else if (isIteration())
        return "Iteration";
    else if (isDeiteration())
        return "Deiteration";
    else if (isDCAdd())
        return "Double cut addition";
    else if (isDCRem())
        return "Double cut removal";
    else if (isDCSurr())
        return "Double cut surround";
    else if (isGoal())
        return "Goal";
    else
        return "Unknown type!";
}
