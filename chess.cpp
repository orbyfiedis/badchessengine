/*
 * By orbyfied (2023)
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "chess.h"

#include "util.h"

#include <cstdlib>
#include <cstdio>

/* positions */

// get the positions in different directions //
inline Pos Board::mov_pos_offset(Pos src,
                                 unsigned int offX,
                                 unsigned int offY) {
    return { src.packed + offX + (WIDTH * offY) };
}

// get the positions diagonally //
inline Pos Board::mov_pos_diag_tr(Pos src,
                                    unsigned int off) {
    return { src.packed + off + (WIDTH * off) };
}

inline Pos Board::mov_pos_diag_br(Pos src,
                                    unsigned int off) {
    return { src.packed + off - (WIDTH * off) };
}

inline Pos Board::mov_pos_diag_tl(Pos src,
                                    unsigned int off) {
    return { src.packed - off + (WIDTH * off) };
}

inline Pos Board::mov_pos_diag_bl(Pos src,
                                    unsigned int off) {
    return { src.packed - off - (WIDTH * off) };
}

// get the positions on a straight line //

inline Pos Board::mov_pos_h(Pos src,
                              unsigned int off) {
    return { src.packed + off };
}

inline Pos Board::mov_pos_v(Pos src,
                              unsigned int off) {
    return { src.packed + (WIDTH * off) };
}

// cap offsets to a bound //

inline unsigned int Board::cap_offset_h(Pos src,
                                        unsigned int off) {
    unsigned short col = src.vec.x % WIDTH;
    return cap(0, col + off, WIDTH);
}

inline unsigned int Board::cap_offset_v(Pos src,
                                        unsigned int off) {
    unsigned short row = src.vec.y % HEIGHT;
    return cap(0, row + off, HEIGHT);
}

/* pieces */
PieceDescriptor *Board::get_piece(Pos pos) {
    if (pos.packed >= SIZE || pos.packed < 0)
        return nullptr;
    return get_piece_unchecked(pos);
}

inline PieceDescriptor *Board::get_piece_unchecked(Pos pos) {
    return _data + pos.packed;
}

/* moves */
void Board::make_move_unchecked(Move *move) {
    // get positions
    const Pos src = move->src_pos;
    const Pos dst = move->dest_pos;

    // get current piece
    PieceDescriptor *src_piece = get_piece_unchecked(src);

    // check capture
    PieceDescriptor *dest_piece = get_piece_unchecked(dst);
    if (dest_piece != nullptr) {
        move->r_captured = *dest_piece;
    }

    // set current to null
    // and move piece
    PieceDescriptor srcP = *src_piece;
    _data[src.packed] = NO_PIECE;
    *dest_piece = srcP;
}

/* configuration */

inline char snext(const char *str, int *i) {
    if (str[*i] == NULL) return NULL;
    return str[++(*i)];
}

inline char snext(const char *str, int *i, int amt) {
    for (; amt > 0; amt--)
        snext(str, i);
    return snext(str, i);
}

int Board::load_fen(char* str) {
    if (!str)
        return -1;

    Pos pos = { .vec = { 0, 7 } };

    // record piece placement field
    int i = 0;
    char c = str[0];
    for (; c != NULL && c != ' '; c = str[i++]) {
        // check for special characters
        if (c == '/') {
            // advance position
            pos.vec.y -= 1;
            pos.vec.x = 0;
            continue;
        }

        // check for h skips
        if (isnumeric10(c)) {
            int skip = tonumeric10(c);
            pos.vec.x += skip > WIDTH ? WIDTH : skip;
            continue;
        }

        // check color
        PieceColor color = isupper(c) ? C_WHITE : C_BLACK;
        // get type
        PieceType type;
        switch (tolower(c)) {
            case 'p': type = P_PAWN; break;
            case 'n': type = P_KNIGHT; break;
            case 'b': type = P_BISHOP; break;
            case 'r': type = P_ROOK; break;
            case 'q': type = P_QUEEN; break;
            case 'k': type = P_KING; break;
            default:
                dlog(P, "fen: unknown piece char %c", c);
                return -EFENNOPIECE;
        }

        // create and store descriptor
        PieceDescriptor descriptor = {.data = {
                        .type = type,
                        .color = color
                }};

        *get_piece_unchecked(pos) = descriptor;
    }

    c = snext(str, &i);
    if (c == NULL) return 0;

    // parse current turn
    _turn = (c == 'b' ? C_BLACK : C_WHITE);

    if ((c = snext(str, &i, 2)) == NULL) return 0;

    // parse castle states
    for (; c != NULL && c != ' '; c = str[i++]) {
        PieceColor color = isupper(c) ? C_WHITE : C_BLACK;
        int mask = tolower(c) == 'k' ? S_KING : S_QUEEN;
        if (color == C_WHITE) _castle_ability.white |= mask;
        else _castle_ability.black |= mask;
    }

    // TODO: load en passant, ply move count since pawn event, full move count
    //  https://nl.wikipedia.org/wiki/Forsyth-Edwards_Notation

    // return success
    return 0;
}
