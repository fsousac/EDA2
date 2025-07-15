/* Recebe um grafo G com custos positivos nos arcos e um vértice s. Calcula e armazena em pa[] o vetor de pais de uma CPT de G com raiz s (supondo que todos os vértices de G estão ao alcance de s). As distâncias a partir de s são armazenadas no vetor dist[]. (A função implementa o algoritmo de Dijkstra. O código foi inspirado no Programa 21.1 de Sedgewick.) */
void GRAPHcptD2(Graph G, int s, int *pa, int *dist)
{
    int mature[1000];
    for (int v = 0; v < G->V; ++v)
        pa[v] = -1, mature[v] = 0, dist[v] = INT_MAX;
    pa[s] = s, dist[s] = 0;
    PQinit(G->V);
    for (int v = 0; v < G->V; ++v)
        PQinsert(v, dist);

    while (!PQempty())
    {
        int y = PQdelmin(dist);
        if (dist[y] == INT_MAX)
            break;
        // atualização de dist[] e pa[]:
        for (link a = G->adj[y]; a != NULL; a = a->next)
        {
            int w = a->v;
            if (mature[w])
                continue;
            if (dist[y] + a->c < dist[w])
            {
                dist[w] = dist[y] + a->c;
                PQdec(w, dist);
                pa[w] = y;
            }
        }
        mature[y] = 1;
    }
    PQfree();
}