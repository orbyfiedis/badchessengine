/*
 * By orbyfied (2023)
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#ifndef BADCHESSENGINE_CHESS_H
#define BADCHESSENGINE_CHESS_H

#include "util.h"

/// @brief The type of a chess piece, including pawns.
enum PieceType {
    P_PAWN = 0,

    P_KNIGHT = 1,
    P_BISHOP = 2,
    P_ROOK   = 3,
    P_QUEEN  = 4,
    P_KING   = 5
};

/// @brief The color of a piece.
enum PieceColor {
    C_NONE  = 0,
    C_WHITE = 1,
    C_BLACK = 2
};

/// @brief Represents a 2D position on the board.
typedef union {
    // the packed data
    unsigned int packed;
    // the vector
    struct {
        unsigned short x : 3;
        unsigned short y : 3;
    } __attribute__((packed)) vec;
} Pos;

/// @brief The data used to describe a piece.
/// A union is used to represent a piece
/// on a board. The union has a size of 2 bytes
/// (short) and contains all data required in
/// bit fields.
typedef union {
    // the packed data
    unsigned short packed;

    // the unpacked accessible data
    struct {
        PieceType  type  : 3;
        PieceColor color : 2;
    } __attribute__((packed)) data;
} PieceDescriptor;

/// No piece.
constexpr PieceDescriptor NO_PIECE = { 0 };

/// @brief A move on the board.
typedef struct {
    // the source position
    Pos src_pos;
    // the destination position
    Pos dest_pos;

    /* data only available after it having been made
     * prefixed with r_ to indicate result */
    PieceDescriptor r_captured; // the piece captured
} Move;

/// To which side one can castle.
enum CastleSide {
    S_KING,
    S_QUEEN
};

// FEN //
#define EFENNOPIECE 2

/// @brief The chess board.
///
/// Positioning:
/// +---------------+
/// |0,1         1,1|
/// |               |
/// |               |
/// |0,0         1,0|
/// +---------------+
class Board {
private:
    // the board data
    PieceDescriptor* _data;

    // if either side can castle
    struct {
        int white;
        int black;
    } _castle_ability;

    // the current turn
    PieceColor _turn;

    // the total number of moves and ply moves played
    // a ply move is a half move and is just one move
    // played by either side, a full move is a duo of
    // moves played by both sides
    unsigned int _tot_ply_moves  = 0;
    unsigned int _tot_moves      = 0;
public:
    // the width and height of the board
    static constexpr unsigned int WIDTH  = 8;
    static constexpr unsigned int HEIGHT = 8;
    static constexpr unsigned int SIZE   = WIDTH * HEIGHT; // 1d size

    /* positions */
    // get the positions in different directions
    static inline Pos mov_pos_offset(Pos src,
                                       unsigned int offX,
                                       unsigned int offY);
    // get the positions diagonally
    static inline Pos mov_pos_diag_tr(Pos src,
                                        unsigned int off);
    static inline Pos mov_pos_diag_br(Pos src,
                                        unsigned int off);
    static inline Pos mov_pos_diag_tl(Pos src,
                                        unsigned int off);
    static inline Pos mov_pos_diag_bl(Pos src,
                                        unsigned int off);

    // get the positions on a straight line
    static inline Pos mov_pos_h(Pos src,
                                  unsigned int off);
    static inline Pos mov_pos_v(Pos src,
                                  unsigned int off);

    // cap offsets to a bound
    static inline unsigned int cap_offset_h(Pos src,
                                            unsigned int off);
    static inline unsigned int cap_offset_v(Pos src,
                                            unsigned int off);

    /* pieces */
    PieceDescriptor *get_piece(Pos pos);
    inline PieceDescriptor *get_piece_unchecked(Pos pos);

    /* moves */
    void make_move_unchecked(Move *move);

    /* configuration */
    /// @brief Load a FEN string into this board.
    int load_fen(char* str);
};

#endif //BADCHESSENGINE_CHESS_H
