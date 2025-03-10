#pragma once
#ifndef LMC_HIGHLIGHTER_H
#define LMC_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QList>

class LmcHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LmcHighlighter(QTextDocument *parent=nullptr);
    ~LmcHighlighter();

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QList<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat datFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat identifierFormat;
    QTextCharFormat intLiteralFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
};

#endif // LMC_HIGHLIGHTER_H