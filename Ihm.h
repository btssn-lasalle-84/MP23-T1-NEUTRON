/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        Ihm.h                                                               */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include <string>
#ifndef IHM_H
#define IHM_H

class Ihm
{
  public:
    Ihm();
    ~Ihm();

    void         afficherPlateau(Plateau& plateau) const;
    std::string* definirJoueurs() const;
}

#endif