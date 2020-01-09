/*
 * 将矩阵保存在一个 vector<vector<char>> 中
 * 矩阵可选部分用字符 1 保存，不可选部分用 0 保存
 */
int maximalRectangle(vector<vector<char>> &matrix) {
    if (matrix.empty() || matrix[0].empty())
        return 0;
    int row = matrix.size();
    int col = matrix[0].size();
    int maxArea = 0;
    vector<int> height(col + 1, 0);
    for (int i = 0; i < row; ++i) {
        stack<int> stack;
        for (int j = 0; j < col + 1; ++j) {
            if (j < col)
                height[j] = (matrix[i][j] - '0') == 0 ? 0 : height[j] + 1; //得到 height 数组
            if (stack.empty() || height[j] >= height[stack.top()])         // 规则1
                stack.push(j);
            else {
                while (!stack.empty() && height[stack.top()] >= height[j]) { //规则2
                    int top = stack.top();
                    stack.pop();
                    int curArea = height[top] * (stack.empty() ? j : j - stack.top() - 1);
                    maxArea = maxArea > curArea ? maxArea : curArea;
                }
            }
            stack.push(j);
        }
    }
    return maxArea;
}