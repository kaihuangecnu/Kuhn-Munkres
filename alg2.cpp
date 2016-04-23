/*
 *   Copyright (c) 2007 John Weaver
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/*
 * Some example code.
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "munkres.h"



int
main() {
	int nrows = 5;
	int ncols = 5;
	double infinity = std::numeric_limits<double>::infinity();
	Matrix<double> matrix_input = Matrix<double>({
		{7.0,6.0,3.5,4.6,8.0},
		{3.4,6.3,2.5,9.3,1.3},
		{9.1,1.7,8.1,3.4,5.6},
		{5.4,4.8,4.1,7.4,8.2},
		{4.5,7,4.4,2.1,6.2}});


	double l0 = matrix_input.min();
	double l2 = matrix_input.max();
	double l1 = (l0+l2)/2;
	//printf("%lf,%lf,%lf\n",l0,l2,l1);




	Matrix<double> matrix = Matrix<double>(matrix_input);


	for ( int row = 0 ; row < nrows ; row++ ) {
                for ( int col = 0 ; col < ncols ; col++  ) {
                        if ( matrix(row,col) > l1 ) {
                                matrix(row,col) = infinity; // prune weight > l1
                        }               
                }
        }

	while (l2-l1>0.05) {// repeat until l2==l1
		Munkres<double> m;
		if (m.solve(matrix)==1) {// 
			l1 = (l1+l2)/2;
		} else {//
			l2 = l1;
			l1 = (l0+l1)/2;
		}
		matrix = Matrix<double>(matrix_input);

////
	        for ( int row = 0 ; row < nrows ; row++ ) {
        	        for ( int col = 0 ; col < ncols ; col++  ) {
                	        if ( matrix(row,col) > l1 ) {
                        	        matrix(row,col) = infinity;//prune weight > l1
                        	}
                	}
        	}

	}

	printf("min weight is %lf, max weight is %lf, min max weight is %lf\n",matrix_input.min(),matrix_input.max(),(l1+l2)/2);
	return 0;
}
