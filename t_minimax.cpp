/**
 * 极大极小算法 - 负极大值算法
 * 仅做参考
 */
int negamax(GameState S, int depth, int alpha, int beta) {
    // 游戏是否结束 || 探索的递归深度是否到边界
    if ( gameover(S) || depth == 0 ) {
        return evaluation(S);
    }
    // 遍历每一个候选步
    foreach ( move in candidate list ) {
        S' = makemove(S);
        value = -negamax(S', depth - 1, -beta, -alpha);
        unmakemove(S')
        if ( value > alpha ) {
            // alpha + beta剪枝点
            if ( value >= beta ) {
                return beta;
            }
            alpha = value;
        }
    }
    return alpha;
}
