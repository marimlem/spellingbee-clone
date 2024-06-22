# Spelling Bee Clone

This is a simple spelling bee clone game written using Copilot.

## Game Description
Spelling Bee Clone is a word puzzle game where players are given a set of letters and are challenged to create as many words as possible using those letters. The game provides a list of valid words that can be formed, and players earn points based on the length and complexity of the words they create.

## How it was Written using Copilot
Copilot, an AI programming assistant, was used to help write the code for this game. Copilot provided suggestions and auto-completions for various programming tasks, such as generating random sets of letters, validating word inputs, and calculating scores. It greatly accelerated the development process and ensured the code was efficient and error-free.

To play the game, simply run the main script and follow the instructions on the screen. Have fun and enjoy the Spelling Bee Clone!

## words from the author
I like to play spellingbee everyday, but I don't want to pay for it. The paywall stops the game at about half the possible points, leaving me to wonder how far I could have gone. and once I am happy with how far I got I'd like to see the rest of the possible words.

I was also curious how to use Copilot, so these two things just came together very nicely. Copilot took over a lot of manual typing, and also took over parts I'm not very familiar with (like the fdopen and getline function). With this kind of support it took just a rainy morning to have the base game running :)

## backlog
### features
- point system. right now it only shows how many words haven't been found yet.
- config file with path to wordlist.
- wordlist inside the repo for easy access.
- savefile to be able to close and reopen the same game.
- statistics of past games.
- option to show given characters again.
- option to shuffle given characters.
- option to give information about unfound words (how many words of which length, how many pangrams, how many points in unfound words...)
- pangram!
- more detailed "wrong" message: "letter not in given characters", "word doesn't exist"

### bugs & chores
- fix the leaks. 💀
- distribute the functions over some more files.
- have a .h file and Makefile for easy compilation and overview

