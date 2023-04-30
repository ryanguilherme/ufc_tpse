#include <stdio.h>

#define gpio_enable (1 << 0)
#define gpio_direction (1 << 1)
#define gpio_level (1 << 2)
#define gpio_rest (1 << 3)

int main() {
    unsigned char gpioREG;
    // a) Escrever a lógica binária para setar a variável gpioREG como habilitado (gpio_enabled).
    gpioREG |= gpio_enable;
    // b) Escrever a lógica binária para testar se a variável gpioREG foi definido como saída (gpio_direction), caso positivo você deve desabilitar (gpio_enabled).
    if (gpioREG & gpio_direction) {
        gpioREG &= ~gpio_enable;
    }
    // c) Escrever a logica binária para setar a variável gpioREG como entrada (gpio_direction).
    gpioREG &= ~gpio_direction;
    // d) Escrever a logica binária para alterar o gpioREG como nível alto (gpio_level) ou nível baixo. Ex: se ele estava como alto passar para baixo e vice-versa).
    gpioREG ^= gpio_level;

}