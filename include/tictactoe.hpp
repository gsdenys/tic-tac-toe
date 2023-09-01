/*
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include <eosio/eosio.hpp>

using namespace eosio;

/**
 * @brief The tictactoe contract handles a simple tic-tac-toe game on AntelopeIO blockchain.
 */
class [[eosio::contract("tictactoe")]] tictactoe : public contract
{
public:
    using contract::contract;

    /**
     * @brief Constructor for the tictactoe contract.
     *
     * @param receiver - The account that receives the contract.
     * @param code - The account that deploys the contract.
     * @param ds - The datastream for contract actions.
     */
    tictactoe(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {}

    // Constants for game state
    static constexpr name none = "none"_n;
    static constexpr name draw = "draw"_n;

    /**
     * @brief The game struct represents the state of a tic-tac-toe game.
     */
    struct [[eosio::table]] game
    {
        static constexpr uint16_t boardWidth = 3;
        static constexpr uint16_t boardHeight = 3;

        std::vector<uint8_t> board; ///< Represents the game board as a 3x3 grid.
        name challenger; ///< The name of the challenger player.
        name host; ///< The name of the host player.
        name turn; ///< The name of the player whose turn it is.
        name winner = none; ///< The name of the winner (if any).

        /**
         * @brief Default constructor for the game struct.
         * Initializes the board with empty cells.
         */
        game() : board(boardWidth * boardHeight, 0) {}

        /**
         * @brief Initializes the game board by clearing all cells.
         */
        void initializeBoard()
        {
            board.assign(boardWidth * boardHeight, 0);
        }

        /**
         * @brief Resets the game by clearing the board and setting the turn and winner to default values.
         */
        void resetGame()
        {
            initializeBoard();
            turn = host;
            winner = none;
        }

        /**
         * @brief Returns the primary key used for indexing game records in the table.
         * @return uint64_t - The primary key value.
         */
        auto primary_key() const { return challenger.value; }

        /**
         * @brief Serializes the game struct for storage in the EOSIO table.
         * @param ds - The datastream used for serialization.
         */
        EOSLIB_SERIALIZE(game, (challenger)(host)(turn)(winner)(board))
    };

    typedef eosio::multi_index<"games"_n, game> games; ///< Alias for the game table.

    /**
     * @brief Action to create a new tic-tac-toe game.
     * @param challenger - The name of the challenger player.
     * @param host - The name of the host player.
     */
    [[eosio::action]] void create(const name &challenger, name &host);

    /**
     * @brief Action to restart a tic-tac-toe game.
     * @param challenger - The name of the challenger player.
     * @param host - The name of the host player.
     * @param by - The name of the player initiating the restart.
     */
    [[eosio::action]] void restart(const name &challenger, const name &host, const name &by);

    /**
     * @brief Action to close and end a tic-tac-toe game.
     * @param challenger - The name of the challenger player.
     * @param host - The name of the host player.
     */
    [[eosio::action]] void close(const name &challenger, const name &host);

    /**
     * @brief Action to make a move in the tic-tac-toe game.
     * @param challenger - The name of the challenger player.
     * @param host - The name of the host player.
     * @param by - The name of the player making the move.
     * @param row - The row of the cell to mark.
     * @param column - The column of the cell to mark.
     */
    [[eosio::action]] void move(const name &challenger, const name &host, const name &by, const uint16_t &row, const uint16_t &column);

private:
    /**
     * @brief Checks if a cell on the game board is empty.
     * @param cell - The value of the cell to check.
     * @return bool - True if the cell is empty, false otherwise.
     */
    bool isEmptyCell(const uint8_t &cell);

    /**
     * @brief Validates if a move is valid on the game board.
     * @param row - The row of the cell to check.
     * @param column - The column of the cell to check.
     * @param board - The current state of the game board.
     * @return bool - True if the move is valid, false otherwise.
     */
    bool isValidMove(const uint16_t &row, const uint16_t &column, const std::vector<uint8_t> &board);

    /**
     * @brief Determines the winner of the game.
     * @param currentGame - The current game state.
     * @return name - The name of the winner or "none" if there is no winner yet.
     */
    name getWinner(const game &currentGame);
};
