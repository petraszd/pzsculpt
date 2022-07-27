/***************************************************************************
 *   Copyright (C) 2008 by Petras Zdanavičius                              *
 *   petraszd@gmail.com                                                    *
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
#include "drawcommand.h"

namespace PZSculpt
{

DrawCommand::DrawCommand() : Command()
{
}


DrawCommand::~DrawCommand()
{
   for ( int i = 0; i < m_elems.size(); ++i )
      delete m_elems[i];

   m_elems.clear();
}


void DrawCommand::insert ( Position * position, const Vector3f & delta )
{
   m_elems << new DrawCommandElem ( position, delta );
}


void DrawCommand::undo()
{
   for ( int i = 0; i < m_elems.size(); ++i )
      m_elems[i]->undo();
}


void DrawCommand::redo()
{
   for ( int i = 0; i < m_elems.size(); ++i )
      m_elems[i]->redo();
}


}
