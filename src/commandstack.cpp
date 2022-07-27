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
#include "commandstack.h"

namespace PZSculpt
{

CommandStack::CommandStack ( int max )
{
   m_max = max;
   m_current = -1;
}


CommandStack::~CommandStack()
{
   clear();
}


void CommandStack::push ( Command * command )
{
   if ( m_current != m_commands.size() - 1 )
      clearTop();

   m_commands.append( command );

   if( m_commands.size() > m_max )
      m_commands.pop_front();

   m_current = m_commands.size() - 1;
}


void CommandStack::undo()
{
   if ( ! canUndo() )
      return;
   m_commands[m_current]->undo();
   m_current--;
}


void CommandStack::redo()
{
   if ( ! canRedo() )
      return;
   m_commands[m_current+1]->redo();
   m_current++;
}


bool CommandStack::canUndo()
{
   if ( m_commands.size() == 0 )
      return false;
   if ( m_current < 0 )
      return false;
   return true;
}


bool CommandStack::canRedo()
{
   if ( m_commands.size() == 0 )
      return false;
   if ( m_current >= m_commands.size() - 1 )
      return false;
   return true;
}


void CommandStack::clear()
{
   for ( int i = 0; i < m_commands.size(); ++i ) {
      delete m_commands[i];
   }
   m_commands.clear();
}


void CommandStack::clearTop()
{
   for ( int i = m_commands.size() - 1; i > m_current; --i ) {
      delete m_commands[i];
      m_commands.remove( i );
   }

   m_current = m_commands.size() - 1;
}


}
