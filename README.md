# 🔐 Cifra de César + Sequências Numéricas (C)

Atividade Avaliativa 02 — **Algoritmo e Pensamento Computacional**
Professor: Francisco de Assis Cavallaro

Programa em C que une criptografia simples e matemática aplicada (progressões e séries) em **duas camadas**:

1. **Camada 1:** Cifra de César com SHIFT fixo
2. **Camada 2:** deslocamento dinâmico por sequência numérica (PA, PG, Fibonacci ou Primos)

Deslocamento total da letra `i` = `SHIFT + sequência[i]` (mod 26)

## ▶️ Como compilar e executar

```bash
gcc -Wall -Wextra -o cifra cifra.c
./cifra
```

## 📋 Menu

- `1` Criptografar · `2` Descriptografar · `0` Sair
- Palavra: até 15 letras, sem acentos ou caracteres especiais
- Tipos de sequência: `1` PA · `2` PG · `3` Fibonacci · `4` Primos

## 🧪 Exemplo

```
Palavra: coracao | SHIFT: 3 | Sequência: Fibonacci (1, 1, 2, 3, 5, 8, 13)
Saída: gswgkle
```

Arquivo `resultado_criptografia.txt`:
```
Palavra codificada: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7
```

> Obs.: o enunciado apresenta `fqvdjqb` como saída desse exemplo, mas aplicando a fórmula
> `SHIFT + sequência[i]` o resultado correto é `gswgkle`.


## 👥 Integrantes

- Marcelo Vitor Sousa Ribeiro
- Fabricio Duarte Santos 
