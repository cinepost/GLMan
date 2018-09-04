#include <algorithm>
#include <iostream>

#include "glman_lib/loaders/rib_loader.h"
#include "glman_lib/parsers/rib_parser.h"

#include "glman_lib/scene.h"

using namespace boost::spirit;
using namespace boost::spirit::classic;
using namespace std;
using namespace rib;
using namespace scene;

bool RIB_Loader::load(const std::string &filename, Scene &target)
{
    iterator_t fileBegin(filename);
    if (!fileBegin)
    {
        cout << "Unable to open file " << filename << endl;
        return false;
    }
    iterator_t fileEnd(fileBegin.make_end());

    Syntax syntax(target);
    rule<scanner_t> skipParser   = blank_p | comment_p('#') | eol_p;
    parse_info<iterator_t> pInfo = parse(fileBegin, fileEnd, syntax, skipParser);
    //pInfo                        = parse(pInfo.stop, fileEnd, skipParser);

    if (!pInfo.full)
    {
        if (pInfo.hit)
            cout << "Erreur d'analyse (offset " << pInfo.length << ") a la ligne: \"";
        else
            cout << "Erreur d'analyse (offset 0) a la ligne: \"";

        // Write error on standard output
        char_t currentChar = *pInfo.stop;
        bool isNewLine     = currentChar == '\n' || currentChar == '\r';
        while (currentChar != 0 && !isNewLine)
        {
            cout << currentChar;
            ++pInfo.stop;

            currentChar         = *pInfo.stop;
            isNewLine           = currentChar == '\n' || currentChar == '\r';
        }
        cout << "\"" << endl;
    }

    return pInfo.full;
}
