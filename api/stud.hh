#ifndef __STUD_HH__
#define __STUD_HH__

#include <bits/stdc++.h>
#include <releax/config.hh>

class Stud {
    std::string Code;
    Config* cfg;


public:
    Stud(Config *cfg);
    std::string experiment_folder = "experiments";
    std::vector<std::string> list_expr();
    std::string process_expr(std::string expr);
    std::string read_template(std::string templ_name);

    int build_proj(std::string infile);
};

#endif