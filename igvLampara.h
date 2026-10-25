//
// Created by juanan on 25/10/2026.
//

#ifndef PR2A_IGVLAMPARA_H
#define PR2A_IGVLAMPARA_H

#include "igvMallaTriangulos.h"

class igvLampara : public igvMallaTriangulos
{  public:

    // Constructores y destructor
    igvLampara ();
    igvLampara ( float r, float a, int divU, int divV );
    ~igvLampara ();

};

#endif //PR2A_IGVLAMPARA_H

