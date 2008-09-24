
// Longest common subsequence - size
int lcs(string a, string b)
{
	mati mat(a.size()+1, vi(b.size()+1));

	for(int i = 0; i <= a.size(); ++i) mat[i][0] = 0;
	for(int i = 0; i <= b.size(); ++i) mat[0][i] = 0;

	for(int i = 1; i <= a.size(); ++i) {
		for(int j = 1; j <= b.size(); ++j) {
			if(a[i-1] == b[j-1]) 
				mat[i][j] = mat[i-1][j-1] + 1;
            else 
				mat[i][j] = max(mat[i][j-1], mat[i-1][j]);
		}
	}
    return mat[a.size()][b.size()];
}