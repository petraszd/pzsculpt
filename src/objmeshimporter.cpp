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
#include "objmeshimporter.h"

#include <QVariant>


namespace PZSculpt
{

ObjMeshImporter::ObjMeshImporter()
      : MeshImporter()
{
}


ObjMeshImporter::~ObjMeshImporter()
{
}


Mesh* ObjMeshImporter::import ( QTextStream & stream )
{
   Mesh *mesh = new Mesh ();
//    QList<Cordinate> textures;
//    QList<Position> positions;

   QString line;
   QStringList stringList;
   QStringList faceList;
   GLfloat x;
   GLfloat y;
   GLfloat z;
   int number;
   int position;
   int texture;
   int defaultText = -1;

   stream.seek ( 0 );

   line = stream.readLine();

   while ( !line.isNull() ) {
      stringList = line.trimmed().split ( QRegExp ( "\\s+" ) );
      if ( stringList[0] == "v" ) {
         x = QVariant ( stringList[1] ).toDouble();
         y = QVariant ( stringList[2] ).toDouble();
         z = QVariant ( stringList[3] ).toDouble();
         mesh->addPos ( x, y, z, 0 );
      }
      else if ( stringList[0] == "vt" ) {
         x = QVariant ( stringList[1] ).toDouble();
         y = QVariant ( stringList[2] ).toDouble();
         mesh->addTex ( x, y, 0.0f, 0 );
      }
      else if ( stringList[0] == "f" ) {
         number = mesh->getFacesCount();
         mesh->addFace ( stringList.size() - 1 );
         for ( int i = 1; i < stringList.size(); ++i ) {
            faceList = stringList.at ( i ).split ( '/' );
            position = QVariant ( faceList[0] ).toInt() - 1;
            if ( faceList.size() > 1 && faceList[1] != "" ) {
               texture = QVariant ( faceList[1] ).toInt() - 1;
            }
            else {//We create default texture Cord
               if ( defaultText == -1 ) {
                  defaultText = mesh->getTexCount();
                  mesh->addTex ( 0.0f, 0.0f, 0.0f, 0 );
               }
               texture = defaultText;
            }

            mesh->facePtr ( number )->addPoint ( position, texture );
         }
      }

      line = stream.readLine();
   }

   mesh->finishConstrucion();
   return mesh;
}


}
