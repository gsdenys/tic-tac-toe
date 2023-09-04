# Tic-Tac-Toe Smart Contract

> _This is an implementation based on [EOSIO Development Tutorials](https://developers.eos.io/welcome/v2.1/tutorials/tic-tac-toe-game-smart-contract-single-node). Navigate to the page to more details._

This smart contract contains the tic-tac-toe game logic that runs over an AntelopeIO blockchain network. This version was conceived to runs over a single node, that means the players needs execute operation in the same network node.

## Game Logic

The game is played by two players, the first one is the host, who starts the game, and the secont is the challenger. The game board has nine squares, and each player takes a turn to place their marker in a square. A player wins the game when three markers are placed in a row.

In the example below the player who placed `X` has won.

|     |  0  |  1  |  2  |
|-----|-----|-----|-----|
|  0  |     |  O  |  X  |
|  1  |     |  X  |     |
|  2  |  X  |  O  |  O  |

When all the squares contain a marker and no player has three markers in a row, then the game is a draw.

## Install Development Environment

All commands described in this document is based in a custom development environment that use a virtual machine with the `Ubuntu 22.04 LTS`. To install this development environment follow the steps bellow: 

> You alternatively can follow the [official documentation](https://docs.antelope.io/docs/latest/getting-started/development-environment/prerequisites) to install it.

1. Update and upgrade the system;

```sh
sudo apt update && sudo apt -y upgrade
```

2. Download the installation script and set execution permition to.

```sh
cd
wget https://gist.githubusercontent.com/gsdenys/0d1ba76c4550c2d24b0106f5ec3fb8dd/raw/472f42955305a903918e7f3901e70f8998b2be89/antelope_dev_environment.sh
chmod +x antelope_dev_environment.sh
```

3. Execute the installation script. Certify yourself to execute it at the user home.

```sh
./antelope_dev_environment.sh
```

## Configure

Before compile and run this smart contract you need to:

1. Create a wallet;
2. Create key pairs to the smart contract, to player 1, and to player 2;
3. Create the account to smart contract, to player 1, and to player 2;
4. Import the account private key to the wallet;

To help do this job the `configure.sh` script was created. Execute it using the command bellow, that pass respectively the name of wallet, game, player 1, and player 2.

```sh
./configure.sh local tictactoe host challenger
```
## Build and install

Follow this sequence to build and install the code:

1. Create the build dir

```sh
mkdir build && cd build
```

2. Build the Smart Contract. This command will create the `.wasm` and `.abi` inside the `build/bin` dir.

```sh
cmake .. && make
```

## Install Game to the Node

The first thing to do is to grant that the wallet created for the game is `unlocked`. You can perform the command bellow and unlock it in case of it is lock.

> For this example the wallet name is `local`.

```sh
cleos wallet unlock -n local --password $(cat .tokens/local.wallet)
```

so, navigate to `${project_home}/build/bin` and then execute the command bellow.
 
```sh
cleos set contract tictactoe ./ tictactoe.wasm tictactoe.abi -p tictactoe@active
```

Now the smart contract is installed in your node.

## Play Game

Now that the smart contract has been successfully deployed push smart contract actions to the blockchain to play the game. Note that the wallet should be `unlocked` before play the game.

### Create Game

Sign the push action with host@active, the host of the game:

```sh
cleos push action tictactoe create '{"challenger":"challenger", "host":"host"}' --permission host@active
```

### Making Game Moves

The host makes the first move. The required payload in json format is:

```sh
cleos push action tictactoe move '{"challenger":"challenger", "host":"host", "by":"host", "row":0, "column":1}' --permission host@active
```

Then the challenger makes the second move. The required payload in json format is:

```sh
cleos push action tictactoe move '{"challenger":"challenger", "host":"host", "by":"challenger", "row":1, "column":1}' --permission challenger@active
```

Continue to make moves until the game ends with a win or a draw.

### Check Game Status

Look at the data in the multi index table to check the game status.

```sh
cleos get table tictactoe host games
```

### Restart the Game

Sign the push action with host@active - the host of the game.

```sh
cleos push action tictactoe restart '{"challenger":"challenger", "host":"host", "by":"host"}' --permission host@active
```

### Close the Game

Sign the push action with ‘host@active’ - the host of the game.

```sh
cleos push action tictactoe close '{"challenger":"challenger", "host":"host"}' --permission host@active
```

## MIT License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

2. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
