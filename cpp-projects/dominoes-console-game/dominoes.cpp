// Thomas Hoerger - Copyright © 2024 Dominoes Console Game
// ----------------------------------------------------
// Object-Oriented Dominoes Game
// Features:
// 1. Two players, human vs computer
// 2. 28 domino pieces
// 3. 10 pieces dealt to each player
// 4. Remaining 8 pieces as boneyard for drawing
// 5. Players take turns playing on head or tail of table
// 6. Game ends when one player runs out of pieces

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

// Class to shuffle and randomize any vector
class CRandom {
public:
    template <typename T>
    static void Shuffle(vector<T>& vec) {
        // Random device and Mersenne Twister generator
        random_device rd;
        mt19937 g(rd());
        // Use STL shuffle with the generator
        shuffle(vec.begin(), vec.end(), g);
    }
};

// Class to manage domino pieces
class CDominoes {
    vector<pair<int,int>> pieces; // Stores all domino pieces
public:
    // Constructor initializes all 28 dominoes
    CDominoes() {
        for(int i=0;i<=6;i++)
            for(int j=i;j<=6;j++)
                pieces.push_back({i,j});
    }

    // Shuffle the domino pieces
    void ShufflePieces() { CRandom::Shuffle(pieces); }

    // Get initial pieces for a player (removes from main set)
    vector<pair<int,int>> GetInitialPieces(int count) {
        vector<pair<int,int>> hand;
        for(int i=0;i<count;i++){
            hand.push_back(pieces.back());
            pieces.pop_back();
        }
        return hand;
    }

    // Check if there are any pieces left in boneyard
    bool AreAvailablePieces() { return !pieces.empty(); }

    // Draw a single piece from remaining pieces
    pair<int,int> DrawPiece() {
        if(pieces.empty()) throw runtime_error("No more pieces to draw.");
        pair<int,int> p = pieces.back();
        pieces.pop_back();
        return p;
    }
};

// Class to manage the table (played pieces)
class CTable {
public:
    vector<pair<int,int>> placedPieces; // Pieces on the table
    int head=-1, tail=-1; // Values at the ends of the table

    // Place a piece on head or tail
    void PlacePiece(pair<int,int> p, bool toHead) {
        if(placedPieces.empty()) {
            // First piece sets head and tail
            placedPieces.push_back(p);
            head = p.first;
            tail = p.second;
            return;
        }

        if(toHead) {
            // Ensure the piece connects to head
            if(p.second != head) swap(p.first, p.second);
            placedPieces.insert(placedPieces.begin(), p);
            head = p.first;
        } else {
            // Ensure the piece connects to tail
            if(p.first != tail) swap(p.first, p.second);
            placedPieces.push_back(p);
            tail = p.second;
        }
    }

    // Display current table pieces
    void DisplayTable() {
        cout << "Table: ";
        for(size_t i=0;i<placedPieces.size();i++){
            cout << "[" << placedPieces[i].first << "|" << placedPieces[i].second << "] ";
            if((i+1)%8==0) cout << "\n       "; // Wrap after 8 pieces for readability
        }
        cout << endl;
    }
};

// Class to manage a player's hand
class CPlayer {
public:
    vector<pair<int,int>> hand; // Player's domino pieces
    bool isUser=false; // Is human player
    CPlayer(vector<pair<int,int>> initHand,bool user=false):hand(initHand),isUser(user){}

    // Check if player has any playable pieces
    bool CanPlay(int head,int tail){
        if(head==-1 || tail==-1) return true; // Can always play first piece
        for(auto &p:hand)
            if(p.first==head || p.second==head || p.first==tail || p.second==tail)
                return true;
        return false;
    }

    // Play a piece, human or computer
    pair<int,int> PlayPiece(int head,int tail,bool &toHead){
        if(isUser){
            while(true){
                // Display user's hand
                cout << "Your hand: ";
                for(size_t i=0;i<hand.size();i++)
                    cout << i+1 << ":[" << hand[i].first << "|" << hand[i].second << "] ";
                
                // Ask which piece to play
                cout << "\nEnter the number of the piece to play: ";
                int choice; cin >> choice;

                // Validate input
                if(choice<1 || choice>(int)hand.size()){
                    cout << "Invalid choice. Pick again.\n\n";
                    continue;
                }

                pair<int,int> p=hand[choice-1];
                bool canPlayHead=false, canPlayTail=false;

                // Determine if piece can be played on head/tail
                if(head==-1 && tail==-1){
                    canPlayHead=true; // first move
                    canPlayTail=false;
                } else {
                    if(p.first==head || p.second==head) canPlayHead=true;
                    if(p.first==tail || p.second==tail) canPlayTail=true;
                }

                if(!canPlayHead && !canPlayTail){
                    cout << "Piece cannot be played on current head or tail. Pick again.\n\n";
                    continue;
                }

                // Decide where to play
                if(canPlayHead && !canPlayTail) toHead=true;
                else if(!canPlayHead && canPlayTail) toHead=false;
                else {
                    char pos;
                    while(true){
                        cout << "Play on head (h) or tail (t)? ";
                        cin >> pos;
                        pos=tolower(pos);
                        if(pos=='h' && canPlayHead){ toHead=true; break; }
                        else if(pos=='t' && canPlayTail){ toHead=false; break; }
                        else cout << "Cannot play on that side. Choose again.\n";
                    }
                }

                // Remove piece from hand and return it
                hand.erase(hand.begin()+choice-1);
                return p;
            }
        } else {
            // AI Logic Explanation:
            bool hasMove=false;
            // Step 1: Check if AI has any playable pieces
            for(auto &p:hand){
                if(head==-1 || tail==-1 || p.first==head || p.second==head || p.first==tail || p.second==tail){
                    hasMove=true; // Found at least one playable piece
                    break;
                }
            }
            if(!hasMove) return {-1,-1}; // No move possible

            // Step 2: Iterate through AI hand to select a piece
            for(size_t i=0;i<hand.size();i++){
                pair<int,int> p=hand[i];

                // If table is empty, just play first piece
                if(head==-1 || tail==-1){ 
                    hand.erase(hand.begin()+i); 
                    toHead=false; 
                    return p; 
                }

                // Prefer playing on tail if matches
                if(p.first==tail || p.second==tail){ 
                    hand.erase(hand.begin()+i); 
                    toHead=false; // Place at tail
                    return p; 
                }

                // Else play on head if matches
                if(p.first==head || p.second==head){ 
                    hand.erase(hand.begin()+i); 
                    toHead=true; // Place at head
                    return p; 
                }
            }

            // Fallback, should not reach here
            return {-1,-1};
        }
    }

    // Add a drawn piece to hand
    void Draw(pair<int,int> p){ hand.push_back(p); }

    // Check if player still has pieces
    bool HasPieces(){ return !hand.empty(); }
};

// Helper function to check if game is over
bool CheckWinner(CPlayer &p1, CPlayer &p2){
    if(!p1.HasPieces() || !p2.HasPieces()) return true;
    return false;
}

int main(){
    srand((unsigned)time(nullptr));
    char input;
    do{
        system("cls||clear"); // Clear screen for new game
        CDominoes dominoes;
        dominoes.ShufflePieces();
        CPlayer player1(dominoes.GetInitialPieces(10),true); // Human
        CPlayer player2(dominoes.GetInitialPieces(10)); // AI
        vector<pair<int,int>> remaining = dominoes.GetInitialPieces(8); // Boneyard
        CTable table;

        // Randomly select starting player
        int current=(rand()%2==0)?1:2;
        cout << "Player " << current << " goes first!\n\n";
        this_thread::sleep_for(chrono::milliseconds(800));

        while(true){
            CPlayer *p=(current==1)?&player1:&player2;
            bool toHead=false;

            // Keep drawing until a playable piece is found
            while(!p->CanPlay(table.head,table.tail) && !remaining.empty()){
                pair<int,int> draw=remaining.back();
                remaining.pop_back();
                p->Draw(draw);
                if(p->isUser) cout << "No piece to play you draw a piece.\n\n";
                else cout << "Player " << current << " has no piece to play they draw a piece.\n\n";
                this_thread::sleep_for(chrono::milliseconds(800));
            }

            // Play a piece if possible
            if(p->CanPlay(table.head,table.tail)){
                pair<int,int> move = p->PlayPiece(table.head,table.tail,toHead);
                table.PlacePiece(move,toHead);
                if(p->isUser) cout << endl;
                else cout << "Player " << current << " plays [" << move.first << "|" << move.second << "]\n\n";
                table.DisplayTable();
                cout << endl;
                this_thread::sleep_for(chrono::milliseconds(800));
            } else {
                cout << "Player " << current << " cannot play.\n\n";
                this_thread::sleep_for(chrono::milliseconds(800));
            }

            if(CheckWinner(player1,player2)) break; // Game over
            current=(current==1)?2:1; // Switch turn
        }

        // Display winner and remaining pieces
        cout << endl;
        if(!player1.HasPieces()){
            cout << "Player 1 wins!\n\n";
            cout << "Player 2 has " << player2.hand.size() << " piece" << (player2.hand.size()==1?"":"s") << " left: ";
            for(auto &p:player2.hand) cout << "[" << p.first << "|" << p.second << "] ";
        } else {
            cout << "Player 2 wins!\n\n";
            cout << "Player 1 has " << player1.hand.size() << " piece" << (player1.hand.size()==1?"":"s") << " left: ";
            for(auto &p:player1.hand) cout << "[" << p.first << "|" << p.second << "] ";
        }

        cout << "\n\nFinal table:\n";
        table.DisplayTable();

        // Ask for restart or quit
        cout << "\nType 'r' to restart the game or 'q' to quit: ";
        cin >> input;

    } while(input=='r');

    cout << "\nThanks for playing! Goodbye.";
    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}