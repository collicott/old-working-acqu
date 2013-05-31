/**
 * Demo file for CBClustering.h
 * Compile with 
 * $ g++ example_CBClustering.cpp -o example_CBClustering
 * and then ./example_CBClustering
 */

#include "CBClustering.h"

#define NHITS 7

int main() {

	// crystals that fired
	int NaIHits[ NHITS ] = { 0,1,2,40,24,39,52 };

	// create a CBClustering instance
	CBClustering clu;

	int num_clusters = clu.NumClusters( NaIHits, NHITS );

	cout << "found " << num_clusters << " clusters" << endl;

	cout << " Here are the assigned cluster ids:" << endl;

	clu.PrintResult( NaIHits, NHITS );
	
	return 0;
}
