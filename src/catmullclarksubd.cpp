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
#include <QVariant>
#include "catmullclarksubd.h"

namespace PZSculpt
{

CatmullClarkSubd::CatmullClarkSubd() : Subdivider()
{
   m_level = 0;
   zeroContainers();
}


CatmullClarkSubd::~CatmullClarkSubd()
{
}


void CatmullClarkSubd::initContainers()
{
   m_cornerVertexes = new QHash<int, bool>;
   m_facePoints = new QList<int>;
   m_edgesPoints = new QHash<uint, int>;
   m_neighbourVertexes = new QHash<int, int>;
   m_nearFaces = new QHash<int, int>;
}


void CatmullClarkSubd::zeroContainers()
{
   m_cornerVertexes = 0;
   m_facePoints = 0;
   m_edgesPoints = 0;
   m_neighbourVertexes = 0;
   m_nearFaces = 0;
}


Mesh* CatmullClarkSubd::subdivide ( Mesh & oldMesh )
{
   m_oldMesh = &oldMesh;
   m_newMesh = new Mesh();
   m_level = 0;

   initContainers();

   copyVertexes ();
   generateFacePoints ();
   generateEdgePoints ();
   createFaces ();
   repositionOldVertex ();

   delete m_cornerVertexes;
   delete m_facePoints;
   delete m_edgesPoints;
   delete m_neighbourVertexes;
   delete m_nearFaces;
   zeroContainers();

   m_newMesh->finishConstrucion();

   return m_newMesh;
}


void CatmullClarkSubd::copyVertexes ()
{
   m_level = 0;
   for ( int i = 0; i < m_oldMesh->getPosCount(); ++i ) {
      m_newMesh->addPos ( m_oldMesh->pos ( i ) );
      if ( m_oldMesh->posPtr ( i )->getLevel() > m_level )
         m_level = m_oldMesh->posPtr ( i )->getLevel();
   }
   m_level++;

   for ( int i = 0; i < m_oldMesh->getTexCount(); ++i ) {
      m_newMesh->addTex ( m_oldMesh->tex ( i ) );
   }
}


void CatmullClarkSubd::generateFacePoints ()
{
   int current;
   for ( int i = 0; i < m_oldMesh->getFacesCount(); ++i ) {
      current = m_newMesh->getPosCount();
      m_facePoints->append ( current );
      m_newMesh->addPos ( m_oldMesh->faceMiddle ( i ), m_level );
   }
}


void CatmullClarkSubd::generateEdgePoints ()
{
   QHash<uint, int*> temp;

   Face *face;
   QString key;
   for ( int i = 0; i < m_oldMesh->getFacesCount(); ++i ) {
      face = m_oldMesh->facePtr ( i );
      for ( int j = 0; j < face->getCount(); ++j )
         fillEdgesHash ( temp, i, face->posSafe ( j ), face->posSafe ( j + 1 ) );
   }

   Vector3f v0, v1, v2, v3;
   QHashIterator<uint, int*> it ( temp );
   while ( it.hasNext() ) {
      it.next();

      Position v;
      v.setLevel ( m_level );

      v0 = m_newMesh->pos ( it.value() [0] );
      v1 = m_newMesh->pos ( it.value() [1] );

      if ( it.value() [3] != NO_VERTEX ) {
         v2 = m_newMesh->pos ( m_facePoints->at ( it.value() [2] ) );
         v3 = m_newMesh->pos ( m_facePoints->at ( it.value() [3] ) );
         v.setPlace ( ( v0 + v1 + v2 + v3 ) / 4.0f );
      }
      else {
         v.setPlace ( ( v0 + v1 ) / 2.0f );
         //Boundary vertexes
         ( *m_cornerVertexes ) [ it.value() [0] ] = true;
         ( *m_cornerVertexes ) [ it.value() [1] ] = true;
      }

      ( *m_edgesPoints ) [ it.key() ] = m_newMesh->getPosCount();
      m_newMesh->addPos ( v );

      delete [] it.value();
   }
}


void CatmullClarkSubd::createFaces ()
{
   uint key0, key1;
   Face *face;
   int number;
   int texture;
   int faceTexture;
   int current, before, after;
   Vector3f pos;

   for ( int i = 0; i < m_oldMesh->getFacesCount(); ++i ) {
      face = m_oldMesh->facePtr ( i );
      faceTexture = makeFaceTexture ( face );
      for ( int j = 0; j < face->getCount(); ++j ) {
         before = face->posSafe ( j );
         current = face->posSafe ( j + 1 );
         after = face->posSafe ( j + 2 );

         key0 = getEdgeKey ( before, current );
         key1 = getEdgeKey ( current, after );

         if ( m_edgesPoints->contains ( key0 )
               &&
               m_edgesPoints->contains ( key1 ) ) {
            number = m_newMesh->getFacesCount();
            m_newMesh->addFace ( 4 );

            texture = makeEdgeTexture ( face, j, j + 1 );
            m_newMesh->facePtr ( number )->addPoint ( ( *m_edgesPoints ) [key0],
                  texture );
            texture = face->texSafe ( j + 1 );

            m_newMesh->facePtr ( number )->addPoint ( current, texture );
            texture = makeEdgeTexture ( face, j + 1, j + 2 );
            m_newMesh->facePtr ( number )->addPoint ( ( *m_edgesPoints ) [key1],
                  texture );
            m_newMesh->facePtr ( number )->addPoint ( m_facePoints->at ( i ),
                  faceTexture );

            //Push stuff for old Vertexes
            //For old vertexes
            m_nearFaces->insertMulti ( current, m_facePoints->at ( i ) );

            m_neighbourVertexes->insertMulti ( current, before );
            m_neighbourVertexes->insertMulti ( current, after );
         }
      }
   }
}


int CatmullClarkSubd::makeFaceTexture ( Face * face )
{
   Vector3f v ( 0.0f, 0.0f, 0.0f );

   for ( int i = 0; i < face->getCount(); ++i ) {
      v += m_newMesh->tex ( face->texAt ( i ) );
   }

   v /= face->getCount ();

   m_newMesh->addTex ( v, m_level );
   return m_newMesh->getTexCount() - 1;
}


int CatmullClarkSubd::makeEdgeTexture ( Face * face, int edgePoint0, int edgePoint1 )
{
   int tex0 = face->texSafe ( edgePoint0 );
   int tex1 = face->texSafe ( edgePoint1 );

   Vector3f v = ( m_newMesh->tex ( tex0 ) + m_newMesh->tex ( tex1 ) ) / 2.0f;

   m_newMesh->addTex ( v, m_level );
   return m_newMesh->getTexCount() - 1;
}


inline  int CatmullClarkSubd::getEdgeKey ( int one, int two )
{
   return m_oldMesh->generateEdgeKey ( one, two );
}


void CatmullClarkSubd::fillEdgesHash ( QHash<uint, int*> & hash,
                                       int face,
                                       int edgeOne,
                                       int edgeTwo )
{
   uint key = getEdgeKey ( edgeOne, edgeTwo );

   if ( hash.contains ( key ) ) {
      hash[key][3] = face;
   }
   else {
      hash[key] = new int[4];
      hash[key][0] = edgeOne;
      hash[key][1] = edgeTwo;
      hash[key][2] = face;
      hash[key][3] = NO_VERTEX;//-1
   }
}


void CatmullClarkSubd::repositionOldVertex()
{
   int n;
   QList<int> Q;
   QSet<int> R;
   Vector3f vQ;
   Vector3f vR;
   Vector3f vS;
   Vector3f middle;

   for ( int i = 0; i < m_newMesh->getPosCount(); ++i ) {
      //My C2 algo implementation garantues that old verts comes first

      if ( m_newMesh->posPtr ( i )->getLevel() >= m_level )
         break;

      if ( m_cornerVertexes->contains ( i ) ) {//Boundary
         vS = m_newMesh->pos ( i ) * 0.5f;
         vR.setPlace ( 0.0f, 0.0f, 0.0f );
         R = m_neighbourVertexes->values ( i ).toSet();
         QSetIterator<int> itr ( R );
         int number;
         while ( itr.hasNext() ) {
            number = itr.next();
            if ( m_cornerVertexes->contains ( number ) )
               vR += ( m_oldMesh->pos ( i ) +
                       m_oldMesh->pos ( number ) ) * 0.125f;
         }
         m_newMesh->posPtr ( i )->setPlace ( vR + vS );
      }
      else {//Non-Boundary
         vR.setPlace ( 0.0f, 0.0f, 0.0f );
         R = m_neighbourVertexes->values ( i ).toSet();
         QSetIterator<int> itr ( R );
         while ( itr.hasNext() ) {
            middle = ( m_oldMesh->pos ( i ) +
                       m_oldMesh->pos ( itr.next() ) ) / 2.0f;
            vR += middle;
         }
         vR = vR / R.count() * 2.0f;

         Q = m_nearFaces->values ( i );
         n = Q.size();
         vQ.setPlace ( 0.0f, 0.0f, 0.0f );
         for ( int j = 0; j < n; ++j )
            vQ += m_newMesh->pos ( Q[j] );

         vQ /= n;

         vS = m_newMesh->pos ( i ) * ( n - 3 );
         m_newMesh->posPtr ( i )->setPlace ( ( vQ + vR + vS ) / n );
      }
   }
}


}
