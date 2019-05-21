/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#ifndef PIC_UTIL_GL_DISPLAY_HPP
#define PIC_UTIL_GL_DISPLAY_HPP

namespace pic {

#include <string>

#include "../../util/gl/technique.hpp"
#include "../../util/std_util.hpp"

#include "../../gl/filtering/filter_simple_tmo.hpp"

/**
 * @brief The DisplayGL class
 */
class DisplayGL
{
protected:
    pic::QuadGL *quad;
    pic::FilterGLSimpleTMO *tmo;
    pic::TechniqueGL technique;
    ImageGL *img_flt_tmo;

public:

    /**
     * @brief DisplayGL
     */
    DisplayGL()
    {
        //create a screen aligned quad
        pic::QuadGL::getTechnique(technique,
                                pic::QuadGL::getVertexProgramV3(),
                                pic::QuadGL::getFragmentProgramForView());

        quad = new pic::QuadGL(true);

        tmo = new pic::FilterGLSimpleTMO();

        img_flt_tmo = NULL;
    }

    ~DisplayGL()
    {
        delete_s(tmo);
        delete_s(quad);
        delete_s(img_flt_tmo);
    }

    /**
     * @brief Process
     * @param img_to_be_displayed
     */
    void Process(ImageGL *img_to_be_displayed)
    {
        //simple tone mapping: gamma + exposure correction
        img_flt_tmo = tmo->Process(SingleGL(img_to_be_displayed), img_flt_tmo);

        //visualization
        quad->Render(technique, img_flt_tmo->getTexture());
    }

};

} // end namespace pic

#endif /* PIC_UTIL_GL_DISPLAY_HPP */

