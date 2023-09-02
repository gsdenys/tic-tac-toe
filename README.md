# Tic-Tac-Toe Smart Contract for AntelopeIO Blockchain

>! _This is an implementation based on [EOSIO Development Tutorials](https://developers.eos.io/welcome/v2.1/tutorials/tic-tac-toe-game-smart-contract-single-node). Navigete to the page to more details._

This smart contract contains the tic-tac-toe game logic that runs over an AntelopeIO blockchain network. This version was concebed to runs over a single node, that means the players needs execute operation in the same network node.

## Game Logic

The game is played by two players, the first one is the host, who starts the game, and the secont is the challenger. The game board has nine squares, and each player takes a turn to place their marker in a square. A player wins the game when three markers are placed in a row.

In the example below the player who placed `X` has won.

| Row |  0  |  1  |  2  |
|-----|-----|-----|-----|
|  0  |     |  O  |  X  |
|  1  |     |  X  |     |
|  2  |  X  |  O  |  O  |

When all the squares contain a marker and no player has three markers in a row, then the game is a draw.

## Install development environment

All commands described in this document is based in a custom development environment that use a virtual machine with the `Ubuntu 22.04 LTS`. To install this development environment follow the steps bellow: 

>? You alternatively can follow the [official documentation](https://docs.antelope.io/docs/latest/getting-started/development-environment/prerequisites) to install it.

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

## Run It

If you chosse the script way __go to step 2__. The develop environment is already configured to start itselt using `systemctl`, you can check it using the commands bellow.

```sh
systemctl status nodeos
systemctl status keosd
```

3. Create the folder to store the keys, users identification and tokens.

```sh
mkdir tokens
```

4. Open and unlock the wallet.

```sh
cleos wallet open
cleos wallet unlock --password $(cat ~/.wallet.pw)
```

5. Create a wallet called `local`.

```sh
cleos wallet create --name local --file .tokens/wallet.pw
```

6. 

```sh 
cleos create key | tee >(grep "Private key: " | cut -d ' ' -f 3 > private_key.txt) >(grep "Public key: " | cut -d ' ' -f 3 > public_key.txt)

```