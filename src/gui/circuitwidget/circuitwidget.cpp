/***************************************************************************
 *   Copyright (C) 2010 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "circuitwidget.h"

CircuitWidget::CircuitWidget( QWidget *parent, QToolBar* toolbar  )
    : QWidget( parent )
    ,m_verticalLayout(this)
    ,m_horizontLayout()
    ,m_circView(this)
    ,m_outPanel(this)
    ,m_oscope(this)
    ,m_plotter(this)
{
    m_verticalLayout.setObjectName(tr("verticalLayout"));
    m_verticalLayout.setContentsMargins(0, 0, 0, 0);
    m_verticalLayout.setSpacing(0);

    m_verticalLayout.addWidget( toolbar );
    m_verticalLayout.addWidget( &m_circView );
    
    m_verticalLayout.addLayout( &m_horizontLayout );
    m_horizontLayout.addWidget( &m_oscope );
    m_horizontLayout.addWidget( &m_plotter );
    m_horizontLayout.addWidget( &m_outPanel );

    //QGridLayout lo(this);
    //lo.addLayout( &m_verticalLayout, 0, 0 );
}
CircuitWidget::~CircuitWidget() { }

void CircuitWidget::clear()
{
    m_circView.clear();
}

#include "moc_circuitwidget.cpp"
