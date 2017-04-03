TODO
=====

ncurses::Window
---------------
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
