# UGE
A game engine for UA-Games

## Summary

UGE is a game engine designed to ease the development of UA-Games. UA-Games follow the principles of the Design for All, aiming to enable as many users as possible, regardless of their (dis)abilities, to play.
A good introduction to UA-Games is available at: <http://www.gamasutra.com/view/feature/1764/unified_design_of_universally_.php>.

UGE uses many of the Game Coding Complete 4 game engine features (described in McShaffry and Graham's book Game Coding Complete 4) combined with several open-source libraries to create a cohesive framework to develop UA-Games.
The engine's architecture and overall approach is described in the Documentation.

UGE is a work in progress and, therefore, is experimental and might be unstable.

## Evaluation

We are performing an evaluation of the engine approaches and available features.
Should you wish to participate or check out, please visit <https://github.com/francogarcia/uge-evaluation>.

## First Contact

If this is your first contact with UGE, it might be a good idea to read UGE in a Nutshell (<https://github.com/francogarcia/uge/raw/master/doc/UGE%20in%20a%20Nutshell.pptx>).
This is a quick, illustrated guide to learn about the engine's approaches and features.
Afterwards, for a full documentation, please refer to the Documentation.

## Getting Started

To start using UGE:

1. Download the source code from the repository;
2. Download the release files 'UGE-Dependencies.zip' and 'UGE-GameData.zip' from <https://github.com/francogarcia/uge/releases/tag/v0.1-beta>;
3. Extract the files from (2) into the root of the source code directory. Merge them to existing files if necessary;
4. Open the project's solution file under 'source/UGE_VS2012.sln' with Visual C++ or Visual Studio 2012;
5. Compile the project;
6. Before running a sample, please set the working directory (refer to the release or the documentation).

Afterwards, check the Documentation for general information and a step-by-step tutorial for setting up a new project and start using UGE to implement your game.

## Documentation

An extensive documentation is available in the 'doc' directory. There are also many code snippets for different features of the engine.
The documentation is not complete at the moment, though. However, it should be enough for many of the most important core features of UGE.
If you notice any important omissions, please contact me.

## License

This version of UGE is licensed under the LGPL license version 3 (<https://www.gnu.org/copyleft/lgpl> and <http://opensource.org/licenses/LGPL-3.0> for more information).
A copy of the license is avaliable at the directory

## Supported Platforms

Although most of UGE dependencies and the codebase itself are cross-platform, a few are currently Windows-only.
Therefore, UGE only supports Windows platforms at this moment.

## Required Toolchain

At this moment, Visual Studio or Visual C++ 2012 is required to compile the project.
Earlier versions are not supported, as UGE's require some C++11 features.

## Disclaimer of Warranty

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 'AS IS' WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

## Limitation of Liability

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
