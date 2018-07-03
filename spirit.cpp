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
#include<stdio.h>
#include<curl/curl.h>
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

string str;
string type;
string repos;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void download(string name)
{
	CURL *curl;
    FILE *fp;
    CURLcode res;
	string pkg = name + ".banshee";
    char *url = ("https://ufpr.dl.sourceforge.net/project/ghostos-repo/" + name + ".banshee").c_str();
    char outfilename[FILENAME_MAX] = {pkg.c_str()};
	curl = curl_easy_init();
	if(curl)
		{
		    fp = fopen(outfilename,"wb");
		    curl_easy_setopt(curl, CURLOPT_URL, url);
		    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		    res = curl_easy_perform(curl);
		    curl_easy_cleanup(curl);
		    fclose(fp);
		}
}

void getrepofile()
{
	CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "https://ufpr.dl.sourceforge.net/project/ghostos-repo/repos.vision";
    char outfilename[FILENAME_MAX] = "/etc/spirit/repos.vision";
	curl = curl_easy_init();
	if(curl)
		{
		    fp = fopen(outfilename,"wb");
		    curl_easy_setopt(curl, CURLOPT_URL, url);
		    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		    res = curl_easy_perform(curl);
		    curl_easy_cleanup(curl);
		    fclose(fp);
		}
}

void getrepos()
{
	ifstream in("/etc/spirit/repos.vision");
	if(!in)
		{
			cout << "Repos.vision does not exist" << endl;
			cout << "Downloading from Hardcoded Repo" << endl;
			getrepofile();
			cout << "Done:Plaese Run" << endl;
			cout << "spirit update" << endl;
			cout << "to fetch new Database" << endl;
			system("exit");
		}
	getline(in,str);
	if(str == "\0")
		{
			cout << "Repos.vision is empty" << endl;
			cout << "Downloading from Hardcoded Repo" << endl;
			getrepofile();
			cout << "Done:Plaese Run" << endl;
			cout << "spirit update" << endl;
			cout << "to fetch new Database" << endl;
			system("exit");
		}
}

void getdb()
{
	CURL *curl;
    FILE *fp;
    CURLcode res;
	string db = "/etc/spirit/" + type + "_list.xml";
    char *url = ("https://ufpr.dl.sourceforge.net/project/ghostos-repo/" + type + "db.xml").c_str();
    char outfilename[FILENAME_MAX] = {db.c_str()};
	curl = curl_easy_init();
	if(curl)
		{
		    fp = fopen(outfilename,"wb");
		    curl_easy_setopt(curl, CURLOPT_URL, url);
		    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		    res = curl_easy_perform(curl);
		    curl_easy_cleanup(curl);
		    fclose(fp);
		}
}

int main(int argc, char* argv[])
{
    string array = argv[1];
    if(argc < 2)
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
            cout << "Please Enter the Package Name >>";
            getline(cin, packagename);
            Zipper zipper(packagename + ".banshee");
        	zipper.add(argv[2]);
            zipper.close();
        }
    if(array == "install")
        {
            string installer = argv[2];
            cout << installer << endl;
            Unzipper unzipper(installer + ".banshee");
            unzipper.extract("/");
            unzipper.close();
        }
	if(array == "clean")
		{
			system("rm -v /etc/spirit/grave/*.banshee");
			cout << "Grave is Emptied" << endl;
			system("exit");
		}
    if(array == "update")
        {
			getdb();
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
    system("ldconfig");
    cout << argc << " " << argv[1] << " " << "0" << " " << array <<  " " << "Ok" << endl;
}