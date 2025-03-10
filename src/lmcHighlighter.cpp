#include "lmcHighlighter.h"

LmcHighlighter::LmcHighlighter(QTextDocument *parent) 
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    identifierFormat.setFontItalic(true);
    identifierFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z]+\\b"));
    rule.format = identifierFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bSUB\\b"),
        QStringLiteral("\\bADD\\b"),
        QStringLiteral("\\bSTA\\b"),
        QStringLiteral("\\bLDA\\b"),
        QStringLiteral("\\bBRA\\b"),
        QStringLiteral("\\bBRZ\\b"),
        QStringLiteral("\\bBRP\\b"),
        QStringLiteral("\\bINP\\b"),
        QStringLiteral("\\bOUT\\b"),
        QStringLiteral("\\bOTC\\b"),
        QStringLiteral("\\bHLT\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern, QRegularExpression::CaseInsensitiveOption);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    datFormat.setFontWeight(QFont::Bold);
    datFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\bDAT\\b"), QRegularExpression::CaseInsensitiveOption);
    rule.format = datFormat;
    highlightingRules.append(rule);

    intLiteralFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[0-9]+\\b"));
    rule.format = intLiteralFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

LmcHighlighter::~LmcHighlighter()
{
}

void LmcHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);
    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}