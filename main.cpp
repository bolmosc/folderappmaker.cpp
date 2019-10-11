#include "docopt.h"
#include "tinyxml2.h"
#include <iostream>
#include <unistd.h>
#include <map>
#include <sys/stat.h>
#include <windows.h>

using namespace tinyxml2;
using namespace std;

static const char USAGE[] =
R"(Example usage for Folder App Maker

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
)";

int dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

bool fileExists (const string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

int main(int argc, const char** argv)
{
    string dirBase="",dirPadre="", tipoStr="", rutaCompleta="", path="", exeDir="", tipoHijo="";
    int pos=0;
    char cwd[1024];
    char buffer[MAX_PATH];
    XMLDocument doc;

    //Se obtiene ruta del ejecutable
    GetModuleFileName(NULL,buffer,sizeof(buffer));
    exeDir = buffer;
    pos = exeDir.rfind("\\");
    path = exeDir.substr(0,pos+1);

    //Objeto para el manejo de parametros de consola
    map<string, docopt::value> args = docopt::docopt(USAGE,
                                                  { argv + 1, argv + argc },
                                                  true,               // show help if requested
                                                  "Folder App Maker 0.4.0");  // version string

/*    for(auto const& arg : args) {
        cout << arg.first << ": " << arg.second << endl;

    }*/

    //Se define el directorio base
    if(args["--base"].isString())
    {
        dirBase = args["--base"].asString();
    }
    else
    {
        dirBase = getcwd(cwd, sizeof(cwd));
    }

    //Se verifica existencia de directorio base
    if(dirExists(dirBase.c_str())==0 && args["--test"].asBool() == false)
    {
        cout<<dirBase<<endl<<"!Directorio base inexistente!, se aborta proceso.";
        return 0;
    }

    //Se carga archivo de configuracion de directorios
    path = path+"dirs.xml";
    if(fileExists(path))
       doc.LoadFile(path.c_str());
    else
    {
        cout<<"!Advertencia! Archivo config no encontrado:"<<endl<<path;
        return 0;
    }

    if(args["--config"].asBool())
    {
        cout<<"Archivo de configuracion de rutas: "<<path<<endl;
        doc.Print();
        return 0;
    }

    //Se define el directorio final padre
    dirPadre = dirBase + "\\" + args["<name>"].asString();

    //Se verifica existencia de directorio padre
    if(dirExists(dirPadre.c_str())==1 && args["--test"].asBool() == false && args["--append"].asBool() == false)
    {
        cout<<dirPadre<<endl<<"!Directorio padre existente!, se aborta proceso.";
        return 0;
    }

    //Se establece el tipo de estructura, default si no fue proporcionado.
    if(args["--type"].isString())
    {
        tipoStr = args["--type"].asString();
    }
    else
    {
        tipoStr = "default";
    }

    //Se localiza el tipo de estructura
    XMLElement* element = doc.FirstChildElement("directorios")->FirstChildElement(tipoStr.c_str());

    if(element == nullptr)
    {
        cout<<"Error, no se encuentra el nombre de estructura indicada";
        return 0;
    }


    //Se muestra o crea ruta Padre
    if(args["--test"].asBool() == true)
        cout<<"Estructura resultante:"<<endl<<dirPadre;
    else
    {
        if(mkdir(dirPadre.c_str()) == 0 && args["--verbose"].asBool() == true)
            cout<<"Estructura resultante:"<<endl<<dirPadre+" ...created!";
    }

    for(XMLElement* ele = element->FirstChildElement("dir");
		ele;
		ele = ele->NextSiblingElement() )
    {
        //Se muestra o crea Directorio hijo
        rutaCompleta = dirPadre+"\\"+ele->GetText();
        tipoHijo = ele->Attribute("tipo");

        if(tipoHijo == "Base" || args["--full"].asBool() == true)
        {
            if(args["--test"].asBool() == true)
            {
                cout<<endl<<rutaCompleta;
            }
            else
            {
                if(mkdir(rutaCompleta.c_str()) == 0 && args["--verbose"].asBool() == true)
                    cout<<endl<<rutaCompleta+" ...created!";
            }
        }
	}

    return 0;
}


