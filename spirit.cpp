#include<iostream>
#include<sstream>
#include<fstream>
#include<istream>
#include<string>
#include<vector>
#include<cmath>
#include<math.h>
#include<cassert>
#include<ostream>
#include<map>
//Downloading
#include<arpa/inet.h>
//#include<curl/curl.h>
//Internet Connectivity 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
//Colour Changer
#include<termcolor/termcolor.hpp>
//zipping and unzipping
#include "zipper/zipper.h"
#include "zipper/unzipper.h"
#include "zipper/tools.h"

using namespace zipper;
using namespace std;
using namespace termcolor;

int main(int argc, char* argv[])
{
    string array = argv[1];
    if(argc != 2)
        {
            cout << "Wrong" << endl;
        }
    if(array.length() == 0)
        {
            cout << "Array = 0" << endl;
        }
    if(array == "create")
        {
            string packagename;
            cout << "Please Enter the Package Namwe >>";
            getline();
            Zipper zipper(packagename + ".banshee");
        	zipper.add(argv[2]);
            zipper.close();
        }
    if(array == "install")
        {
            string installer = argv[2];
            cout << installer << endl;
            Unzipper unzipper(installer + ".banshee");
            unzipper.extract("/usr");
            unzipper.close();
        }
    if(array == "update")
        {
            cout << "Tess" << endl;
        }
    if(array == "upgrade")
        {
            cout << "Tess" << endl;
        }
    if(array == "remove")
        {
            string remover = argv[2];
            cout << remover << endl;
        }
    if(array == "search")
        {
            string searcher = argv[2];
            cout << searcher << endl;
        }
    
    cout << argc << " " << argv[1] << " " << "0" << " " << array <<  " " << "Ok" << endl;
}