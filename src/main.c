#include <bin/shell/shell.h>
#include <drivers/keyboard/keyboard.h>

int main() {
    keyboardInit();
    shell();
}
