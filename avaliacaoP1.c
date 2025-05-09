#include <stdio.h>

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sao_coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

int inverso_modular(int g, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = g;

    while (novo_r != 0) {
        int quociente = r / novo_r;

        int temp_t = t;
        t = novo_t;
        novo_t = temp_t - quociente * novo_t;

        int temp_r = r;
        r = novo_r;
        novo_r = temp_r - quociente * novo_r;
    }

    if (r > 1) return -1; 
    if (t < 0) t += n;
    return t;
}

int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int phi(int n) {
    int resultado = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            resultado -= resultado / p;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
    return resultado;
}

int exp_mod(int base, int exp, int mod) {
    int resultado = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            resultado = (resultado * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return resultado;
}

int main() {
    int H, G, n, x, n1;

    printf("Digite H, G, n, x e n1:\n");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    printf("\nPASSO 1: Verificando se G e n são primos entre si...\n");
    if (!sao_coprimos(G, n)) {
        printf("G (%d) e n (%d) não são primos entre si. A divisão modular não é possível.\n", G, n);
        return 0;
    } else {
        printf("G e n são primos entre si.\n");
    }

    printf("\nPASSO 2: Calculando o inverso modular de G em Z%d...\n", n);
    int G_inv = inverso_modular(G, n);
    if (G_inv == -1) {
        printf("O inverso de G não existe em Z%d.\n", n);
        return 0;
    } else {
        printf("O inverso de G é: %d\n", G_inv);
    }

    printf("\nPASSO 3: Calculando a = H ⊘ G em Z%d...\n", n);
    int a = (H * G_inv) % n;
    printf("a = %d\n", a);

    printf("\nPASSO 4: Verificando se a (%d) e n1 (%d) são coprimos...\n", a, n1);
    if (sao_coprimos(a, n1)) {
        printf("a e n1 são coprimos.\n");
    } else {
        printf("a e n1 não são coprimos.\n");
    }

    printf("\nPASSO 5: Verificando se n1 (%d) é primo...\n", n1);
    int x1;
    if (eh_primo(n1)) {
        printf("n1 é primo. Aplicando o Pequeno Teorema de Fermat.\n");
        x1 = n1 - 1;
    } else {
        printf("n1 não é primo. Aplicando o Teorema de Euler.\n");
        x1 = phi(n1);
        printf("φ(%d) = %d\n", n1, x1);
    }

    printf("\nPASSO 8: Decompondo x (%d) na forma x = x1 * q + r\n", x);
    int q = x / x1;
    int r = x % x1;
    printf("x = %d * %d + %d\n", x1, q, r);

    printf("\nPASSO 9 e 10: Calculando valores intermediários...\n");
    int x2 = exp_mod(a, x1, n1);
    printf("a^x1 mod n1 = %d\n", x2);

    int x2q = exp_mod(x2, q, n1);
    printf("(a^x1)^q mod n1 = %d\n", x2q);

    int ar = exp_mod(a, r, n1);
    printf("a^r mod n1 = %d\n", ar);

    printf("\nPASSO 11: Calculando o resultado final...\n");
    int resultado = (x2q * ar) % n1;
    printf("Resultado final: ((%d * %d) mod %d) = %d\n", x2q, ar, n1, resultado);

    return 0;
}