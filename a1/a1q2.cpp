#include "maze.h"
#include <iostream>

//function returns true if the end coordinate is found
bool pathFinder(int x, int y, Coord& way, const Coord &end, Maze& theMaze ,Coord path[], int *counter){

	//returns true when the current coordinate is equal to the end coordinate
	if(way.x == end.x && way.y == end.y){
		return true;
	}

	
	Coord temp;

	//sets appropriate x and y values for the temp coordinate
	temp.set(x,y);

	//Checks if the current coordinate is not in the Maze range and returns false if that is true
	if(way.x < 0 && way.x >= theMaze.width() && way.y < 0 && way.y >= theMaze.height()){
		return false;
	}

	
	//If the current coordinate is empty and not marked.If yes, then it marks the current coordinate and looks right,left,top and bottom sides. 
	if(theMaze.isEmpty(temp) && !theMaze.isMarked(temp)){

		theMaze.mark(temp);


		if(pathFinder(x+1, y, temp, end, theMaze, path, counter)){
			
			//Increases the step counter by 1 each time it finds an empty spot and also returns true
			*counter = *counter + 1;
			path[*counter] = {x, y};

			return true;

		}else if(pathFinder(x-1, y, temp, end, theMaze, path, counter)){
			
			*counter = *counter + 1;
			path[*counter] = {x, y};

			return true;

		}else if(pathFinder(x, y+1, temp, end, theMaze, path, counter)){

			*counter = *counter + 1;
			path[*counter] = {x, y};

			return true;

		}else if(pathFinder(x, y-1, temp, end, theMaze, path, counter)){

			*counter = *counter + 1;
			path[*counter] = {x, y};

			return true;
		}

			//If it finds no empty spots in the four directions then it unmarks the current coordinate and returns false.
			theMaze.unMark(temp);
			return false;

	}

	
}



int findPath (Maze& theMaze, const Coord& start, const Coord& end, Coord path[]){

	bool check = false;
	Coord way = start;
	int counter = 0;


	check = pathFinder(way.x,way.y, way, end, theMaze, path, &counter);
	
	//If the return from pathFinder function is true. Then, loop through the Coordinates, reverse the path array and store it into pathTemp
	//Iterate pathTemp again store the array values back into path array and return the counter
	if(check == true){
		
		Coord pathTemp[10000];
		
		for(int i =0; i <= counter ; i++){
			pathTemp[i] = path[counter - i];
		}
		for(int i =0; i <= counter ; i++){
			path[i] = pathTemp[i];
		}

		return counter;

	}else{
		return counter;
	}

}






