//Ayesha_Khalid_22i2678
#include<iostream>
#include"Header.h"
#include <cstdlib>
#include<conio.h>
#include<ctime>
#include<chrono>
using namespace std;
void initializeGame(ElementQueue& obstacleQueue, ElementQueue& powerupQueue, PowerUpCollection& powerupCollection, CustomLinkedList* gameGraph, int gridSize) {
    srand(time(0));

   int i = 0;
		do {
		    int randomElement = rand() % 3;
		    switch (randomElement) {
		        case 0: {
		            int obstaclePower = 20 + (rand() % 10);
		            char obstacleSymbol = '#';
		            BoardElement* obstacleElement = new BoardElement(-1 * obstaclePower, obstacleSymbol);
		            obstacleQueue.Enqueue(obstacleElement);
		            break;
		        }
		        case 1: {
		            int obstaclePower = 15 + (rand() % 10);
		            char obstacleSymbol = '|';
		            BoardElement* obstacleElement = new BoardElement(-1 * obstaclePower, obstacleSymbol);
		            obstacleQueue.Enqueue(obstacleElement);
		            break;
		        }
		        default: {
		            int obstaclePower = 10 + (rand() % 10);
		            char obstacleSymbol = 'X';
		            BoardElement* obstacleElement = new BoardElement(-1 * obstaclePower, obstacleSymbol);
		            obstacleQueue.Enqueue(obstacleElement);
		            break;
		        }
		    }
		    i++;
		} while (i < gridSize);


   i = 0;
		do {
	    int randPowerup = rand() % 3;
	    int power;
	    char powerupSymbol;
	
	    switch (randPowerup) {
	        case 0:
	            power = 10 + (rand() % 10);
	            powerupSymbol = '$';
	            break;
	        case 1:
	            power = 15 + (rand() % 10);
	            powerupSymbol = '!';
	            break;
	        default:
	            power = 20 + (rand() % 10);
	            powerupSymbol = '\xE2';
	            break;
	    }
	
	    BoardElement* powerupElement = new BoardElement(power, powerupSymbol);
	    powerupQueue.Enqueue(powerupElement);
	    i++;
	} while (i < gridSize);


    // Initialize gameGraph
    bool goalReached = false;
    int randomStartColumn = rand() % gridSize;
    int randomEndColumn = rand() % gridSize;
      
    for (int i = 0; i < gridSize; i++) {
        int obstacleIndex = rand() % gridSize;
        int powerupIndex = rand() % gridSize;

        for (int j = 0; j < gridSize; j++) {
            if (i == 0 && j == randomStartColumn) {
                BoardElement* element = new BoardElement(0, 'E');
                gameGraph[i].Insert(element);
                goalReached = true;
                continue;
            }

            if (i == gridSize - 1 && j == randomEndColumn) {
                BoardElement* element = new BoardElement(0, 'C');
                gameGraph[i].Insert(element);
                continue;
            }

            if (j == obstacleIndex) {
                gameGraph[i].Insert(obstacleQueue.Front());
                obstacleQueue.Dequeue();
            } else if (j == powerupIndex) {
                gameGraph[i].Insert(powerupQueue.Front());
                powerupQueue.Dequeue();
            } else {
                BoardElement* element = new BoardElement(2, '*');
                gameGraph[i].Insert(element);
            }
        }
    }
}

int main()
{
			int elapsedTime = 0, discoveredElements = 0, numObstacles = 0, numPowerups = 0;
			int playerScore = 0;
    int gridSize = 3 + (rand() % 13);

			auto gameStartTime = chrono::steady_clock::now();
		 ElementQueue obstacleQueue;
    ElementQueue powerupQueue;
    PowerUpCollection powerupCollection;
    CustomLinkedList* gameGraph = new CustomLinkedList[gridSize];

    initializeGame(obstacleQueue, powerupQueue, powerupCollection, gameGraph, gridSize);
			
			int userChoice;
			while (1)
			{
			    cout << "One for Manual User Gameplay" << endl;
			    cout << "Two for Auto Gameplay" << endl;
			    cout << "Three for Exit" << endl;
			    cout << "Enter your choice: ";
			    cin >> userChoice;
			    system("cls");
			
			    if (userChoice == 1)
			    {
			        cout << "TIMER: 0 seconds" << endl;
			        DisplayGraph(gameGraph, gridSize);
			        cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			        cout << "COLLECTED POWER-UPS: ";
			        powerupCollection.Display();
			        cout << endl;			
			        int userInput;
			        while (1)
			        {
			            cout << "Press 'w' to move forward | 'd' to turn right | 'a' to turn left | 's' to turn back" << endl;
			            cout << "Enter your choice: ";
			            userInput = _getch();
			            system("cls");
			
			            if (userInput == 'w')
			            {
			                discoveredElements++;
			                auto currentTime = chrono::steady_clock::now();
			                auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - gameStartTime);
			
			                if (MoveUp(gameGraph, 'C', gridSize, powerupCollection, numObstacles))
			                {
			                    cout << "Game completed successfully, Thank You for Playing!" << endl;
			                    break;
			                }
			
			                cout << "TIMER: " << elapsedTime.count() << " seconds" << endl;
			                DisplayGraph(gameGraph, gridSize);
			                cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			                cout << "COLLECTED POWER-UPS: ";
			                powerupCollection.Display();
			                cout << endl;
			            }
							else if (userInput == 'd')
							{
								discoveredElements++;
			                auto currentTime = chrono::steady_clock::now();
			                auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - gameStartTime);
			
			                if (MoveUp(gameGraph, 'C', gridSize, powerupCollection, numObstacles))
			                {
			                    cout << "Game completed successfully!" << endl;
			                    break;
			                }
			
			                cout << "TIMER: " << elapsedTime.count() << " seconds" << endl;
			                DisplayGraph(gameGraph, gridSize);
			                cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			                cout << "COLLECTED POWER-UPS: ";
			                powerupCollection.Display();
			                cout << endl;
							}
							else if (userInput == 'a')
							{
								discoveredElements++;
			                auto currentTime = chrono::steady_clock::now();
			                auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - gameStartTime);
			
			                if (MoveUp(gameGraph, 'C', gridSize, powerupCollection, numObstacles))
			                {
			                    cout << "Game completed successfully!" << endl;
			                    break;
			                }
			
			                cout << "TIMER: " << elapsedTime.count() << " seconds" << endl;
			                DisplayGraph(gameGraph, gridSize);
			                cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			                cout << "COLLECTED POWER-UPS: ";
			                powerupCollection.Display();
			                cout << endl;
							}
							else if (userInput == 's')
							{
							discoveredElements++;
			                auto currentTime = chrono::steady_clock::now();
			                auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - gameStartTime);
			
			                if (MoveUp(gameGraph, 'C', gridSize, powerupCollection, numObstacles))
			                {
			                    cout << "Game completed successfully!" << endl;
			                    break;
			                }
			
			                cout << "TIMER: " << elapsedTime.count() << " seconds" << endl;
			                DisplayGraph(gameGraph, gridSize);
			                cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			                cout << "COLLECTED POWER-UPS: ";
			                powerupCollection.Display();
			                cout << endl;
							}
							else
							{
								cout << "Invalid input. Exiting..." << endl;
			                    break;
							}
						}
					}
					
				else if (userChoice == 2)
			{
			
			    cout << "TIMER: 0 seconds" << endl;
			    DisplayGraph(gameGraph, gridSize);
			    cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			    cout << "COLLECTED POWER-UPS: ";
			    powerupCollection.Display();
			    cout << endl;
			
			    int userMove;
			    while (1)
			    {
			        DisplayGraph(gameGraph, gridSize);
			        cout << "Press 'w' to move forward | 'd' to turn right | 'a' to turn left | 's' to turn back" << endl;
			        cout << "Enter your move: ";
			        userMove = _getch();
			        system("cls");
			
			        if (userMove == 'w' || userMove == 'd' || userMove == 'a' || userMove == 's')
			        {
			            discoveredElements++;
			            auto currentTime = chrono::steady_clock::now();
			            auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - gameStartTime);
			
			            bool gameOver = false;
			
			            switch (userMove)
			            {
			            case 'w':
			                gameOver = MoveUp(gameGraph, 'C', gridSize, powerupCollection, numObstacles);
			                break;
			            case 'd':
			                gameOver = TurnRight(gameGraph, 'C', gridSize, powerupCollection, numObstacles);
			                break;
			            case 'a':
			                gameOver = TurnLeft(gameGraph, 'C', gridSize, powerupCollection, numObstacles);
			                break;
			            case 's':
			                gameOver = MoveBackward(gameGraph, 'C', gridSize,powerupCollection, numObstacles);
			                break;
			            }
			
			            if (gameOver)
			            {
			                cout << "Game ended successfully!" << endl;
			                break;
			            }
			
			            cout << "TIMER: " << elapsedTime.count() << " seconds" << endl;
			            DisplayGraph(gameGraph, gridSize);
			            cout << "SCORE: " << playerScore << " | DISTANCE COVERED: " << discoveredElements << " | OBSTACLES HIT: " << numObstacles << endl;
			            cout << "COLLECTED POWER-UPS: ";
			            powerupCollection.Display();
			            cout << endl;
			        }
			        else
			        {
			            cout << "Invalid move. Exiting..." << endl;
			            break;
			        }
			    }
			}
			else if (userChoice == 3)
			    {
			        cout << "Exiting the game. Thank you for playing!" << endl;
			        break;
			    }
			    else
			    {
			        cout << "Invalid choice. Please enter a valid option." << endl;
			    }
		}
				return 0;
}