#include <func.hh>
#include <stud.hh>
#include <releax/config.hh>
#include <releax/filesys.hh>

int 
func_new(App *app)
{
    return 0;
}

int
func_build(App *app)
{
    if (!filesys::exist("practical.conf")) {
        std::cout << "No configuration file found" << std::endl;
        return 0;
    }

    auto conf = new Config("practical.conf");
    //std::string name = conf->get("name");
    
    Stud s(app->cfg);
    if (!filesys::exist(s.experiment_folder)) {
        std::cout << "no experiments folder found" << std::endl;
        return 0;
    }

    auto exprs =  filesys::list_all(s.experiment_folder);
    

    std::string file;
    for (auto exp : exprs) {
        file += s.process_expr(exp);
        file += "\n\n";
    }

    std::ofstream outfile("build/source.txt");
    outfile << file;
    outfile.close();

    s.build_proj("build/source.txt");

    return 0;
}