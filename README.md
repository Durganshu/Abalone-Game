# Abalone Game

Abalone is a board game of class "2-Person Zero-Sum Game with Complete Information". Zero-sum means that an advantage of one player is exactly the disadvantage of his opponent. Complete information is given as there is no randomness or unknown information for the players in the game (such as dice or hidden cards).

Rules of Abalone are available at

  [https://ultraboardgames.com/abalone/game-rules.php](https://ultraboardgames.com/abalone/game-rules.php)

We've implemented our search strategy to the base version of Abalone by Josef Weidendorfer.

The complete base code consists of network protocols, evaluation strategy, and search strategies: 'ABID' and 'OneLevel'. We've implemented 'MinMax', based on the Mini-Max search algorithm, and 'AlphaBeta', based on the Alpha-beta pruning of the Mini-Max search algorithm. 'AlphaBeta' is OpenMP enabled and uses PV splitting (more on this in the later sections) for achieving parallelism.


Network protocol
========================

The network protocol is based on broadcasting board states on a virtual communication bus, identified by a host/port TCP address, on which one of the communicating game processes listens. The default is "localhost:23412"; two game processes started on one machine automatically can exchange data.

The default bus ID can be overridden by command line options "-p <port>" and "-h <hostname>." If something goes wrong, debug information is printed via "-v" or "-vv" (more verbose). Every process first opens a listening socket on the port address provided for others to be able to send a message to the process.
If a port is already used, the next port number is tried. This way, multiple processes can run on one machine.

Processes on a virtual communication bus know each other. Broadcasts are multiple messages sent to all communication partners. For every message, a new TCP connection is opened and afterward closed again. This improves reliability if processes are crashing.

Search Strategies
========================

Coming soon...

Usage
========================

Dependencies
------------------------

- g++ or Intel C++ compiler (icpc)
- make
- git
- OpenMP

Installation
------------------------

```shell
git clone https://github.com/Durganshu/Abalone-Game.git
cd Abalone-Game
make
```

Program "player"
------------------------

This is a computer player using a given stone color. Colors are either "O" (default) or "X" and can be specified as a command line parameter. E.g., to play color X, use `./player X`. 

A computer strength can be specified as another command line parameter and is forwarded to the gameplay strategy used. However, one can think of strategies where strength is unnecessary, e.g., when playing against time. Whenever the player receives a board position where his color is about to draw, he starts "thinking," after finding a move, he broadcasts the resulting board position.

To get more details and parameters, use the following:
`./player --help`


Program "start"
----------------

This starts programs by broadcasting a specified position, defaulting to the starting position of Abalone.  After that, it observes the communication bus and logs any received positions to the terminal. Other positions may be specified by a file containing a position in ASCII art (using the same style as "start" when logging positions to the terminal).

To get more details and parameters, use the following:
`./start --help`

Program "referee"
------------------

First, this does the same as "start" but uses two communication buses. Afterward, it forwards game positions between these two busses and checks whether subsequent game positions follow the game rules. If not, the referee complains and does not forward the position. Game positions are numbered and contain a time. Both are corrected by the referee if needed. This way, players cannot cheat. However, using a referee is optional.

The referee forwards a game position only if it has detected another process running on the other bus. It blocks until a process appears.

To get more details and parameters, use the following:
`./referee --help`

Starting the game (on one machine):
-----------------------

Without referee:

```shell
./player O & ./player X & ./start
 ```

With referee:
 ```shell
./player -p 3000 O & ./player -p 4000 X & ./referee -p 3000 -p 4000
```
 
Four different strategies are available, with 'AlphaBeta' being the default strategy (-s 0).

Any other strategy can be selected using the '-s ' flag while running the executable.

```shell
./player O -s 0 4 & ./player X -s 1 3 & ./start
```

If you want more details, use the '--help' flag with the executable.

The order of starting the programs does not matter. Similarly, if a program crashes or is killed, you can continue gameplay by restarting the terminated player.

With players on different machines using SSH tunneling
--------------------------------------------------------------

One player should run on the local host "local" (O) and one (X) on the host "remote", which is only reachable via SSH. As we want "start" to observe the game on the local host, the remote must be able to open two connections to the local host. Thus, we need 3 tunnels: one from local to remove and two from remote to local.

```shell
ssh -L 5000:localhost:5000 \
    -R 5001:localhost:5001 -R 5002:localhost:5002 remote
remote> ./player -p 5000 O
local>./player -p 5000 X &
local>./start -p 5000
```
Contributing to this repository
========================================================================

Implementing your strategy
--------------------------------------------------------------
Check out [search-onelevel.cpp](https://github.com/Durganshu/Abalone-Game/blob/main/search-onelevel.cpp) to see what is needed to write your strategy. Documentation is found in the comments. For another strategy (or parallelization with OpenMP), use this file as a template, and give the strategy a new name, which then can be specified for "player" by using the command line option "-s <strategy>". Run a player with "-h" for a list of compiled-in strategies.

For MPI, change players' main() in a way that rank 0 starts the already existing code, and all other MPI ranks should directly branch to your worker code for your strategy, waiting on requests from rank 0 (i.e., master-slave structure).

Implementing your evaluation strategy
--------------------------------------------------------------
Another possibility of a contribution is through making a new evaluation strategy. Check [eval.cpp](https://github.com/Durganshu/Abalone-Game/blob/main/eval.cpp)https://github.com/Durganshu/Abalone-Game/blob/main/eval.cpp for more details.

Contact
========================================================================

Feel free to drop an [email](mailto:durganshu.mishra@tum.de) for any feedback or possible collaborations.
