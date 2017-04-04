#include "checker.h"
#include <QDebug>

/*
 * Constructor parses for well-formed ness determines depths.
 * Params:
 *      s: a headerless (stripped) graph string
 */
Checker::Checker(QString in)
{
    original = in;

    // For well formed-ness
    int count = 1;

    // For depths
    int depth = -1;

    //qDebug() << "Entering constructor for " << in;

    for (int i = 0; i < in.length(); ++i)
    {
        QChar curr = in[i];

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

    wellFormed = (count == 0);
}

/*
 *
 */
void Checker::printDepths()
{
    qDebug() << "Printing depths for: ";
    qDebug().noquote() << original;

    for (int i = 0; i < depths.size(); ++i)
        qDebug() << original[i] << "=" << depths[i];
}
