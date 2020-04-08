



#include "Security.h"

Security::Security()
{
}
Security::~Security()
{
}
string Security::DDSReadHash(int level,GlgSCADAViewer *ptr)
{

	ifstream  myfile;
	string file[2] = {"hash1.txt","hash2.txt"};
	string str;
    switch(level)
    {
    	case 1:
            myfile.open(file[0]);
    	 break;
    	case 2:
    		 myfile.open(file[1]);
    	 break;
    };
    if (myfile.is_open())
    {
           getline (myfile,str);
           myfile.close();
     }

    /*PASSWORDSTR *p;
    ptr->pDataFeed->ReadPassword(p);

    if(level == 1)
    {

              str = string(p->level1);

    }
    else if(level == 2)
    {

             str = string(p->level2);
    }*/

    return str;
}

void Security::DDSWriteHash(int level,char hash[HASH_LENGTH])
{
	ofstream  myfile;
	string file[2] = {"hash1.txt","hash2.txt"};
    switch(level)
    {
    	case 1:
            myfile.open(file[0]);
    	 break;
    	case 2:
    		 myfile.open(file[1]);
    	 break;
    };
    if (myfile.is_open())
    {
    	  myfile << createHash(hash) << endl;
    	  myfile.close();
     }
}

//
bool Security::AuthorizeLogin(string hashin,string hashout)
{
    bool result = false;
    cout << "hash 1 = "<< hashin << "   "<<"hash 2 = "<< hashout << endl;
    if(strcmp(hashin.c_str(),hashout.c_str()) == 0)
        result = true;
    return result;
}
//////////
string Security::createHash(char password[PASSWORD_LENGTH])
{
      unsigned char digest[(HASH_LENGTH - 1)/2];
      const char* string = password;

      MD5_CTX ctx;
      MD5_Init(&ctx);
      MD5_Update(&ctx, string, strlen(string));
      MD5_Final(digest, &ctx);
      char mdString[HASH_LENGTH];
      for (int i = 0; i < (HASH_LENGTH - 1)/2; i++)
          sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
      std::string hash = mdString;

      return hash;
}





