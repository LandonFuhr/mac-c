# Mac C: A simple MacOS app in pure C.
This was a toy project to understand how MacOS apps work. Most tutorials will tell you to use Xcode which does all of the setup for you. I wanted to see what was actually happening.

## Build and run
To build:
```sh
clang mac-c.c -framework Cocoa -o "Mac C" -Wall -Wextra -Wpedantic
```

To run:
```sh
./Mac\ C
```

## Functionality
1. Open a window
2. Remove the ugly default toolbar
3. Quit on CMD+Q

## Experience and learnings
Coming into this I had no experience with Objective-C or Swift, and only moderate experience with C.

I learnt that Objective-C is a runtime that implements classes and methods via message passing. It turns C into a dynamic language. I don't know who thought that Objective-C was a good idea. It seems overly complicated.

I learnt that Objective-C is a superset of C and the entire language is basically synactic sugar. You can compile normal C programs with an Objective-C compiler. You can also achieve all of the same functionality as Objective-C in pure C, as demonstrated by this project. The synactic sugar is nice though because calling the Objective-C functions directly is very hard to read.

I learnt that Swift uses Objective-C under the hood. The core app APIs are still in Objective-C so Swift hooks into the Objective-C runtime.

I learnt that Xcode does a lot of stuff behind the scenes in projects. I think anyone who works in Xcode should do something like this project to learn the "magic" that Xcode is handling. It is much easier to solve problems when you know what's happening behind the scenes.

I learnt about the `-framework` compilation flag and `*.framework` folders. This is a MacOS-specific thing that is basically just a library.

## Credits
This was heavily based on the following StackOverflow post:
https://stackoverflow.com/questions/30269329/creating-a-windowed-application-in-pure-c-on-macos
