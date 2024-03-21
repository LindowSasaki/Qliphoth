# Qliphoth

## A C++ project for learning WIN32API and showing off common Windows persistence mechanisms.
* It's name is derived from the "Qliphoth" or "Qlippoth" from the Kabbalah and Jewish Mysticism and representts evil or impure spirtual forces. It is considered the opposite of the "Sefirot" or "Sephiroth" which represents good or pure spiritual forces. Each one of these "trees" as they are often mentioned contains 10 visible "spheres" or "branches" with a hidden 11th.
* This project draws inspiration from this by creating 11 unique persistence mechanisms on a Windows machine (pretty loose I know). The inspiration mostly stops there, however more information and background on the Qliphoth tree can be found here: https://teaandrosemary.com/the-qliphoth-tree/

# Sephiroth

## A C++ project for learning WIN32API and detecting common Windows persistence mechanisms.
* Testing the Qliphoth part of this can often require multiple commands for cleaning up a system (especially if not testing on a VM!), this part of the project aims at using C++ to discover the persistence mechanisms that were used in the Qliphoth part, as well as eradicating them (if the flag is given to the function).
* This is otherwise known as the RAT Detector 3.0

# Main Goals
* To better learn C++, WIN32API, and make a project that can be used by security researchers and even students to become more educated on WIN32API abuse and common persistence mechanisms used by threat actors and APTs.
* This project additionally will be restricted to non-domain Windows persistence mechanisms, and some will live exclusively in memory after running the program (you restart and they die, which is why its important for forensic analysts to capture RAM on a live machine).
* The intended audience like stated before is any interested security researcher and or students that want to educate themselves and even practice their skills if they so desire to run the program and identify all of the persistence mechanisms on their own.
