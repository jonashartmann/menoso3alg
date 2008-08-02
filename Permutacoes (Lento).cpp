// Gera todas as permutacoes de 0 a tamanho-1
// vb inicializado c/ false (0 a tamanho-1)
void permut(int tamanho, vi *perm, vb jahFoi)
{
	for(int i = 0; i < tamanho; ++i) {
		if(!jahFoi[i]) {
			perm->push_back(i);
			jahFoi[i] = true;
			
			permut(tamanho, perm, jahFoi);
			if(perm->size() == tamanho) {
				// PROCESSAR RESULTADO
			}
			perm->pop_back();
			jahFoi[i] = false;
		}
	}
}