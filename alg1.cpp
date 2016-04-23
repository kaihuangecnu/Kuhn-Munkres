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

	Matrix<double> matrix = Matrix<double>(matrix_input);



	double t = 9.1;
        for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++  ) {
			if ( matrix(row,col) > t ) {
				matrix(row,col) = infinity;//prune weight > t .
			}		
		}
	}




	Munkres<double> m;
	int state = m.solve(matrix); // return state =0 means successful match; else means failure match.

	if (state==0) {
		printf("t=%lf,success!!!!!!!!\n\n\n",t);
		double sumweight = 0;// the sum of weights of selected edges.
		for ( int row = 0 ; row < nrows ; row++ ) {
			for ( int col = 0 ; col < ncols ; col++  ) {
				if (matrix(row,col) > -0.5) { // if the edge is a match
					printf("<%d, %d>: %lf\n",row,col,matrix_input(row,col));
					sumweight += matrix_input(row,col);
				}
			}
		}
		printf("The sum weights is: %lf\n", sumweight);
	} else {
		printf("t=%lf,failure !!!!!!!!!!!!!!!!!!!1\n\n\nfailure!!!!!!!!!!!!!!!!!!!!!!!!!1\n\n\n",t);
	}
        


	return 0;
}
