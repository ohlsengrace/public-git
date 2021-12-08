//Project 3
//Grace Ohlsen and Justin Jamrowski
# Project3 (CSCI 1300 - FALL 2021)

Link to Gameplay video:
https://drive.google.com/file/d/1lVnak9i0e1s_aXcLIk142pw6IdNETk94/view?usp=sharing
Must have CU email to access. If you want to view it, just contact me and I'll give you access.


DEFEAT THE METAVERSE: A TEXT-BASED ESCAPE ROOM GAME
Zuckerberg's Metaverse has taken over the world and entrapped society in a virtual dystopia. Your job is to deactivate the Metaverse
computer and save the world. Explore the map to collect the password and destruction file while avoiding viruses along the way.
The world is in your hands.

To compile:
g++ project3Driver.cpp CheatCode.cpp GameRoom.cpp Lobby.cpp Map.cpp Player.cpp SuperComputer.cpp

SCROLL TO BOTTOM FOR TRIVIA AND HANGMAN ANSWERS


PREPARATION
To prepare for this project, my partner Justin and I held a design meeting. In that meeting, we firstly came up with a narrative for the game that would be both interesting for us and the players. We decided to make an escape room so we could use the Map class as well as implement our own classes and features. Once we decided that we were doing an escape room, we drew out the map, where our objects would be placed, and what each class might look like. We also pinpointed where in the project we could implement the requirements, like sorting, randomization, user input, and menu choices. Finally, I taught my partner how to use Github so we could work on different parts of the project at the same time. 

CODE SKELETON
We developed our code skeleton by basing it off of our whiteboard drawing. We had a general idea of the classes we wanted as well as their member functions, mostly getters and setters as well as a few others. An important thing we had to keep in mind was how our classes would interact with each other, especially at initialization. A few variables had to be the same across multiple classes. Because of this, we had to make sure things were only being initialized in one class, then passed appropriately to the other classes. Paying attention to making default and parameterized constructors was really important for us. Once we developed the classes and the simple member functions, we were complete with our code skeleton and we utilized everything we wrote in our code skeleton throughout the project.

AREAS OF IMPROVEMENT
The one thing I wish I had done better is breaking up the main function into smaller parts. For our project, I was in charge of making the interaction() function, which basically displayed the game to the terminal. I wrote most of it all as one function and occasionally called smaller functions within it. I wish I had broken interaction() down into smaller functions so that it was easier to read and test. One thing my group did well was constant testing but it would have been easier to pinpoint the errors if each component of the game was its own function. Despite this flaw, I was pretty happy with how me and my partner executed our project.

FALSE STARTS
One of the false starts I had was deciding to write everything in one function within interaction(). For example, we had a game room with 3 “chat rooms”. Each chat room had its own text that would come up when you interacted with it on the map. I wrote all of that text into the interaction() function instead of it being a member function of the GameRoom class. I did this similar thing with other functions maybe 30 times. It made testing extremely difficult. So, I had to go back to each class and write what I call “interaction functions” so that all of it wasn’t in just one function. It took maybe 2 hours to rewrite the interaction() function so that it called member functions of the classes instead of how it was before. Other than that slip up, the project went pretty smoothly. I think what me and my partner did well was doing more work upfront to plan and get the code skeleton right before diving into the code. I think that saved us a lot of grief of not knowing how we wanted our project to look and function like.













Trivia Answers:
1) 2004
2) taurus
3) 2021
4) infra

Hangman Answers:
rat
fly
bug
