/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        main.cpp                                                            */
/*                                                                            */
/*   By: Jérémy Mercklen                                                      */
/*                                                                            */
/*   Created: 2022/12/16 by J. Mercklen                                       */
/*   Updated: 2022/12/16 by J. Mercklen                                       */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "JeuNewton.h"

int main()
{
    JeuNewton partie;
    partie.demarrer();
#ifdef DEBUG
    std::cout << "Partie Finie" << std::endl;
#endif
    return 0;
}