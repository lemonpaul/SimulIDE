/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#include "outpaneltext.h"
#include "mainwindow.h"
#include "simulator.h"

OutPanelText::OutPanelText( QWidget* parent )
            : QPlainTextEdit( parent )
            , eElement( "outPanel" )
{
    m_textBuffer = "";
    this->setObjectName( "outPanel" );

    m_highlighter = new OutHighlighter( document() );

    QPalette p;// = palette();
    p.setColor( QPalette::Base, QColor( 35, 30, 60 ) );
    p.setColor( QPalette::Text, QColor( 190, 190, 150) );
    setPalette(p);
    
    QFont font;
    font.setFamily("Monospace");
    font.setFixedPitch(true);
    font.setPixelSize( 12*MainWindow::self()->fontScale() );
    setFont(font);

    setMaximumBlockCount( 1000 );

    setReadOnly(true);
}
OutPanelText::~OutPanelText(){}

void OutPanelText::appendText( const QString text )
{
    m_textBuffer.append( text );
}

void OutPanelText::writeText( const QString text )
{
    m_textBuffer.append( text+"\n" );
    if( !Simulator::self()->isRunning() ) updateStep();
}

void OutPanelText::updateStep()
{
    if( m_textBuffer.isEmpty() ) return;

    if( this->document()->characterCount() > 50000 )
        setPlainText( this->toPlainText().right( 25000 ) );

    moveCursor( QTextCursor::End );
    insertPlainText( m_textBuffer );
    moveCursor( QTextCursor::End );
    m_textBuffer.clear();
}

// CLASS OutHighlighter ***********************************************

OutHighlighter::OutHighlighter( QTextDocument* parent )
              : QSyntaxHighlighter( parent )
{
    HighlightingRule rule;

    fileFormat.setForeground( QColor(110, 180, 100) );
    rule.pattern = QRegExp( "/[^\n]*" );
    rule.format = fileFormat;
    highlightingRules.append( rule );

    numberFormat.setForeground( QColor(120, 120, 250) );
    rule.pattern = QRegExp("[0-9]+");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground( QColor(50, 200, 100) );
    rule.pattern = QRegExp( "\".*\"" );
    rule.format = quotationFormat;
    highlightingRules.append( rule );

    successFormat.setForeground( QColor(255, 255, 200) );
    successFormat.setFontWeight( QFont::Bold );
    rule.pattern = QRegExp("SUCCESS");
    rule.format = successFormat;
    highlightingRules.append(rule);
    
    sentFormat.setForeground( QColor(255, 255, 200) );
    sentFormat.setFontWeight( QFont::Bold );
    rule.pattern = QRegExp("SENT:");
    rule.format = sentFormat;
    highlightingRules.append(rule);

    warningFormat.setForeground( QColor(255, 200, 100) );
    warningFormat.setFontWeight( QFont::Bold );
    rule.pattern = QRegExp("WARNING");
    rule.format = warningFormat;
    highlightingRules.append(rule);

    errorFormat.setForeground( QColor(100, 50, 0) );
    errorFormat.setBackground( QColor(255, 255, 100) );
    errorFormat.setFontWeight( QFont::Bold );
    rule.pattern = QRegExp(" ERROR");
    rule.format = errorFormat;
    highlightingRules.append(rule);
}
OutHighlighter::~OutHighlighter(){}

void OutHighlighter::highlightBlock( const QString &text )
{
    QString upText = text;
    upText = upText.toUpper(); // Do case insensitive

    for( const HighlightingRule &rule : highlightingRules )
    {
        QRegExp expression( rule.pattern );
        int index = expression.indexIn( upText );
        while( index >= 0 )
        {
            int length = expression.matchedLength();
            setFormat( index, length, rule.format );
            index = expression.indexIn( upText, index + length );
        }
    }
}
#include "moc_outpaneltext.cpp"
