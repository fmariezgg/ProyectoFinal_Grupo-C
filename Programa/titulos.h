#include <iostream>
#include <windows.h>
using namespace std;

//cambian los colores de la consola para que se vea bonito
void cambiar_color(int color);
void resetear_color();

//ascii art para los menus
void title_splash();
void menu_principal();
//---------------------------------
void titulo_prod();
void titulo_clientes();
//---------------------------------
void titulo_finanzas();
void titulo_ventas();
void titulo_costos();
void titulo_costos_Fijos();
void titulo_costos_Variables();
void titulo_utilidad();
//---------------------------------
void titulo_facturacion();
void titulo_reportes();

//***************************************************************************************************

void cambiar_color(int color) {
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consola, color);
}

void resetear_color() {
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consola, 15);
}

//***************************************************************************************************

void title_splash() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$    /$$                      /$$                                     /$$                 /$$                           /$$\n";
    cout << "   | $$   | $$                     | $$                                    | $$                | $$                          | $$\n";
    cout << "   | $$   | $$ /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$        /$$$$$$$  /$$$$$$       | $$        /$$$$$$   /$$$$$$$| $$$$$$$   /$$$$$$\n";
    cout << "   |  $$ / $$//$$__  $$| $$__  $$|_  $$_/   |____  $$ /$$_____/       /$$__  $$ /$$__  $$      | $$       /$$__  $$ /$$_____/| $$__  $$ /$$__  $$\n";
    cout << "    \\  $$ $$/| $$$$$$$$| $$  \\ $$  | $$      /$$$$$$$|  $$$$$$       | $$  | $$| $$$$$$$$      | $$      | $$$$$$$$| $$      | $$  \\ $$| $$$$$$$\n";
    cout << "     \\  $$$/ | $$_____/| $$  | $$  | $$ /$$ /$$__  $$ \\____  $$      | $$  | $$| $$_____/      | $$      | $$_____/| $$      | $$  | $$| $$_____/\n";
    cout << "      \\  $/  |  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/      |  $$$$$$$|  $$$$$$$      | $$$$$$$$|  $$$$$$$|  $$$$$$$| $$  | $$|  $$$$$$$\n";
    cout << "       \\_/    \\_______/|__/  |__/   \\___/   \\_______/|_______/        \\_______/ \\_______/      |________/ \\_______/ \\_______/|__/  |__/ \\_______/\n" << endl;
    cambiar_color(8);
    cout << "    v1.0.0: por Fátima Zogaib y Joaquín Pérez\n";
    cout << " --------------------------------------------------------------------------------------------------------------------------------------------------\n";
    resetear_color();
}

void menu_principal() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$      /$$                                     /$$$$$$$           /$$                     /$$                     /$$\n";
    cout << "   | $$$    /$$$                                    | $$__  $$         |__/                    |__/                    | $$\n";
    cout << "   | $$$$  /$$$$  /$$$$$$  /$$$$$$$  /$$   /$$      | $$  \\ $$ /$$$$$$  /$$ /$$$$$$$   /$$$$$$$ /$$  /$$$$$$   /$$$$$$ | $$\n";
    cout << "   | $$ $$/$$ $$ /$$__  $$| $$__  $$| $$  | $$      | $$$$$$$//$$__  $$| $$| $$__  $$ /$$_____/| $$ /$$__  $$ |____  $$| $$\n";
    cout << "   | $$  $$$| $$| $$$$$$$$| $$  \\ $$| $$  | $$      | $$____/| $$  \\__/| $$| $$  \\ $$| $$      | $$| $$  \\ $$  /$$$$$$$| $$\n";
    cout << "   | $$\\  $ | $$| $$_____/| $$  | $$| $$  | $$      | $$     | $$      | $$| $$  | $$| $$      | $$| $$  | $$ /$$__  $$| $$\n";
    cout << "   | $$ \\/  | $$|  $$$$$$$| $$  | $$|  $$$$$$/      | $$     | $$      | $$| $$  | $$|  $$$$$$$| $$| $$$$$$$/|  $$$$$$$| $$\n";
    cout << "   |__/     |__/ \\_______/|__/  |__/ \\______/       |__/     |__/      |__/|__/  |__/ \\_______/|__/| $$____/  \\_______/|__/\n";
    cout << "                                                                                                   | $$\n";
    cout << "                                                                                                   |__/" << endl;
    cambiar_color(8);
    cout << " ----------------------------------------------------------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_prod() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$$$$$$                           /$$                               /$$                    \n";
    cout << "   | $$__  $$                         | $$                              |__/                    \n";
    cout << "   | $$  \\ $$ /$$$$$$   /$$$$$$   /$$$$$$$ /$$   /$$  /$$$$$$$  /$$$$$$$ /$$  /$$$$$$  /$$$$$$$ \n";
    cout << "   | $$$$$$$//$$__  $$ /$$__  $$ /$$__  $$| $$  | $$ /$$_____/ /$$_____/| $$ /$$__  $$| $$__  $$\n";
    cout << "   | $$____/| $$  \\__/| $$  \\ $$| $$  | $$| $$  | $$| $$      | $$      | $$| $$  \\ $$| $$  \\ $$\n";
    cout << "   | $$     | $$      | $$  | $$| $$  | $$| $$  | $$| $$      | $$      | $$| $$  | $$| $$  | $$\n";
    cout << "   | $$     | $$      |  $$$$$$/|  $$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$|  $$$$$$/| $$  | $$\n";
    cout << "   |__/     |__/       \\______/  \\_______/ \\______/  \\_______/ \\_______/|__/ \\______/ |__/  |__/\n" << endl;
    cambiar_color(8);
    cout << " -------------------------------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_clientes() {
    cambiar_color(10);
    cout << endl;
    cout << "     /$$$$$$  /$$ /$$                       /$$                        \n";
    cout << "    /$$__  $$| $$|__/                      | $$                        \n";
    cout << "   | $$  \\__/| $$ /$$  /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   | $$      | $$| $$ /$$__  $$| $$__  $$|_  $$_/   /$$__  $$ /$$_____/\n";
    cout << "   | $$      | $$| $$| $$$$$$$$| $$  \\ $$  | $$    | $$$$$$$$|  $$$$$$ \n";
    cout << "   | $$    $$| $$| $$| $$_____/| $$  | $$  | $$ /$$| $$_____/ \\____  $$\n";
    cout << "   |  $$$$$$/| $$| $$|  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/\n";
    cout << "    \\______/ |__/|__/ \\_______/|__/  |__/   \\___/   \\_______/|_______/ \n" << endl;
    cambiar_color(8);
    cout << " ------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_finanzas() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$$$$$$$ /$$                                                            \n";
    cout << "   | $$_____/|__/                                                            \n";
    cout << "   | $$       /$$ /$$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$  /$$$$$$   /$$$$$$$\n";
    cout << "   | $$$$$   | $$| $$__  $$ |____  $$| $$__  $$|____ /$$/ |____  $$ /$$_____/\n";
    cout << "   | $$__/   | $$| $$  \\ $$  /$$$$$$$| $$  \\ $$   /$$$$/   /$$$$$$$|  $$$$$$ \n";
    cout << "   | $$      | $$| $$  | $$ /$$__  $$| $$  | $$  /$$__/   /$$__  $$ \\____  $$\n";
    cout << "   | $$      | $$| $$  | $$|  $$$$$$$| $$  | $$ /$$$$$$$$|  $$$$$$$ /$$$$$$$/\n";
    cout << "   |__/      |__/|__/  |__/ \\_______/|__/  |__/|________/ \\_______/|_______/ \n" << endl;
    cambiar_color(8);
    cout << " ------------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_ventas() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$    /$$                      /$$                        \n";
    cout << "   | $$   | $$                     | $$                        \n";
    cout << "   | $$   | $$ /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   |  $$ / $$//$$__  $$| $$__  $$|_  $$_/   |____  $$ /$$_____/\n";
    cout << "    \\  $$ $$/| $$$$$$$$| $$  \\ $$  | $$      /$$$$$$$|  $$$$$$ \n";
    cout << "     \\  $$$/ | $$_____/| $$  | $$  | $$ /$$ /$$__  $$ \\____  $$\n";
    cout << "      \\  $/  |  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/\n";
    cout << "       \\_/    \\_______/|__/  |__/   \\___/   \\_______/|_______/ \n" << endl;
    cambiar_color(8);
    cout << " ----------------------------------------------------------------\n";
    resetear_color();
}

void titulo_costos() {
    cambiar_color(10);
    cout << endl;
    cout << "     /$$$$$$                        /$$                        \n";
    cout << "    /$$__  $$                      | $$                        \n";
    cout << "   | $$  \\__/  /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   | $$       /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$_____/\n";
    cout << "   | $$      | $$  \\ $$|  $$$$$$   | $$    | $$  \\ $$|  $$$$$$ \n";
    cout << "   | $$    $$| $$  | $$ \\____  $$  | $$ /$$| $$  | $$ \\____  $$\n";
    cout << "   |  $$$$$$/|  $$$$$$/ /$$$$$$$/  |  $$$$/|  $$$$$$/ /$$$$$$$/\n";
    cout << "    \\______/  \\______/ |_______/    \\___/   \\______/ |_______/ \n" << endl;
    cambiar_color(8);
    cout << " ----------------------------------------------------------------\n";
    resetear_color();
}

void titulo_costos_Fijos() {
    cambiar_color(10);
    cout << endl;
    cout << "     /$$$$$$                        /$$                               /$$$$$$$$ /$$                        \n";
    cout << "    /$$__  $$                      | $$                              | $$_____/|__/                        \n";
    cout << "   | $$  \\__/  /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$$      | $$       /$$ /$$  /$$$$$$   /$$$$$$$\n";
    cout << "   | $$       /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$_____/      | $$$$$   | $$|__/ /$$__  $$ /$$_____/\n";
    cout << "   | $$      | $$  \\ $$|  $$$$$$   | $$    | $$  \\ $$|  $$$$$$       | $$__/   | $$ /$$| $$  \\ $$|  $$$$$$ \n";
    cout << "   | $$    $$| $$  | $$ \\____  $$  | $$ /$$| $$  | $$ \\____  $$      | $$      | $$| $$| $$  | $$ \\____  $$\n";
    cout << "   |  $$$$$$/|  $$$$$$/ /$$$$$$$/  |  $$$$/|  $$$$$$/ /$$$$$$$/      | $$      | $$| $$|  $$$$$$/ /$$$$$$$/\n";
    cout << "    \\______/  \\______/ |_______/    \\___/   \\______/ |_______/       |__/      |__/| $$ \\______/ |_______/ \n";
    cout << "                                                                              /$$  | $$                    \n";
    cout << "                                                                             |  $$$$$$/                    \n";
    cout << "                                                                              \\______/                     " << endl;
    cambiar_color(8);
    cout << " ------------------------------------------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_costos_Variables() {
    cambiar_color(10);
    cout << endl;
    cout << "     /$$$$$$                        /$$                               /$$    /$$                    /$$           /$$       /$$                    \n";
    cout << "    /$$__  $$                      | $$                              | $$   | $$                   |__/          | $$      | $$                    \n";
    cout << "   | $$  \\__/  /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$$      | $$   | $$ /$$$$$$   /$$$$$$  /$$  /$$$$$$ | $$$$$$$ | $$  /$$$$$$   /$$$$$$$\n";
    cout << "   | $$       /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$_____/      |  $$ / $$/|____  $$ /$$__  $$| $$ |____  $$| $$__  $$| $$ /$$__  $$ /$$_____/\n";
    cout << "   | $$      | $$  \\ $$|  $$$$$$   | $$    | $$  \\ $$|  $$$$$$        \\  $$ $$/  /$$$$$$$| $$  \\__/| $$  /$$$$$$$| $$  \\ $$| $$| $$$$$$$$|  $$$$$$ \n";
    cout << "   | $$    $$| $$  | $$ \\____  $$  | $$ /$$| $$  | $$ \\____  $$        \\  $$$/  /$$__  $$| $$      | $$ /$$__  $$| $$  | $$| $$| $$_____/ \\____  $$\n";
    cout << "   |  $$$$$$/|  $$$$$$/ /$$$$$$$/  |  $$$$/|  $$$$$$/ /$$$$$$$/         \\  $/  |  $$$$$$$| $$      | $$|  $$$$$$$| $$$$$$$/| $$|  $$$$$$$ /$$$$$$$/\n";
    cout << "    \\______/  \\______/ |_______/    \\___/   \\______/ |_______/           \\_/    \\_______/|__/      |__/ \\_______/|_______/ |__/ \\_______/|_______/ \n" << endl;
    cambiar_color(8);
    cout << " ----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_utilidad() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$   /$$   /$$     /$$ /$$ /$$       /$$                 /$$\n";
    cout << "   | $$  | $$  | $$    |__/| $$|__/      | $$                | $$\n";
    cout << "   | $$  | $$ /$$$$$$   /$$| $$ /$$  /$$$$$$$  /$$$$$$   /$$$$$$$\n";
    cout << "   | $$  | $$|_  $$_/  | $$| $$| $$ /$$__  $$ |____  $$ /$$__  $$\n";
    cout << "   | $$  | $$  | $$    | $$| $$| $$| $$  | $$  /$$$$$$$| $$  | $$\n";
    cout << "   | $$  | $$  | $$ /$$| $$| $$| $$| $$  | $$ /$$__  $$| $$  | $$\n";
    cout << "   |  $$$$$$/  |  $$$$/| $$| $$| $$|  $$$$$$$|  $$$$$$$|  $$$$$$$\n";
    cout << "    \\______/    \\___/  |__/|__/|__/ \\_______/ \\_______/ \\_______/\n" << endl;
    cambiar_color(8);
    cout << " ------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_facturacion() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$$$$$$$                   /$$                                            /$$                    \n";
    cout << "   | $$_____/                  | $$                                           |__/                    \n";
    cout << "   | $$    /$$$$$$   /$$$$$$$ /$$$$$$   /$$   /$$  /$$$$$$  /$$$$$$   /$$$$$$$ /$$  /$$$$$$  /$$$$$$$ \n";
    cout << "   | $$$$$|____  $$ /$$_____/|_  $$_/  | $$  | $$ /$$__  $$|____  $$ /$$_____/| $$ /$$__  $$| $$__  $$\n";
    cout << "   | $$__/ /$$$$$$$| $$        | $$    | $$  | $$| $$  \\__/ /$$$$$$$| $$      | $$| $$  \\ $$| $$  \\ $$\n";
    cout << "   | $$   /$$__  $$| $$        | $$ /$$| $$  | $$| $$      /$$__  $$| $$      | $$| $$  | $$| $$  | $$\n";
    cout << "   | $$  |  $$$$$$$|  $$$$$$$  |  $$$$/|  $$$$$$/| $$     |  $$$$$$$|  $$$$$$$| $$|  $$$$$$/| $$  | $$\n";
    cout << "   |__/   \\_______/ \\_______/   \\___/   \\______/ |__/      \\_______/ \\_______/|__/ \\______/ |__/  |__/\n" << endl;
    cambiar_color(8);
    cout << " -------------------------------------------------------------------------------------------------------\n";
    resetear_color();
}

void titulo_reportes() {
    cambiar_color(10);
    cout << endl;
    cout << "    /$$$$$$$                                            /$$                        \n";
    cout << "   | $$__  $$                                          | $$                        \n";
    cout << "   | $$  \\ $$  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   | $$$$$$$/ /$$__  $$ /$$__  $$ /$$__  $$ /$$__  $$|_  $$_/   /$$__  $$ /$$_____/\n";
    cout << "   | $$__  $$| $$$$$$$$| $$  \\ $$| $$  \\ $$| $$  \\__/  | $$    | $$$$$$$$|  $$$$$$ \n";
    cout << "   | $$  \\ $$| $$_____/| $$  | $$| $$  | $$| $$        | $$ /$$| $$_____/ \\____  $$\n";
    cout << "   | $$  | $$|  $$$$$$$| $$$$$$$/|  $$$$$$/| $$        |  $$$$/|  $$$$$$$ /$$$$$$$/\n";
    cout << "   |__/  |__/ \\_______/| $$____/  \\______/ |__/         \\___/   \\_______/|_______/ \n";
    cout << "                       | $$                                                        \n";
    cout << "                       |__/                                                        \n" << endl;
    cambiar_color(8);
    cout << " ------------------------------------------------------------------------------------\n";
    resetear_color();
}