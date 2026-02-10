all: graph

compile:
	@echo "--- Compilando código C ---"
	gcc codigos/benchmark_levenshtein.c -o codigos/benchmark.bin

run: compile
	@echo "--- Executando Benchmark ---"
	cd codigos && ./benchmark.bin

graph: run
	@echo "--- Gerando Gráfico ---"
	cd codigos && python3 gerar_grafico.py

.PHONY: all compile run graph
