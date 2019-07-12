string getLCS(string str1, string str2){
    vector<vector<int> > record(str1.length(), vector<int> (str2.length()));
    int maxLen = 0, maxEnd = 0;
    for(int i = 0; i < static_cast<int>(str1.length()); i++){
        for(int j = 0; j < static_cast<int>(str2.length()); j++){
            if(str1[i] == str2[j]){
                if(i == 0 || j == 0){
                    record[i][j] = 1;
                }else{
                    record[i][j] = record[i - 1][j - 1] + 1;
                }
            }else{
                record[i][j] = 0;
            }

            if(record[i][j] > maxLen){
                maxLen = record[i][j];
                maxEnd = i;
            }
        }
    }
    return str1.substr(maxEnd - maxLen + 1, maxLen);
}