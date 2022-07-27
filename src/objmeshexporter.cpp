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
#include "objmeshexporter.h"

namespace PZSculpt
{

const QString TOP_TEXT = ""
                         "# Petras Sculpt (Working Title) Exporter v0.1\n"
                         "# Software is under development. So is Exporter.\n"
                         "# File can be corupted.";

const QString OBJ_TEXT = "o PZSculpt_OBJ";


ObjMeshExporter::ObjMeshExporter() : MeshExporter()
{
}


ObjMeshExporter::~ObjMeshExporter()
{
}


void ObjMeshExporter::save ( QTextStream & stream, Mesh & mesh )
{
   stream << TOP_TEXT << "\n";
   stream << "\n" << OBJ_TEXT << "\n";

   Vector3f *v;

   stream << "\n# Vertexes ( " << mesh.getPosCount() << " )\n";
   for ( int i = 0; i < mesh.getPosCount(); ++i ) {
      v = mesh.posPtr ( i );
      stream << "v " << v->getX() << " "
      << v->getY() << " " << v->getZ() << "\n";
   }

   stream << "\n# Texture ( " << mesh.getTexCount() << " )\n";
   for ( int i = 0; i < mesh.getTexCount(); ++i ) {
      v = mesh.texPtr ( i );
      stream << "vt " << v->getX() << " "
      << v->getY() << " " << v->getZ() << "\n";
   }

   stream << "\n# Faces ( " << mesh.getFacesCount() << " )\n";
   Face *face;
   for ( int i = 0; i < mesh.getFacesCount(); ++i ) {
      stream << "f ";
      face = mesh.facePtr ( i );
      for ( int j = 0; j < face->getCount(); ++j ) {
         stream << ( face->posAt ( j ) + 1 );
         stream << "/" << ( face->texAt ( j ) + 1 );
         stream << " ";
      }
      stream << "\n";
   }
}

}
