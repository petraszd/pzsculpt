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
#include "multimesh.h"

namespace PZSculpt
{

MultiMesh::MultiMesh ( Subdivider * subdivider ) :
      Drawable(),
      m_subdivider ( subdivider )
{
   m_current = 0;
   m_isMesh = false;
}


MultiMesh::~MultiMesh()
{
   if ( m_subdivider != 0 )
      delete m_subdivider;

   deleteAllMeshes();
}


void MultiMesh::putMesh ( Mesh * mesh )
{
   deleteAllMeshes();
   m_meshes << mesh;
   m_current = 0;
   m_isMesh = true;
}


void MultiMesh::stepUp()
{
   if ( ! m_isMesh )
      return;

   if ( m_current >= m_meshes.size() - 1 )
      return;

   Mesh * currentMesh = m_meshes[m_current];
   Mesh * fowardMesh = m_meshes[m_current+1];
   QList<Vector3f> deltas;

   stepUpPassInitDeltas ( currentMesh, fowardMesh, deltas );
   stepUpPassFacePoints ( fowardMesh, deltas );
   stepUpPassEdgePoints ( fowardMesh, deltas );
   stepUpPassOldPoints ( fowardMesh, deltas );
   stepUpPassDeform ( fowardMesh, deltas );

   m_current++;
   m_meshes[m_current]->recalculateNormalAll();
}


void MultiMesh::stepUpPassInitDeltas ( Mesh *currentMesh, Mesh *fowardMesh,
                                       QList<Vector3f> & deltas )
{
   for ( int i = 0; i < fowardMesh->getPosCount(); ++i ) {
      if ( fowardMesh->posPtr ( i )->getLevel() <= m_current )
         deltas.append ( currentMesh->pos ( i ) - fowardMesh->pos ( i ) );
      else
         deltas.append ( Vector3f ( 0.0f, 0.0f, 0.0f ) );
   }
}


void MultiMesh::stepUpPassFacePoints ( Mesh *fowardMesh, QList<Vector3f> & deltas )
{
   Position *pos;
   QList<Position*> list;
   for ( int i = 0; i < fowardMesh->getPosCount(); ++i ) {
      pos = fowardMesh->posPtr ( i );


      //Working just with thoses who where constructed as face points
      if ( pos->getLevel() <= m_current || ! pos->isNeighborsSameLevel() )
         continue;

      list = getDiagonals ( pos );
      if ( list.size() == 0 )
         continue;

      for ( int j = 0; j < list.size(); ++j )
         deltas[i] += deltas[ list[j]->getNumber() ];
      deltas[i] /= list.size();
   }
}


void MultiMesh::stepUpPassEdgePoints ( Mesh *fowardMesh,
                                       QList<Vector3f> & deltas )
{
   Position *pos;
   for ( int i = 0; i < fowardMesh->getPosCount(); ++i ) {
      pos = fowardMesh->posPtr ( i );
      //Working just with thoses who where constructed as edge points
      if ( pos->getLevel() <= m_current || pos->isNeighborsSameLevel() )
         continue;

      for ( int j = 0; j < pos->getNeighborsSize(); ++j )
         deltas[i] += deltas[ pos->getNeighbor ( j )->getNumber() ];

      deltas[i] /= pos->getNeighborsSize();
   }
}


void MultiMesh::stepUpPassOldPoints ( Mesh *fowardMesh,
                                      QList<Vector3f> & deltas )
{
   Position *pos;
   Vector3f newValue;
   for ( int i = 0; i < fowardMesh->getPosCount(); ++i ) {
      pos = fowardMesh->posPtr ( i );
      //Working just with thoses with lower levels
      if ( pos->getLevel() > m_current )
         continue;

      newValue.setPlace ( 0.0f, 0.0f, 0.0f );
      for ( int j = 0; j < pos->getNeighborsSize(); ++j )
         newValue += deltas[ pos->getNeighbor ( j )->getNumber() ];

      newValue /= pos->getNeighborsSize();

      deltas[i] = newValue * ( 2.0f / 3.0f ) + deltas[i] * ( 1.0f / 3.0f );
   }
}


void MultiMesh::stepUpPassDeform ( Mesh *fowardMesh, QList<Vector3f> & deltas )
{
   for ( int i = 0; i < fowardMesh->getPosCount(); ++i )
      fowardMesh->posPtr ( i )->setPlace ( fowardMesh->pos ( i ) + deltas[i] );
}


QList<Position*> MultiMesh::getDiagonals ( Position *pos )
{
   QSet<Position*> set;
   Position *ptr;
   for ( int i = 0; i < pos->getNeighborsSize(); ++i ) {
      for ( int j = 0; j < pos->getNeighbor ( i )->getNeighborsSize(); ++j ) {
         ptr = pos->getNeighbor ( i )->getNeighbor ( j );
         if ( pos == ptr )
            continue;

         if ( ptr->getLevel() < pos->getLevel() )
            set.insert ( ptr );
      }
   }
   return set.toList();
}


void MultiMesh::stepDown()
{
   if ( ! m_isMesh )
      return;

   if ( m_current > 0 )
      m_current--;
   else
      return;

   Mesh *newMesh = new Mesh();
   Mesh *oldMesh = m_meshes[m_current+1];

   for ( int i = 0; i < oldMesh->getPosCount(); ++i ) {
      if ( oldMesh->posPtr ( i )->getLevel() <= m_current ) {
         newMesh->addPos ( oldMesh->pos ( i ) );
      }
   }

   for ( int i = 0; i < oldMesh->getTexCount(); ++i ) {
      if ( oldMesh->texPtr ( i )->getLevel() <= m_current ) {
         newMesh->addTex ( oldMesh->tex ( i ) );
      }
   }

   oldMesh = m_meshes[m_current];
   for ( int i = 0; i < oldMesh->getFacesCount(); ++i ) {
      newMesh->addFace ( oldMesh->face ( i ) );
   }

   newMesh->finishConstrucion();

   delete m_meshes[m_current];
   m_meshes[m_current] = newMesh;
}


void MultiMesh::addLevel()
{
   if ( ! m_isMesh )
      return;

   for ( int i = m_current; i < m_meshes.size() - 1; ++i )
      stepUp();

   Mesh *mesh = m_subdivider->subdivide ( * ( m_meshes[m_current] ) );
   m_meshes << mesh;
   m_current++;
}


void MultiMesh::draw()
{
   if ( ! m_isMesh )
      return;

   m_meshes[m_current]->draw();
}


void MultiMesh::deleteAllMeshes()
{
   for ( int i = 0; i < m_meshes.size(); ++i ) {
      if ( m_meshes.at ( i ) != 0 ) {
         delete m_meshes[i];
         m_meshes[i] = 0;
      }
   }
   m_meshes.clear();
   m_isMesh = false;
}


QString MultiMesh::toString() const
{
   if ( ! m_isMesh )
      return QString ( "" );
   return QString ( "Level: %1 of %2\n" )
          .arg ( m_current + 1 )
          .arg ( m_meshes.size() )
          .append ( m_meshes[m_current]->toString() );
}


}
