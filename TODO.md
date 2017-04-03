TODO
=====

ncurses::Window
---------------
* NCCharType array strings are not normal c-strings but rather ncurses wide character type strings.
  These also hold attributes. Consider extractString and similar and work to ensure
  it is understood which one should be used in which circumstances. Additionally,
  we cannot simply return a string object so it would be best to write either a wrapper or helper function.
* Change ncCharType to something more expressive
* getline functions and extractString functions should throw on error
* Return of GetKeyStroke should probably have alias/user type
* Define defaults for Window dimensions
* Properly explain color pairs, setPalette, getColor and color types. Consider reworking so they are more expressive/idiomatic
* Find a better way to define attribute types
* Ensure that all ncurses functions that return ERR are properly wrapped with _onError
* Describe decorator functions as helper functions
* Normalize vocabulary in respect to row and col vs x and y
* If move cosntructors do soemthing special, document as appropriate
* Consider making attribute a struct/class to use RAII to reset attron/attroff
* Implement interface for all window functionality that needs to be exposed in Window class
* All string functions that take an n param should change to use std::strings and not using the n param


Ideas
=====
Idea for WebView

modelFromFile
modelFromURL
