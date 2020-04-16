# FolderAppMaker
Crea estructura de carpetas previamente configuradas

Uso
======================================================================

    Usage:
      folderappmaker  [--type=<struct>] [--base=<dir>] <name> [--full] [--verbose | --test] [--append]
      folderappmaker  (-h | --help)
      folderappmaker  --version
      folderappmaker  --config

    Options:
      -f --full        Create full structure.
      -h --help     Show this screen.
      -v --verbose  Show result on screen.
      -r --base=<ruta>  Path base for the structure [detault: current path].
      -t --test  Show structure on screen without creating it.
      -s --type=<struct>  Indicate the type of structure to use of the config file [default if null].
      -a --append  Append the structure to the existing path.
      --version     Show version.
      --config   Show the directories of the configuration file.

Ejemplos

    #1
	folderappmaker NombreApp
		Crea carpetas basicas para estructura default de NombreApp en ruta Base.

     #2
	 folderappmaker --type=proyecto NombreProyecto
		Crea carpetas basicas para estructura proyecto de NombreProyecto en ruta Base.
    
     #3
	 folderappmaker NombreApp --rutabase="D:\Carpeta" --full
		Crea listado completo de carpetas en la ruta base especificada con la estructura default de NombreApp

     #4
	 folderappmaker NombreApp --rutabase="D:\Carpeta" --full --test
		Muestra listado completo de carpetas (sin crearlas) en la ruta base especificada de NombreApp

Instalación
======================================================================

Copiar el contenido de la carpeta bin y pegar en ``ruta``

    FolderAppMaker.exe
    LICENSE-MIT.txt
    LICENSE.txt
    dirs.xml

Donde ``ruta`` es cualquier directorio.

Agregar ``ruta`` dentro de las variables de entorno **PATH** de usuario

Licencia
======================================================================

	Folder App Maker, Crea estructura de carpetas previamente condiguradas.
	Benjamin Olmos Carrillo <bolmosc1@gmail.com>

	--------------------------------------------------------------------------------
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
	--------------------------------------------------------------------------------

	For more details about license see the file LICENCE.txt.
	
	--------------------------------------------------------------------------------
	
	Folder App Maker utiliza:

        -docopt
	docopt.cpp is licensed under the MIT License. For more details about license see the file LICENSE-MIT.txt

	-CodeBlocks
	Code::Blocksis distributed under the GNU General Public License, version 3, which means it can be used freely by anyone!

	-TinyXML-2
	TinyXML-2 is released under the zlib license
