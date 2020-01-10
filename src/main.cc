#include <func.hh>

#define CFG_FILE "stud.conf"

int
main(int ac, char** av)
{
    auto app = new App();
         app->name("stud")
            ->version(0.1)
            ->release('a')
            ->desc("Practical file builder application")
            
            ->author("Manjeet Saini","itsmanjeet1998@gmail.com","-")
            ->config_file(CFG_FILE)
            
            ->sub("new",
                  "build a template structure to start",
                  "NAME",
                  func_new)
                  
                  
            ->sub("build",
                  "Build Practical File in Doc format",
                  "[]",
                  func_build);

    if (app->execute(ac,av)) {
        std::cout << "error while processing" << std::endl;
    }    

    delete app;
    return 0;
}