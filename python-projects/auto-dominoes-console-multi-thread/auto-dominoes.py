'''
Auto Dominoes Multithreading Example
--------------------------------
Author: Thomas Hoerger
Copyright: Thomas Hoerger - Copyright © 2025 Auto Dominoes Multithreading Example
Date: 10/20/2024

Description:
This program demonstrates the use of multithreading and synchronization in Python
through a console-based Dominoes game simulation.

Each player runs in a separate thread, taking turns to place domino pieces
onto a shared game table managed by synchronized thread-safe classes.
Locks are used to prevent race conditions during shared data access
(such as the game table and remaining pieces pool).

Key Concepts Demonstrated:
- Thread creation and synchronization using the threading module
- Safe concurrent access with threading.Lock
- Turn-based coordination between multiple threads
- Game logic control with automatic piece flipping and win/draw detection
- Clean console visualization of multithreaded activity
'''

import random
import threading
import time

# Class representing a player in the dominoes game
class CPlayer:
    def __init__(self):
        self.playerPieces = []  # List of domino pieces the player holds
        self.lock = threading.Lock()  # Lock for thread-safe operations

    def givePieces(self, pieces):
        with self.lock:
            self.playerPieces = pieces

    def display_hand(self):
        with self.lock:
            return " ".join(f"[{p[0]}|{p[1]}]" for p in self.playerPieces)

    def hasPieces(self):
        with self.lock:
            return bool(self.playerPieces)

    def drawPiece(self, piece):
        with self.lock:
            self.playerPieces.append(piece)

    # Attempt to place a matching piece on the table
    def placePiece(self, head, tail):
        with self.lock:
            for piece in self.playerPieces:
                a, b = piece
                # Match at the head side
                if head is not None and (a == head or b == head):
                    self.playerPieces.remove(piece)
                    # Flip if needed so the connection aligns correctly
                    if b == head:
                        return (a, b, "head")
                    else:
                        return (b, a, "head")
                # Match at the tail side
                if tail is not None and (a == tail or b == tail):
                    self.playerPieces.remove(piece)
                    # Flip if needed so the connection aligns correctly
                    if a == tail:
                        return (a, b, "tail")
                    else:
                        return (b, a, "tail")
            raise ValueError("No matching piece found.")

class CDominoes:
    def __init__(self):
        self.dominoes = []
        self.createDominoes()

    def createDominoes(self):
        for i in range(7):
            for j in range(i, 7):
                self.dominoes.append((i, j))

    def getDominoes(self):
        return self.dominoes

class CRandom:
    @staticmethod
    def mix(dominoes):
        random.shuffle(dominoes)

class CTable:
    def __init__(self):
        self.lock = threading.Lock()

    def display_table(self, table_pieces):
        # Display the current state of the dominoes table in ASCII format.
        with self.lock:
            if not table_pieces:
                print("Table is empty.")
                return
            table_display = " ".join(f"[{p[0]}|{p[1]}]" for p in table_pieces)
            print(f"Current Table: {table_display}")

class GameState:
    def __init__(self):
        self.lock = threading.Lock()
        self.currentPlayer = 0
        self.table = []
        self.remainingPieces = []
        self.gameEnded = False
        self.bothPlayersPassed = False

    def switchTurns(self):
        with self.lock:
            self.currentPlayer = (self.currentPlayer + 1) % 2

    def getCurrentPlayer(self):
        with self.lock:
            return self.currentPlayer

    def checkGameEnded(self):
        with self.lock:
            return self.gameEnded

    def endGame(self):
        with self.lock:
            self.gameEnded = True

    # Add a domino piece to the correct side of the table (head or tail)
    def addPieceToTable(self, piece, side=None):
        with self.lock:
            if not self.table:
                self.table.append(piece)
            elif side == "head":
                self.table.insert(0, (piece[0], piece[1]))
            elif side == "tail":
                self.table.append((piece[0], piece[1]))
            else:
                self.table.append(piece)

    def getTable(self):
        with self.lock:
            return list(self.table)

    def setRemainedPieces(self, pieces):
        with self.lock:
            self.remainingPieces = pieces

    def getRemainedPieces(self):
        with self.lock:
            return self.remainingPieces

    def passTurn(self):
        with self.lock:
            self.bothPlayersPassed = True

    def resetPassed(self):
        with self.lock:
            self.bothPlayersPassed = False


# Function representing a player's turn
def playerTurn(player, playerIndex, gameState, tableManager):
    while not gameState.checkGameEnded():
        # Wait until it's this player's turn
        if gameState.getCurrentPlayer() != playerIndex:
            time.sleep(0.1)
            continue  # Try again

        playerName = f"Player {playerIndex + 1}"
        print(f"{playerName}'s turn")
        time.sleep(1)

        try:
            table = gameState.getTable()
            if table:
                head = table[0][0]
                tail = table[-1][1]
            else:
                head = tail = None

            # Place piece and get which side it goes on
            a, b, side = player.placePiece(head, tail)
            gameState.addPieceToTable((a, b), side)
            print(f"{playerName} placed: [{a}|{b}]")
            tableManager.display_table(gameState.getTable())

            time.sleep(1)

            if not player.hasPieces():
                print(f"\n{playerName} wins!")
                gameState.endGame()
                return

            gameState.resetPassed()

        except ValueError:
            print(f"{playerName} has no matching piece to place, drawing a piece...")
            time.sleep(1)
            remainingPieces = gameState.getRemainedPieces()
            if remainingPieces:
                drawn_piece = remainingPieces.pop()
                print(f"{playerName} drew: [{drawn_piece[0]}|{drawn_piece[1]}]")
                player.drawPiece(drawn_piece)
            else:
                print(f"{playerName} has no more pieces to draw, passing turn.")
                gameState.passTurn()

        # Only one thread should handle the draw message once
        if gameState.bothPlayersPassed and not gameState.checkGameEnded():
            print("\nBoth players have passed. The game ends in a draw!")
            gameState.endGame()
            return

        gameState.switchTurns()
        print("\n" + "-" * 50 + "\n")
        time.sleep(1)


def main():
    domino_set = CDominoes()
    CRandom.mix(domino_set.getDominoes())

    all_pieces = domino_set.getDominoes()
    player1 = CPlayer()
    player2 = CPlayer()
    player1.givePieces(all_pieces[:10])
    player2.givePieces(all_pieces[10:20])
    remainingPieces = all_pieces[20:]

    gameState = GameState()
    gameState.setRemainedPieces(remainingPieces)
    tableManager = CTable()

    first_player = random.choice([0, 1])
    print(f"Player {first_player + 1} starts the game.")

    firstPlayerObj = player1 if first_player == 0 else player2
    first_piece = firstPlayerObj.playerPieces.pop(0)
    gameState.addPieceToTable(first_piece)
    tableManager.display_table(gameState.getTable())
    print("\n" + "-" * 50 + "\n")

    thread1 = threading.Thread(target=playerTurn, args=(player1, 0, gameState, tableManager))
    thread2 = threading.Thread(target=playerTurn, args=(player2, 1, gameState, tableManager))

    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()


if __name__ == "__main__":
    main()
