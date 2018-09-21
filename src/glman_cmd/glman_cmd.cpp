#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <fstream>
#include <iterator>

namespace logging = boost::log;
using namespace std;

#include "glman_lib/loaders/rib_loader.h"
#include "glman_lib/scene.h"


// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
    return os;
}

int main(int argc, char **argv) {
  logging::core::get()->set_filter(
    logging::trivial::severity >= logging::trivial::debug
  );

  try { 
    int opt;
    string config_file;

    // Declare a group of options that will be 
    // allowed only on command line
    namespace po = boost::program_options; 
    po::options_description generic("Options"); 
    generic.add_options() 
      ("help", "Print help messages") 
      ("add", "additional options") 
      ("like", "this");

    // Declare a group of options that will be 
    // allowed both on command line and in
    // config file
    po::options_description config("Configuration");
    config.add_options()
        ("optimization", po::value<int>(&opt)->default_value(10), 
              "optimization level")
        ("include-path,I", 
             po::value< vector<string> >()->composing(), 
             "include path")
        ;

    // Hidden options, will be allowed both on command line and
    // in config file, but will not be shown to the user.
    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("input-file", po::value< vector<string> >(), "input file")
        ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config).add(hidden);

    po::options_description visible("Allowed options");
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("input-file", -1);
 
    po::variables_map vm; 
    po::store(po::command_line_parser(argc, argv).
      options(cmdline_options).positional(p).run(), vm); // can throw 
    po::notify(vm); // throws on error, so do after help in case there are any problems

    ifstream ifs(config_file.c_str());
    if (!ifs)
    {
        cout << "No config file provided but that's totally fine." << config_file << "\n";
    }
    else
    {
        store(parse_config_file(ifs, config_file_options), vm);
        notify(vm);
    }

    /** --help option 
     */ 
    if ( vm.count("help")  ) 
    { 
      cout << "Basic Command Line Parameter App" << endl 
        << generic << endl; 
      return 0; 
    }

    if (vm.count("version")) {
      cout << "GLMan, version 0.0\n";
      return 0;
    }

    if (vm.count("input-file"))
    {
        cout << "Input files are: " 
             << vm["input-file"].as< vector<string> >() << "\n";
    } 

 
    // application code here //
    string sceneFilename("tutoriel.rib");
    if (argc > 1)
        sceneFilename = argv[1];

    scene::Scene loadedScene;
    rib::RIB_Loader ribLoader;
    if (ribLoader.load(sceneFilename, loadedScene)) {
        cout << "File " << sceneFilename << " loaded successfuly !" << endl;
    }
     
    return 1;
 
  } 
  catch(exception& e) 
  { 
    std::cerr << "Unhandled Exception reached the top of main: " 
              << e.what() << ", application will now exit" << std::endl; 
    return 1; 
 
  } 
 
  return 0;
}