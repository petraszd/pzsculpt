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
#ifndef PZSCULPTMESH_H
#define PZSCULPTMESH_H

#include <QList>
#include <QHash>
#include "drawable.h"
#include "cordinate.h"
#include "position.h"
#include "face.h"
#include "edge.h"
#include "config.h"

namespace PZSculpt
{

typedef QList<Position*> PositionData;
typedef QList<Cordinate*> TextureData;
typedef QList<Face*> FaceData;
typedef QHash<int, Edge*> EdgeData;

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class Mesh : public Drawable
{
   protected:
      PositionData m_posData;
      TextureData m_texData;
      FaceData m_faceData;
      EdgeData m_edgeData;

      bool m_allQuads; //For faster rendering

      //Needed for edgeKey generation
      int m_shiftAmount;

   public:
      Mesh ();
      Mesh ( Mesh & mesh );
      ~Mesh();

      virtual void draw();
      void finishConstrucion();
      void getMetrics ( Vector3f & center, GLfloat & radius );
      int generateEdgeKey ( int one, int two );
      void recalculateNormalAll();
      void recalculateNormal ( Face *face );

      Vector3f faceMiddle ( int face );
      Vector3f faceMiddle ( Face *face );
      Vector3f faceMiddle ( Face & face );

      QString toString() const;
   protected:
      void recalculateFaceNeighbors();
      void recalculatePosNeighbors();
      void initShiftAmount();

      void addPos ( Position *pos ) {
         pos->setNumber ( m_posData.size() );
         m_posData << pos;
      }

   public:
      int getFacesCount() const {
         return m_faceData.size();
      }


      void addFace ( int count ) {
         m_faceData << new Face ( count );
      }


      void addFace ( const Face & face ) {
         m_faceData << new Face ( face );
      }


      Face* facePtr ( int number ) {
         return m_faceData[number];
      }


      Face face ( int number ) {
         return * ( m_faceData[number] );
      }


      int getPosCount() const {
         return m_posData.size();
      }


      void addPos ( GLfloat x, GLfloat y, GLfloat z, int level ) {
         addPos ( new Position ( x, y, z, level ) );
      }


      void addPos ( const Position & pos ) {
         addPos ( new Position ( pos ) );
      }


      void addPos ( const Cordinate & cord ) {
         addPos ( new Position ( cord ) );
      }


      void addPos ( const Vector3f & vector, int level ) {
         addPos ( new Position ( vector, level ) );
      }


      Position* posPtr ( int number ) {
         return m_posData[number];
      }


      Position pos ( int number ) const {
         return * ( m_posData[number] );
      }


      int getTexCount() const {
         return m_texData.size();
      }


      void addTex ( GLfloat x, GLfloat y, GLfloat z, int level ) {
         m_texData << new Cordinate ( x, y, z, level );
      }


      void addTex ( const Cordinate & cord ) {
         m_texData << new Cordinate ( cord );
      }


      void addTex ( const Vector3f & vector, int level ) {
         m_texData << new Cordinate ( vector, level );
      }


      Cordinate* texPtr ( int number ) {
         return m_texData[number];
      }


      Cordinate tex ( int number ) const {
         return * ( m_texData[number] );
      }


      Edge* edgePtr ( int key ) {
         return m_edgeData[key];
      }


      Edge* edgePtr ( int one, int two ) {
         int key = generateEdgeKey ( one, two );
         return m_edgeData[key];
      }


      Edge edge ( int key ) const {
         return * m_edgeData[key];
      }

      QList<int> edgeKeys() const {
         return m_edgeData.keys();
      }

};

}//end of namespace

#endif
