#ifndef __RIB_PARSER_H
#define __RIB_PARSER_H

//#include <string>

//#include <boost/spirit.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/spirit/include/classic.hpp>
//#include <boost/spirit/phoenix.hpp>

#include "glman_lib/scene.h"

namespace rib
{
    // A plain function
    void printDbl(double const& d)
    {
        std::cout << "dbl: " << d << std::endl;
    }

    using namespace boost::lambda;
    using namespace boost::spirit::classic;
    using namespace phoenix;

    typedef char                    char_t;
    typedef file_iterator<char_t>   iterator_t;
    typedef scanner<iterator_t>     scanner_t;
    typedef rule<scanner_t>         rule_t;

    struct Syntax : public grammar<Syntax>
    {
        Syntax(scene::Scene &target) :scn(target){ }

        template <typename ScannerT>
        struct definition
        {
            definition(Syntax const &self)
            {
                // General types
                ribString       =   '"' >> +(alnum_p | '.') >> "\"";

                ribDouble = real_p[&printDbl];
                ribInnerVector  =   ribDouble >> ribDouble >> ribDouble;
                ribVector       =   ribInnerVector | ('[' >> ribInnerVector >> ']');

                ribInnerColor   =   repeat_p(self.scn.getColorSize())[ real_p ];
                ribColor        =   ribInnerColor | ( '[' >> ribInnerColor >> ']' );

                ribArray        =   '[' >> (+real_p | +ribString) >> ']';
                ribParameter    =   ribString >> (real_p | ribVector | ribArray | ribColor | ribString);

                // Graphical state query definitions (without subcategories)
                worldBegin      =   str_p("WorldBegin");
                worldEnd        =   str_p("WorldEnd");
                topLevelGSRules =   worldBegin | worldEnd;

                // Options type definitions
                projection      =   str_p("Projection") >> '"' >> (str_p("perspective") | "orthographic") >> '"' >> !ribParameter;
                format          =   "Format" >> int_p >> int_p >> real_p;
                cameraRules     =   projection | format;

                display         =   "Display" >> ribString >> '"' >> (str_p("framebuffer") | "file") >> '"' >> ribString >> !ribParameter;
                //display[bind(&scene::Scene::setDisplay)(var(self.scn), display.str)];
                displayRules    =   display;

                colorSamples    =   "ColorSamples" >> ribArray >> ribArray;
                addOptionsRules =   colorSamples;

                optionRules     =   displayRules | cameraRules | addOptionsRules;
                
                // Attribute type definitions
                lightSource         =   "LightSource" >> ribString >> int_p >> *ribParameter;
                lightSourceRules    =   lightSource;
                
                color               =   "Color" >> ribColor;
                colorOpacityRules   =   color;

                surface             =   "Surface" >> ribString >> *ribParameter;

                sides               =   "Sides" >> int_p;
                orientSideRules     =   sides;

                attributeRules      =   colorOpacityRules | lightSourceRules | surface | orientSideRules;
                
                // Transformation type query definitions
                translate           =   "Translate" >> ribVector;
                rotate              =   "Rotate" >> real_p >> ribVector;

                transformationRules =   translate | rotate;

                // Aggregation of rules for graphic state
                graphicStateRules   =   topLevelGSRules | optionRules | attributeRules | transformationRules;
                
                // Geometric primitive type query definitions
                sphere          =   "Sphere"
                                        >> (('[' >> real_p >> real_p >> real_p >> real_p >> ']')
                                            | (real_p >> real_p >> real_p >> real_p))
                                        >> *ribParameter;
                quadricRules    =   sphere;

                geomPrimRules   =   quadricRules;

                // Defining a query and the contents of the file
				request     =   graphicStateRules | geomPrimRules;
                root        =  *request;
            }

            rule<ScannerT> const& start() const	{ return root; }

            // Lists of rules used
            rule<ScannerT>  root, request;
            rule<ScannerT>  ribString, ribDouble, ribInnerVector, ribVector, ribInnerColor, ribColor, ribArray, ribParameter;
            rule<ScannerT>  graphicStateRules,
                                topLevelGSRules, worldBegin, worldEnd;
            rule<ScannerT>  optionRules,
                                cameraRules, projection, format,
                                displayRules, display,
                                addOptionsRules, colorSamples;
            rule<ScannerT>  attributeRules,
                                colorOpacityRules, color,
                                lightSourceRules, lightSource,
                                surface,
                                orientSideRules, sides;
            rule<ScannerT>  transformationRules,
                                translate, rotate;
            rule<ScannerT>  geomPrimRules,
                                quadricRules, sphere;
        };

    private:
        scene::Scene &scn;
    };
}

#endif
