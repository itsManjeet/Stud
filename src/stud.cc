#include <stud.hh>
#include <releax/filesys.hh>
#include <releax/sys.hh>

Stud::Stud(Config *cfg)
{
    this->cfg = cfg;
    if (!filesys::exist(experiment_folder)) {
        exit(5);
    }
}

std::string
readfile(std::string filename)
{
    std::ifstream f(filename);
    std::string str((std::istreambuf_iterator<char>(f)),
                    std::istreambuf_iterator<char>());

    return str;
}

void 
replace(std::string& str, 
  const std::string& from, 
  const std::string& to) 
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


std::string
Stud::
process_expr(std::string expr)
{
    std::string expr_folder = experiment_folder + "/" + expr;
    if (!filesys::exist(expr_folder)) {
        std::cout << "No experiment with name " + expr << std::endl;
        exit(5);
    }

    std::string out = read_template("page");
    std::string exprname = expr;
    replace(exprname,"_"," ");
    replace(out,"&EXP&",exprname);

    if(filesys::exist(expr_folder + "/aim")) {
        std::string aim = readfile(expr_folder + "/aim");
        replace(out,"<!--&AIM&-->","<b>Aim: </b> " + aim);
    }

    if (filesys::exist(expr_folder + "/algo")) {
        replace(out,"<!--&ALOG-->","<h2>Alog</h2>\n<ul>\n<!--&ALGO_LIST&-->\n</ul>");
        std::ifstream input(expr_folder + "/algo");
        for (std::string line; getline(input,line);) {
            replace(out,"<!--&ALGO_LIST&-->","<li>" + line + "</li>\n<!--&ALGO_LIST&-->");
        }
    }

    if (filesys::exist(expr_folder + "/" + expr )) {
        replace(out,"<!--&IMG&-->","<h3>Output: </h3>\n<img style=\"width: 80%;\" src=\"img/" + expr +"\">");
    }

    std::string str = readfile(expr_folder + "/code");
    replace(out,"&CODE&",str);
    return out;
}

std::string
Stud::read_template(std::string template_name)
{
    std::string template_dir = cfg->get("templates");
    if (!filesys::exist(template_dir)) {
        std::cout << "Template dir not exist '" + template_dir + "'\n" ;
        exit (5);
    }

    Config *c = new Config("practical.conf");

    std::string template_file = c->get(template_name,"none");
    if (template_file == "none") {
        template_file = template_dir + "/" + template_name + ".html";
    }
    
    delete c;

    std::ifstream f(template_file);
    if (f.good()) {
        std::string str((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());

        return str;
    }
    std::cout << "Template not found '" + template_file + "'\n" ;
    exit (6);
}

int
Stud::build_proj(std::string infile)
{
    return sys::execute("soffice " 
                        "--headless " 
                        "--infilter=writerglobal8_HTML "
                        "--convert-to pdf:writer_web_pdf_Export " 
                        "--outdir build/ " +
                        infile,".");
}