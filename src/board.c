
uint64_t typedef bb_t;

enum CastlingSide {
    CASTLE_SHORT,
    CASTLE_LONG,
    CASTLE_CNT,
} typedef CastlingSide;

struct Board typedef Board;
struct Board {
    bb_t pieces[COLOR_CNT][PIECE_CNT];
    bool castling[COLOR_CNT][CASTLE_CNT];
    bool ep_target;
    int  ep_target_file;
    int  ep_target_rank;
    int  move_counter;
};

const bb_t white_pawns   = 0x000000000000ff00;
const bb_t white_rooks   = 0x0000000000000081;
const bb_t white_knights = 0x0000000000000042;
const bb_t white_bishops = 0x0000000000000024;
const bb_t white_queen   = 0x0000000000000008;
const bb_t white_king    = 0x0000000000000010;
const bb_t black_pawns   = 0x00ff000000000000;
const bb_t black_rooks   = 0x8100000000000000;
const bb_t black_knights = 0x4200000000000000;
const bb_t black_bishops = 0x2400000000000000;
const bb_t black_queen   = 0x0800000000000000;
const bb_t black_king    = 0x1000000000000000;

#define FILE_A UINT64_C(0x0101010101010101)
#define FILE_B UINT64_C(0x0202020202020202)
#define FILE_C UINT64_C(0x0404040404040404)
#define FILE_D UINT64_C(0x0808080808080808)
#define FILE_E UINT64_C(0x1010101010101010)
#define FILE_F UINT64_C(0x2020202020202020)
#define FILE_G UINT64_C(0x4040404040404040)
#define FILE_H UINT64_C(0x8080808080808080)

#define RANK_1 UINT64_C(0x00000000000000ff)
#define RANK_2 UINT64_C(0x000000000000ff00)
#define RANK_3 UINT64_C(0x0000000000ff0000)
#define RANK_4 UINT64_C(0x00000000ff000000)
#define RANK_5 UINT64_C(0x000000ff00000000)
#define RANK_6 UINT64_C(0x0000ff0000000000)
#define RANK_7 UINT64_C(0x00ff000000000000)
#define RANK_8 UINT64_C(0xff00000000000000)

#define SQ_A1 (FILE_A & RANK_1)
#define SQ_A2 (FILE_A & RANK_2)
#define SQ_A3 (FILE_A & RANK_3)
#define SQ_A4 (FILE_A & RANK_4)
#define SQ_A5 (FILE_A & RANK_5)
#define SQ_A6 (FILE_A & RANK_6)
#define SQ_A7 (FILE_A & RANK_7)
#define SQ_A8 (FILE_A & RANK_8)
#define SQ_B1 (FILE_B & RANK_1)
#define SQ_B2 (FILE_B & RANK_2)
#define SQ_B3 (FILE_B & RANK_3)
#define SQ_B4 (FILE_B & RANK_4)
#define SQ_B5 (FILE_B & RANK_5)
#define SQ_B6 (FILE_B & RANK_6)
#define SQ_B7 (FILE_B & RANK_7)
#define SQ_B8 (FILE_B & RANK_8)
#define SQ_C1 (FILE_C & RANK_1)
#define SQ_C2 (FILE_C & RANK_2)
#define SQ_C3 (FILE_C & RANK_3)
#define SQ_C4 (FILE_C & RANK_4)
#define SQ_C5 (FILE_C & RANK_5)
#define SQ_C6 (FILE_C & RANK_6)
#define SQ_C7 (FILE_C & RANK_7)
#define SQ_C8 (FILE_C & RANK_8)
#define SQ_D1 (FILE_D & RANK_1)
#define SQ_D2 (FILE_D & RANK_2)
#define SQ_D3 (FILE_D & RANK_3)
#define SQ_D4 (FILE_D & RANK_4)
#define SQ_D5 (FILE_D & RANK_5)
#define SQ_D6 (FILE_D & RANK_6)
#define SQ_D7 (FILE_D & RANK_7)
#define SQ_D8 (FILE_D & RANK_8)
#define SQ_E1 (FILE_E & RANK_1)
#define SQ_E2 (FILE_E & RANK_2)
#define SQ_E3 (FILE_E & RANK_3)
#define SQ_E4 (FILE_E & RANK_4)
#define SQ_E5 (FILE_E & RANK_5)
#define SQ_E6 (FILE_E & RANK_6)
#define SQ_E7 (FILE_E & RANK_7)
#define SQ_E8 (FILE_E & RANK_8)
#define SQ_F1 (FILE_F & RANK_1)
#define SQ_F2 (FILE_F & RANK_2)
#define SQ_F3 (FILE_F & RANK_3)
#define SQ_F4 (FILE_F & RANK_4)
#define SQ_F5 (FILE_F & RANK_5)
#define SQ_F6 (FILE_F & RANK_6)
#define SQ_F7 (FILE_F & RANK_7)
#define SQ_F8 (FILE_F & RANK_8)

static int bb_first_bit(bb_t bb) {
    return (int)_mm_tzcnt_64(bb);
}

static int bb_last_bit(bb_t bb) {
    return (int)__lzcnt64(bb);
}

static void board_default(Board *board) {
    board->pieces[COLOR_WHITE][PIECE_P] = white_pawns;
    board->pieces[COLOR_WHITE][PIECE_N] = white_knights;
    board->pieces[COLOR_WHITE][PIECE_B] = white_bishops;
    board->pieces[COLOR_WHITE][PIECE_R] = white_rooks;
    board->pieces[COLOR_WHITE][PIECE_Q] = white_queen;
    board->pieces[COLOR_WHITE][PIECE_K] = white_king;
    board->pieces[COLOR_BLACK][PIECE_P] = black_pawns;
    board->pieces[COLOR_BLACK][PIECE_N] = black_knights;
    board->pieces[COLOR_BLACK][PIECE_B] = black_bishops;
    board->pieces[COLOR_BLACK][PIECE_R] = black_rooks;
    board->pieces[COLOR_BLACK][PIECE_Q] = black_queen;
    board->pieces[COLOR_BLACK][PIECE_K] = black_king;
    board->castling[COLOR_WHITE][CASTLE_SHORT] = true;
    board->castling[COLOR_WHITE][CASTLE_LONG]  = true;
    board->castling[COLOR_BLACK][CASTLE_SHORT] = true;
    board->castling[COLOR_BLACK][CASTLE_LONG]  = true;
    board->ep_target = false;
    board->move_counter = 0;
}

static bb_t board_pieces(Board *board, int color) {
    bb_t result = 0;
    for(int piece = 0; piece != PIECE_CNT; ++piece) {
        result |= board->pieces[color][piece];
    }
    return result;
}

static bb_t board_all_pieces(Board *board) {
    bb_t white_pieces = board_pieces(board, COLOR_WHITE);
    bb_t black_pieces = board_pieces(board, COLOR_BLACK);
    return white_pieces | black_pieces;
}

static bb_t valid_moves(Board *board, bb_t loc, int piece, int color) {
    if(piece == PIECE_K) {
        // The spots for king go like this:
        //  1 2 3
        //  4 K 5
        //  6 7 8
        // for going left and right we exclude locations of king
        // that are on files A and H
        bb_t loc_clip_a = loc & ~FILE_A;
        bb_t loc_clip_h = loc & ~FILE_H;
        bb_t spot_1 = loc_clip_a << 7;
        bb_t spot_2 = loc        << 8;
        bb_t spot_3 = loc_clip_h << 9;
        bb_t spot_4 = loc_clip_a >> 1;
        bb_t spot_5 = loc_clip_h << 1;
        bb_t spot_6 = loc_clip_a >> 9;
        bb_t spot_7 = loc        >> 8;
        bb_t spot_8 = loc_clip_h >> 9;
        // Find the mask for all the king moves
        bb_t all_moves = spot_1 | spot_2 | spot_3 | spot_4
                       | spot_5 | spot_6 | spot_7 | spot_8;
        // No self capture
        bb_t valid_moves = all_moves & ~board_pieces(board, color);
        return valid_moves;
    }
    else if(piece == PIECE_N) {
        // The spots for the knight go like this:
        // . 1 . 2 .
        // 3 . . . 4
        // . . N . .
        // 5 . . . 6
        // . 7 . 8 .
        // For the spots 1,7 knight can't be on A file
        // For the spots 2,8 knight can't be on H file
        // For the spots 3,5 knight can't be on A and B files
        // For the spots 4,6 knight can't be on G and H files
        bb_t loc_clip_a  = loc & ~FILE_A;
        bb_t loc_clip_h  = loc & ~FILE_H;
        bb_t loc_clip_ab = loc & ~(FILE_A | FILE_B);
        bb_t loc_clip_gh = loc & ~(FILE_G | FILE_H);
        // Compute spots
        bb_t spot_1 = loc_clip_a  << 15;
        bb_t spot_2 = loc_clip_h  << 17;
        bb_t spot_3 = loc_clip_ab << 6;
        bb_t spot_4 = loc_clip_gh << 10;
        bb_t spot_5 = loc_clip_ab >> 10;
        bb_t spot_6 = loc_clip_gh >> 6;
        bb_t spot_7 = loc_clip_a  >> 17;
        bb_t spot_8 = loc_clip_h  >> 15;
        // Find all moves theorhetically possible by knight
        bb_t all_moves = spot_1 | spot_2 | spot_3 | spot_4
                       | spot_5 | spot_6 | spot_7 | spot_8;
        // No self capture
        bb_t valid_moves = all_moves & ~board_pieces(board, color);
        return valid_moves;
    }
    else if(piece == PIECE_P) {
        bb_t all_pieces = board_all_pieces(board);
        if(color == COLOR_WHITE) {
            bb_t black_pieces = board_pieces(board, COLOR_BLACK);
            // for now just the white pawns
            // One step above move
            bb_t step1 = (loc << 8);
            // For one-square steps from rank 2 (that end up at rank 3) we
            // compute two-square steps
            bb_t step2 = (step1 & RANK_3);
            bb_t valid_moves = (step1 | step2) & ~all_pieces;
            // Now compute valid captures
            bb_t atk_l = (loc & ~FILE_A) << 7;
            bb_t atk_r = (loc & ~FILE_H) << 9;
            bb_t valid_attacks = (atk_l | atk_r) & black_pieces;
            return valid_moves | valid_attacks;
        }
        else {
            bb_t white_pieces = board_pieces(board, COLOR_WHITE);
            // for now just the white pawns
            // One step above move
            bb_t step1 = (loc >> 8);
            // For one-square steps from rank 2 (that end up at rank 3) we
            // compute two-square steps
            bb_t step2 = (step1 & RANK_3);
            bb_t valid_moves = (step1 | step2) & ~all_pieces;
            // Now compute valid captures
            bb_t atk_l = (loc & ~FILE_A) >> 9;
            bb_t atk_r = (loc & ~FILE_H) >> 7;
            bb_t valid_attacks = (atk_l | atk_r) & white_pieces;
            return valid_moves | valid_attacks;
        }
    }
    return 0;
}