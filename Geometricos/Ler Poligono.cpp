// Evita vértices repetidos
vector<pt> pontos;
pontos.clear();
for(int i = 0; i < n; i++) {
	pt aux;
	cin >> aux.x >> aux.y;
	bool adiciona = true;
	for(int i = 0; i < pontos.size(); i++)
		if((pontos[i].x == aux.x)&&(pontos[i].y == aux.y)) {
			adiciona = false;
			break;
		}
	if(adiciona) pontos.push_back(aux);
}