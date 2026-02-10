import pandas as pd
import matplotlib.pyplot as plt
import os

# Caminhos dos arquivos
caminho_csv = '../dados/resultados.csv'
caminho_saida = '../graficos/grafico_desempenho.png'

# Verifica se o arquivo de entrada existe
if not os.path.exists(caminho_csv):
    print(f"Erro: O arquivo {caminho_csv} não foi encontrado.")
    print("Execute o código C primeiro para gerar os dados.")
    exit()

# 1. Ler os dados
df = pd.read_csv(caminho_csv)

# 2. Configurar o gráfico
plt.figure(figsize=(10, 6))

# Plotar os pontos e a linha
plt.plot(df['tamanho'], df['tempo_segundos'], marker='o', linestyle='-', color='b', label='Wagner-Fischer (Matriz)')

# 3. Estilização
plt.title('Análise de Complexidade: Algoritmo de Levenshtein (Wagner-Fischer)', fontsize=14)
plt.xlabel('Tamanho das Strings (n)', fontsize=12)
plt.ylabel('Tempo de Execução (segundos)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# Adicionar anotação de complexidade teórica
plt.text(df['tamanho'].iloc[-1], df['tempo_segundos'].iloc[-1], 
         r'$O(m \times n)$', fontsize=12, verticalalignment='bottom')

# Se o arquivo já existe, cria um novo nome (ex: grafico_desempenho_1.png)
if os.path.exists(caminho_saida):
    base, extensao = os.path.splitext(caminho_saida)
    contador = 1
    novo_caminho = f"{base}_{contador}{extensao}"
    
    while os.path.exists(novo_caminho):
        contador += 1
        novo_caminho = f"{base}_{contador}{extensao}"
    
    caminho_saida = novo_caminho
# --------------------------------------------------------

# 4. Salvar e Mostrar
plt.savefig(caminho_saida, dpi=300)
print(f"Gráfico salvo com sucesso em: {os.path.abspath(caminho_saida)}")
# plt.show() # Emular exibição do gráfico (opcional)