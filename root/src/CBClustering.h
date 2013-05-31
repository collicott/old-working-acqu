/**
 * @file CBClustering.h
 * @author Oliver Steffen <steffen@kph.uni-mainz.de>
 * @date   Nov 19, 2012
 */

#ifndef _CBCLUSTERING_H
#define _CBCLUSTERING_H

#include <iostream>
#include <iomanip>

using namespace std;

class CBClustering {

	protected:

		int id;
		int clid[180];

		/**
		 * @brief clear cluster id and fired arrays
		 */
		void _clear();

		/**
		 * @brief Set up the fired cluster direct lookup array
		 */
		void _setupFired( const int* pattern, const int ncryst );

		/**
		 * @brief Mark a crystal as visited and recursively check it's neighbours
		 * @param[in] cryst crystal number to look at
		 * @param[in] id to assign
		 * @return true if crystal has fired and has not been visited before, otherwise false
		 */
		bool NumberNeighbours( const int cluster, const unsigned int id );


	public:
		/**
		 * @brief Neighbouring information for logical crystals of size 4
		 * There are 180 logical crystals of this size.
		 * The array stores 12 neighbours of each logical crystal.
		 * The first 3 are the direct neighbours.
		 */
		static const int N4[180][12];


		/**
		 * @brief Ctor.
		 */
		CBClustering() { _clear(); };

		/**
		 * @brief Find the number of clusters of fired crystals and assign cluser ids
		 * @param[in] pattern Array of fired crystal indices
		 * @param[in] ncryst Number of fired crystals
		 * @retrun the number of clusters found
		 * The number of found clusters as well as the assigend cluster ids to the crystals are stored
		 * inside the class and can be obtained via #GetNumClusters() and #PrintResult()
		 */
		unsigned int NumClusters( const int* pattern, const int nclust );

		/**
		 * @brief Check if a crystal has fired
		 * @param[in] cryst ID of crystal to check
		 * @return fired yes/no
		 */
		inline bool isFired( const int cryst ) {
			return clid[ cryst ] == -3;
		};

		/**
		 * @brief Check if wa already visited this crystal
		 */
		inline bool isVisited( const int cryst ) {
			return ( clid[ cryst ] >= 0 );
		};


		/**
		 * @brief Get the number of found clusters in the last run of #NumberNeighbours()
		 * @return The number of found clusters
		 */
		inline int GetNumClusters() const { return id; };

		/**
		 * @brief Print crystlas fired and its assigend cluster ids of last run of #NumberNeighbours()
		 */
		void PrintResult( const int* pattern,  const int nclust ) const;

};



#endif
