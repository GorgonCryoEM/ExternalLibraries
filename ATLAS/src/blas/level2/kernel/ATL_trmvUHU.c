/* ---------------------------------------------------------------------
 *
 * -- Automatically Tuned Linear Algebra Software (ATLAS)
 *    (C) Copyright 2000 All Rights Reserved
 *
 * -- ATLAS routine -- Version 3.2 -- December 25, 2000
 *
 * -- Suggestions,  comments,  bugs reports should be sent to the follo-
 *    wing e-mail address: atlas@cs.utk.edu
 *
 * Author         : Antoine P. Petitet
 * Contributor(s) : R. Clint Whaley
 * University of Tennessee - Innovative Computing Laboratory
 * Knoxville TN, 37996-1301, USA.
 *
 * ---------------------------------------------------------------------
 *
 * -- Copyright notice and Licensing terms:
 *
 *  Redistribution  and  use in  source and binary forms, with or without
 *  modification, are  permitted provided  that the following  conditions
 *  are met:
 *
 * 1. Redistributions  of  source  code  must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce  the above copyright
 *    notice,  this list of conditions, and the  following disclaimer in
 *    the documentation and/or other materials provided with the distri-
 *    bution.
 * 3. The name of the University,  the ATLAS group,  or the names of its
 *    contributors  may not be used to endorse or promote products deri-
 *    ved from this software without specific written permission.
 *
 * -- Disclaimer:
 *
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO,  PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEO-
 * RY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (IN-
 * CLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ---------------------------------------------------------------------
 */
/*
 * Include files
 */
#include "atlas_misc.h"
#include "atlas_mv.h"
#include "atlas_r1.h"
#include "atlas_level1.h"
#include "atlas_kernel2.h"
#include "atlas_reflvl2.h"
#include "atlas_lvl2.h"

#ifdef TREAL
#define    MinN_trmvUHU      16
#else
#define    MinN_trmvUHU       8
#endif

void Mjoin( PATL, trmvUHU )
(
   const int                  N,
   const TYPE                 * A,
   const int                  LDA,
   TYPE                       * X
)
{
/*
 * Purpose
 * =======
 *
 * Mjoin( PATL, trmvUHU ) performs the following matrix-vector operation
 *
 *    x := conjg( A' ) * x,
 *
 * where x is an n-element vector and  A  is an n by n  unit, upper tri-
 * angular matrix.
 *
 * This is a  recursive  version of the  algorithm.  For a more detailed
 * description of  the arguments of this function, see the reference im-
 * plementation in the  ATLAS/src/blas/reference directory.
 *
 * ---------------------------------------------------------------------
 */
/*
 * .. Local Variables ..
 */
#ifdef TREAL
#define    one                ATL_rone
#else
   const TYPE                 one[2] = { ATL_rone, ATL_rzero };
#endif
   TYPE                       * x0;
   int                        n1, n1s, n2;
/* ..
 * .. Executable Statements ..
 *
 */
   if( N <= MinN_trmvUHU )
   { Mjoin( PATL, reftrmvUHU )( N, A, LDA, X, 1 ); }
   else
   {
      n2 = N - ( n1 = ( N >> 1 ) ); n1s = (n1 SHIFT);
      MUrnext( n1, A, LDA ); x0 = X + n1s;
      Mjoin( PATL, trmvUHU )( n2, A, LDA, x0 );
      Mjoin( PATL, gemvC_a1_x1_b1_y1 )( n2, n1, one, A - n1s, LDA, X, 1,
                                        one, x0, 1 );
      MUrprev( n1, A, LDA ); Mjoin( PATL, trmvUHU )( n1, A, LDA, X );
   }
/*
 * End of Mjoin( PATL, trmvUHU )
 */
}
