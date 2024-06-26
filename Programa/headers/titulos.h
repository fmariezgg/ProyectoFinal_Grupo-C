#include <iostream>
#include "LemonLibCSB.h"
using namespace std;

//ascii art para los menus
void title_splash();
void menu_principal();
//---------------------------------
void titulo_prod();
void titulo_clientes();
//---------------------------------
void titulo_finanzas();
void titulo_ventas();
void titulo_pendientes();
void titulo_costos_Fijos();
void titulo_costos_Variables();

//***************************************************************************************************

void title_splash() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "    /$$    /$$                      /$$                                     /$$                 /$$                           /$$\n";
    cout << "   | $$   | $$                     | $$                                    | $$                | $$                          | $$\n";
    cout << "   | $$   | $$ /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$        /$$$$$$$  /$$$$$$       | $$        /$$$$$$   /$$$$$$$| $$$$$$$   /$$$$$$\n";
    cout << "   |  $$ / $$//$$__  $$| $$__  $$|_  $$_/   |____  $$ /$$_____/       /$$__  $$ /$$__  $$      | $$       /$$__  $$ /$$_____/| $$__  $$ /$$__  $$\n";
    cout << "    \\  $$ $$/| $$$$$$$$| $$  \\ $$  | $$      /$$$$$$$|  $$$$$$       | $$  | $$| $$$$$$$$      | $$      | $$$$$$$$| $$      | $$  \\ $$| $$$$$$$\n";
    cout << "     \\  $$$/ | $$_____/| $$  | $$  | $$ /$$ /$$__  $$ \\____  $$      | $$  | $$| $$_____/      | $$      | $$_____/| $$      | $$  | $$| $$_____/\n";
    cout << "      \\  $/  |  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/      |  $$$$$$$|  $$$$$$$      | $$$$$$$$|  $$$$$$$|  $$$$$$$| $$  | $$|  $$$$$$$\n";
    cout << "       \\_/    \\_______/|__/  |__/   \\___/   \\_______/|_______/        \\_______/ \\_______/      |________/ \\_______/ \\_______/|__/  |__/ \\_______/\n" << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << "    v1.0.0: por Fátima Zogaib y Joaquín Pérez\n";
    cout << " --------------------------------------------------------------------------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void menu_principal() {
    LLC::_colSET(LLC::cGREEN);
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
    LLC::_colSET(LLC::cGRAY);
    cout << " ----------------------------------------------------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_prod() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "    /$$$$$$$                           /$$                               /$$                    \n";
    cout << "   | $$__  $$                         | $$                              |__/                    \n";
    cout << "   | $$  \\ $$ /$$$$$$   /$$$$$$   /$$$$$$$ /$$   /$$  /$$$$$$$  /$$$$$$$ /$$  /$$$$$$  /$$$$$$$ \n";
    cout << "   | $$$$$$$//$$__  $$ /$$__  $$ /$$__  $$| $$  | $$ /$$_____/ /$$_____/| $$ /$$__  $$| $$__  $$\n";
    cout << "   | $$____/| $$  \\__/| $$  \\ $$| $$  | $$| $$  | $$| $$      | $$      | $$| $$  \\ $$| $$  \\ $$\n";
    cout << "   | $$     | $$      | $$  | $$| $$  | $$| $$  | $$| $$      | $$      | $$| $$  | $$| $$  | $$\n";
    cout << "   | $$     | $$      |  $$$$$$/|  $$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$|  $$$$$$/| $$  | $$\n";
    cout << "   |__/     |__/       \\______/  \\_______/ \\______/  \\_______/ \\_______/|__/ \\______/ |__/  |__/\n" << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << " -------------------------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_clientes() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "     /$$$$$$  /$$ /$$                       /$$                        \n";
    cout << "    /$$__  $$| $$|__/                      | $$                        \n";
    cout << "   | $$  \\__/| $$ /$$  /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   | $$      | $$| $$ /$$__  $$| $$__  $$|_  $$_/   /$$__  $$ /$$_____/\n";
    cout << "   | $$      | $$| $$| $$$$$$$$| $$  \\ $$  | $$    | $$$$$$$$|  $$$$$$ \n";
    cout << "   | $$    $$| $$| $$| $$_____/| $$  | $$  | $$ /$$| $$_____/ \\____  $$\n";
    cout << "   |  $$$$$$/| $$| $$|  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/\n";
    cout << "    \\______/ |__/|__/ \\_______/|__/  |__/   \\___/   \\_______/|_______/ \n" << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << " ------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_finanzas() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "    /$$$$$$$$ /$$                                                            \n";
    cout << "   | $$_____/|__/                                                            \n";
    cout << "   | $$       /$$ /$$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$  /$$$$$$   /$$$$$$$\n";
    cout << "   | $$$$$   | $$| $$__  $$ |____  $$| $$__  $$|____ /$$/ |____  $$ /$$_____/\n";
    cout << "   | $$__/   | $$| $$  \\ $$  /$$$$$$$| $$  \\ $$   /$$$$/   /$$$$$$$|  $$$$$$ \n";
    cout << "   | $$      | $$| $$  | $$ /$$__  $$| $$  | $$  /$$__/   /$$__  $$ \\____  $$\n";
    cout << "   | $$      | $$| $$  | $$|  $$$$$$$| $$  | $$ /$$$$$$$$|  $$$$$$$ /$$$$$$$/\n";
    cout << "   |__/      |__/|__/  |__/ \\_______/|__/  |__/|________/ \\_______/|_______/ \n" << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << " ------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_ventas() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "    /$$    /$$                      /$$                        \n";
    cout << "   | $$   | $$                     | $$                        \n";
    cout << "   | $$   | $$ /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   |  $$ / $$//$$__  $$| $$__  $$|_  $$_/   |____  $$ /$$_____/\n";
    cout << "    \\  $$ $$/| $$$$$$$$| $$  \\ $$  | $$      /$$$$$$$|  $$$$$$ \n";
    cout << "     \\  $$$/ | $$_____/| $$  | $$  | $$ /$$ /$$__  $$ \\____  $$\n";
    cout << "      \\  $/  |  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/\n";
    cout << "       \\_/    \\_______/|__/  |__/   \\___/   \\_______/|_______/ \n" << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << " ----------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_pendientes() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "    /$$$$$$$                                               /$$$$$$$                           /$$ /$$                       /$$                        \n";
    cout << "   | $$__  $$                                             | $$__  $$                         | $$|__/                      | $$                        \n";
    cout << "   | $$  \\ $$ /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$$      | $$  \\ $$ /$$$$$$  /$$$$$$$   /$$$$$$$ /$$  /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$\n";
    cout << "   | $$$$$$$/|____  $$ /$$__  $$ /$$__  $$ /$$_____/      | $$$$$$$//$$__  $$| $$__  $$ /$$__  $$| $$ /$$__  $$| $$__  $$|_  $$_/   /$$__  $$ /$$_____/\n";
    cout << "   | $$____/  /$$$$$$$| $$  \\ $$| $$  \\ $$|  $$$$$$       | $$____/| $$$$$$$$| $$  \\ $$| $$  | $$| $$| $$$$$$$$| $$  \\ $$  | $$    | $$$$$$$$|  $$$$$$ \n";
    cout << "   | $$      /$$__  $$| $$  | $$| $$  | $$ \\____  $$      | $$     | $$_____/| $$  | $$| $$  | $$| $$| $$_____/| $$  | $$  | $$ /$$| $$_____/ \\____  $$\n";
    cout << "   | $$     |  $$$$$$$|  $$$$$$$|  $$$$$$/ /$$$$$$$/      | $$     |  $$$$$$$| $$  | $$|  $$$$$$$| $$|  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/\n";
    cout << "   |__/      \\_______/ \\____  $$ \\______/ |_______/       |__/      \\_______/|__/  |__/ \\_______/|__/ \\_______/|__/  |__/   \\___/   \\_______/|_______/ \n";
    cout << "                       /$$  \\ $$                                                                                                                       \n";
    cout << "                      |  $$$$$$/                                                                                                                       \n";
    cout << "                       \\______/                                                                                                                        " << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << " --------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_costos_Fijos() {
    LLC::_colSET(LLC::cGREEN);
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
    LLC::_colSET(LLC::cGRAY);
    cout << " ------------------------------------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

void titulo_costos_Variables() {
    LLC::_colSET(LLC::cGREEN);
    cout << endl;
    cout << "     /$$$$$$                        /$$                               /$$    /$$                    /$$           /$$       /$$                    \n";
    cout << "    /$$__  $$                      | $$                              | $$   | $$                   |__/          | $$      | $$                    \n";
    cout << "   | $$  \\__/  /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$$      | $$   | $$ /$$$$$$   /$$$$$$  /$$  /$$$$$$ | $$$$$$$ | $$  /$$$$$$   /$$$$$$$\n";
    cout << "   | $$       /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$_____/      |  $$ / $$/|____  $$ /$$__  $$| $$ |____  $$| $$__  $$| $$ /$$__  $$ /$$_____/\n";
    cout << "   | $$      | $$  \\ $$|  $$$$$$   | $$    | $$  \\ $$|  $$$$$$        \\  $$ $$/  /$$$$$$$| $$  \\__/| $$  /$$$$$$$| $$  \\ $$| $$| $$$$$$$$|  $$$$$$ \n";
    cout << "   | $$    $$| $$  | $$ \\____  $$  | $$ /$$| $$  | $$ \\____  $$        \\  $$$/  /$$__  $$| $$      | $$ /$$__  $$| $$  | $$| $$| $$_____/ \\____  $$\n";
    cout << "   |  $$$$$$/|  $$$$$$/ /$$$$$$$/  |  $$$$/|  $$$$$$/ /$$$$$$$/         \\  $/  |  $$$$$$$| $$      | $$|  $$$$$$$| $$$$$$$/| $$|  $$$$$$$ /$$$$$$$/\n";
    cout << "    \\______/  \\______/ |_______/    \\___/   \\______/ |_______/           \\_/    \\_______/|__/      |__/ \\_______/|_______/ |__/ \\_______/|_______/ \n" << endl;
    LLC::_colSET(LLC::cGRAY);
    cout << " ----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    LLC::_colRESET();
}

//***************************************************************************************************