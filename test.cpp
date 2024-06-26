#include <bits/stdc++.h>
//#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include<conio.h>

using namespace std;

int tam = 100;
/*
int getch (void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
//Funcion para trabajar en linux con getch(), debido a que no esta presente en sus librerias
int getche (void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
*/
struct Banco{
    string nombre="";
    int cedula=0;
    string email="";
    int celular=0;
    string clave="";
    double saldo=0;
    vector<pair<int,string>> pagos ;
};

bool validarClave (string clave){
    int longitud, i;
    bool aux = true;
    longitud = clave.size();
    for (i = 0; i < longitud; i++){
	if (clave[i] < 48 || clave[i] > 57){
		aux = false;
            	break;
	}
    }
    return aux;
}

string capturarClave (){
    int contarLetras;
    bool comprobar = true, respuesta;
    char letra;
    string clave;
    cout << "INGRESE UNA CLAVE PARA LA CUENTA: ";
    contarLetras = 1;
    cin.ignore();
    do{
	//letra = getch();
	letra = getch();
	cout << "*";
	clave += letra;
	contarLetras++;
	if (contarLetras == 5){
	    comprobar = validarClave(clave);
	    if (comprobar == false){
	        contarLetras = 1;
	        system("cls");
                cout<<"\n";
                cout << "CARACTER PROHIBIDO.\n";
        	cout << "!VERIFICA QUE LOS DATOS SEAN CORRECTOS!.\n";
                cout << "DIGITE NUEVAMENTE SU CONTRASEÑA : ";
	        clave = "";
	        cout << "\n";
		}
	}
    }while (contarLetras <= 4 || comprobar == false);
    return clave;
}

bool compararClave(Banco cliente[], int tam, int ced) {
    int contarLetras;
    bool comprobar = true, estado = false;
    char letra;
    string clave;
    int intentos = 0;
    string pin;
    cout << "INGRESE LA CLAVE DE LA CUENTA-->";
    contarLetras = 1;
    cin.ignore();
    for (int i = 0; i < tam; i++) {
        if (cliente[i].cedula == ced) {
            pin = cliente[i].clave;
            break;
        }
    }
    do {
        letra = getch();
        cout << "*";
        clave += letra;
        contarLetras++;
        if (contarLetras == 5) {
            if (intentos == 3) {
                cout << "\nHA SUPERADO EL NUMERO DE INTENTOS DISPONIBLES\n";
                estado = false;
                break;
            }
            comprobar = validarClave(clave);
            if (comprobar == false) {
                contarLetras = 1;
                system("cls");
                cout << "CARACTER PROHIBIDO.\n";
                cout << "!VERIFICA QUE LOS DATOS SEAN CORRECTOS!.\n";
                cout << "DIGITE NUEVAMENTE SU CONTRASE�A : ";
                clave = "";
                intentos++;
                cout << "\n";
                cout << "INTENTOS RESTANTES: " << 3 - intentos << endl;
            } else if (clave != pin) {
                contarLetras = 1;
                system("cls");
                cout << "CONTRASENA INCORRECTA.\n";
                cout << "DIGITE NUEVAMENTE SU CONTRASENA : ";
                clave = "";
                intentos++;
                cout << "\n";
                cout << "INTENTOS RESTANTES: " << 3 - intentos << endl;
            } else {
                estado = true;
            }
        }
    } while (contarLetras <= 4 || comprobar == false);

    return estado;
}

int guardar (Banco cliente[], int tam){
    for (int i = 0; i < tam; i++){
        if (cliente[i].cedula == 0 && cliente[i].email.empty() && cliente[i].celular == 0 && cliente[i].clave.empty() && cliente[i].saldo == 0){
            return i;
        }
    }
    return 100;
}

bool validarCedula (Banco cliente[], int tam, int ced){
    for (int i = 0; i < tam; i++){
        if (cliente[i].cedula == ced){
            return true;
        }
    }
    return false;
}

void consultarSaldo(Banco cliente[], int tam, int ced){
    if(validarCedula(cliente,tam,ced)){
        bool validacion=compararClave(cliente,tam,ced);
        if(validacion){
            for(int i=0;i<tam;i++){
                if(cliente[i].cedula==ced && cliente[i].saldo>1500){
                    system("cls");
                    cout<<"\nHOLA SR "<<cliente[i].nombre<<"\n";
                    cout<<"VER EL SALDO TIENE UN COSTO DE $1,500\n";
                    cout<<"SU SALDO ANTES DE CONSULTAR ES-->"<<cliente[i].saldo<<"\n";
                    cliente[i].saldo-=1500;
                    cout<<"SU SALDO ACTUAL ES DE-->"<<cliente[i].saldo<<"\n";
                    break;
                }
                else{
                    cout<<"\nLA CUENTA NO TIENE SALDO SUFICIENTE PARA CONSULTAR EL DINERO GUARDADO.\n";
                    break;
                }
            }
        } else {
            cout << "\nLA CONTRASENA NO ES CORRECTA.\n";
        }
    } else {
        cin.ignore();
        cout << "LA CEDULA NO EXISTE EN EL SISTEMA.\n";
    }
}

void consignacion (Banco cliente[], int tam, int ced){
    bool cedulaExiste = validarCedula (cliente, tam, ced);
    if (cedulaExiste == true){
        double dineroConsignado = 0;
        string persona = "";
        system ("cls");
        cin.ignore();
        cout << "CONSIGNACIONES.\n";
        cout << "INGRESE SU NOMBRE.-->";
        fflush(stdin);
        getline (cin, persona);
        for(int i = 0; i < persona.size(); i++){
        	persona[i] = toupper(persona[i]);
		}
        cout << "INGRESE EL MONTO A CONSIGNAR.-->";
        cin >> dineroConsignado;
        if (dineroConsignado >= 5000){
            double impuesto=0,saldo=0;
            impuesto=(dineroConsignado/1000)*4;
            saldo+=dineroConsignado-impuesto;
            for (int i = 0; i < tam; i++){
                if (cliente[i].cedula == ced){
                    cliente[i].saldo += saldo;
                    break;
                }
            }
            cout << "EL DINERO SE HA CONSIGNADO.\nGRACIAS " << persona << " POR EL DINERO.\n";
        }
        else {
            cout << "EL MONTO MINIMO ES DE $5.000.\n";
            cout << "NO PUEDE CONSIGNAR DINERO. INTENTE NUEVAMENTE.\n";
        }
    }
    else {
        cout << "LA CUENTA NO ESTA EN NUESTRO SISTEMA.\n";
    }
}

void verClientes (Banco cliente[], int tam){
    system("cls");
    cout << "A VER QUE HAY GUARDADO.\n";
    for (int i = 0; i < tam; i++){
        int cedula = 0;
        cedula = cliente[i].cedula;
        if (cedula != 0){
            cout << "\nCLIENTE # " << i+1 << "\n";
            cout << "NOMBRE:" << cliente[i].nombre << "\n";
            cout << "CEDULA:" << cliente[i].cedula << "\n";
            cout << fixed;
            cout << setprecision(2) << "CELULAR:" << cliente[i].celular << "\n";
            cout << "CLAVE:" << cliente[i].clave<< "\n";
            cout << "CORREO:" <<cliente[i].email << "\n";
            cout << "SALDO DE LA CUENTA: " << cliente[i].saldo<< "\n";
            cout << "-----\nPAGOS:\n\n";
            /*for (const auto& pago : cliente[i].pagos) {
                cout << "ID: " << pago.first << " NOMBRE: " << pago.second << "\n";
            }*/
            for(int j=0;j<cliente[i].pagos.size();j++){
                cout<<j+1<<") "<<cliente[i].pagos[j].first<<" NOMBRE: "<<cliente[i].pagos[j].second<<"\n";
            }
        }
        else{
            cout << "\nINGRESE MAS CLIENTES. ( # DE ESPACIOS DISPONIBLES :" << tam-i << ")\n";
            break; // Break para romper fors esta brutal.
        }
    }
    cin.get();
}

void crearCuenta (Banco cliente[], int tam){
    system("cls");
    cout << "GRACIAS POR ELEGIRNOS.\n";
    cout << "COMPLETE EL FORMULARIO PARA CREAR UNA CUENTA.\n";
    int dato = guardar(cliente, tam);
    int cedula = 0;
    string nombre;
        if (dato >= 0 && dato < tam){
            cout << "INGRESE SU NOMBRE--> ";
            cin >> nombre;
            cout << "INGRESE EL NUMERO DE CEDULA--> ";
            cin >> cedula;
            if (!validarCedula(cliente, tam, cedula)){
                cliente[dato].nombre = nombre;
                cliente[dato].cedula = cedula;
                cout << "INGRESE SU EMAIL--> ";
                cin >> cliente[dato].email;
                cout << "INGRESE SU CELULAR--> ";
                cin >> cliente[dato].celular;
                cout << "\n";
                cliente[dato].clave = capturarClave();
                cout << "\n";
                cliente[dato].saldo = 0;
                /*int i=0;
                while(i<4){
                    cliente[dato].pagos.push_back(make_pair(0, ""));
                    i++;
                }*/
            }else{
                for (int i = 0; i < tam; i++){
                    if (cliente[i].cedula == cedula){
                        cout << "EL USUARIO CON LA CEDULA: " << cliente[i].cedula << " YA TIENE UNA CUENTA.\n";
                        cin.ignore();
                        break;
                    }
                }
                return;
            }
        cout << "\nLA CUENTA SE HA CREADO.\n";
    }
}

void retiros(Banco cliente[],int tam, int ced){
    double retiro=2000,res=0,retirar=0;
    if(validarCedula(cliente,tam,ced)){
        bool validacion=compararClave(cliente,tam,ced);
        if(validacion){
            for(int i=0;i<tam;i++){
                if(cliente[i].cedula==ced){
                    system("cls");
                    cout<<"HOLA SR "<<cliente[i].nombre<<"\n";
                    cout<<"HACER UN RETIRO TIENE UN COSTO DE $2,000\n";
                    cout<<"SU SALDO ANTES DE RETIRAR ES-->"<<cliente[i].saldo<<"\n";
                    cout<<"INGRESE LA CANTIDAD DE DINERO QUE DESEA RETIRAR-->";
                    cin>>retirar;
                    if(retirar+2000<cliente[i].saldo){
                        cin.ignore();
                        res=(cliente[i].saldo-retirar)-retiro;
                        cliente[i].saldo=res;
                        cout<<"HA RETIRADO-->"<<retirar<<" SATISFACTORIAMENTE.\n";
                        cout<<"SU SALDO DESPUES DE RETIRAR ES-->"<<cliente[i].saldo<<"\n";
                    }
                    else{
                        cin.ignore();
                        cout<<"FONDOS INSUFICIENTES.\n";
                        cout<<"LA CUENTA NO TIENE SALDO SUFICIENTE PARA RETIRAR "<<retirar<<"\n";
                    }
                    break;
                }
            }
        } else {
            cout << "\nLA CONTRASENA NO ES CORRECTA.\n";
        }
    } else {
        cin.ignore();
        cout << "LA CEDULA NO EXISTE EN EL SISTEMA.\n";
    }
}

void inscribirPago(Banco cliente[], int tam, int ced) {
    if (validarCedula(cliente, tam, ced)) {
        bool validacion = compararClave(cliente, tam, ced);
        if (validacion) {
            for(int i=0;i<tam;i++){
                if(cliente[i].cedula==ced){
                    system("cls");
                    cout << "INSCRIPCION DE PAGOS.\n";
                    char deseaIngresarPago;
                    int contPagos=cliente[i].pagos.size();
                    do {
                        int precio=0;
                        string nombrePago = "";
                        cout << "DESEA INGRESAR UN PAGO? (S/N)?--> ";
                        cin >> deseaIngresarPago;
                        if (toupper(deseaIngresarPago) == 'S') {
                            cout << "INGRESE EL PRECIO DE PAGO-->";
                            cin >> precio;
                            cout << "INGRESE EL NOMBRE DEL PRODUCTO--> ";
                            cin.ignore();
                            getline(cin, nombrePago);
                            cliente[i].pagos.push_back({precio, nombrePago});
                            cout << "PAGO INGRESADO CORRECTAMENTE.\n";
                            contPagos++;
                            if (contPagos >= 4) {
                                cout << "YA HAY 4 PAGOS REGISTRADOS, LIBERE ALGUNO PARA INSCRIBIR MAS.\n";
                                break;
                            }
                        }
                    } while (toupper(deseaIngresarPago) == 'S');
                    break;
                }
            }
        } else {
            cout << "\nLA CONTRASE�A NO ES CORRECTA.\n";
        }
    } else {
        cin.ignore();
        cout << "LA CEDULA NO EXISTE EN EL SISTEMA.\n";
    }
}

void pagos(Banco cliente[], int tam, int ced) {
    if (validarCedula(cliente, tam, ced)) {
        bool validacion = compararClave(cliente, tam, ced);
        if (validacion) {
            for (int i = 0; i < tam; i++) {
                if (cliente[i].cedula == ced) {
                    system("cls");
                    int numPago = 0;
                    cout << "HOLA SR " << cliente[i].nombre << "\nESTOS SON SUS PAGOS REGISTRADOS:\n";
                    for (int j = 0; j < cliente[i].pagos.size(); j++) {
                        cout << j + 1 << ") " << cliente[i].pagos[j].first << " NOMBRE: " << cliente[i].pagos[j].second << "\n";
                    }
                    cout << "ESCOJA UN NUMERO DE PAGO-->";
                    cin >> numPago;
                    if (numPago >= 1 && numPago <= cliente[i].pagos.size()) {
                            system("cls");
                            cout << "EL PRODUCTO A SELECCIONADO A PAGAR ES:\n-->" << cliente[i].pagos[numPago - 1].second << "\nCON UN COSTO DE:\n-->$" << cliente[i].pagos[numPago - 1].first << "\n";
                            char letra;
                            do {
                                cout << "DESEA PAGAR EL PRODUCTO? (S/N)";
                                cin >> letra;
                                if (toupper(letra) == 'S') {
                                    cin.ignore();
                                    if (cliente[i].pagos[numPago - 1].first > cliente[i].saldo) {
                                        cout << "FONDO INSUFICIENTE PARA PAGAR.\n";
                                        break;
                                    }else{
                                        cliente[i].saldo -= cliente[i].pagos[numPago - 1].first;
                                        cout << "SE HA PAGADO CORRECTAMENTE.\n";
                                        cliente[i].pagos.erase(cliente[i].pagos.begin() + numPago);
                                        break;
                                    }
                                }
                        }while (toupper(letra)=='S');
                    }
                }else {
                    break;
                }
            }
        } else {
            cin.ignore();
            cout << "LA CEDULA NO EXISTE EN EL SISTEMA.\n";
        }
    }
}

void eliminarCuenta(Banco cliente[], int tam, int ced) {
    if (validarCedula(cliente, tam, ced)) {
        bool validacion = compararClave(cliente, tam, ced);
        if (validacion) {
            for (int i = 0; i < tam; i++) {
                if (cliente[i].cedula == ced) {
                    int pagosValidos = 0;
                    for (int j = 0; j < cliente[i].pagos.size(); j++) {
                        if (cliente[i].pagos[j].first != 0 || !cliente[i].pagos[j].second.empty()) {
                            pagosValidos++;
                        }
                    }
                    if (pagosValidos <= 4) {
                        cout << "\nTIENE 4 O MAS PAGOS REGISTRADOS, NO PUEDE ELIMINAR LA CUENTA.\n";
                        break;
                    } else {
                        cliente[i].pagos.clear();
                        cliente[i].cedula = 0;
                        cliente[i].celular = 0;
                        cliente[i].clave = "";
                        cliente[i].email = "";
                        cliente[i].saldo = 0;
                        cliente[i].nombre = "";
                        cout << "\nSE HA ELIMINADO LA CUENTA DEL SISTEMA Y TODOS LOS PAGOS.\n";
                        pagosValidos=0;
                        break;
                    }
                    if (pagosValidos > 0 && pagosValidos < 4) {
                        char letra;
                        cout << "TIENE " << pagosValidos << " PAGOS PENDIENTES.\n";
                        cout << "DESEA REALIZAR SUS PAGOS DIRECTAMENTE ANTES DE ELIMINAR LA CUENTA? (S/N).";
                        cin >> letra;
                        if (toupper(letra) == 'S') {
                            pagos(cliente, tam, ced);
                        }
                    }
                    break;
                }
            }
        } else {
            cin.ignore();
            cout << "LA CONTRASE�A NO ES CORRECTA.\n";
        }
    } else {
        cin.ignore();
        cout << "LA CEDULA NO EXISTE EN EL SISTEMA.\n";
    }
}

void menu(){
    int opcion = 0;
    Banco cliente[tam];
    do{
        system("cls");
            cout << "MENU BANCO.\n";
            cout << "1. CREACION DE UNA CUENTA.\n";
            cout << "2. CONSIGNACIONES.\n";
            cout << "3. CONSULTAS DE SALDO.\n";
            cout << "4. RETIROS.\n";
            cout << "5. INSCRIBIR PAGOS.\n";
            cout << "6. PAGOS.\n";
            cout << "7. CANCELACION DE LA CUENTA.\n";
            cout << "8. SALIR.\n";
            cout << "~  QUE DESEA HACER?--> ";
            cin >> opcion;
        switch (opcion){
            case 1:{
                system("cls");
                int opc = 0;
                cout << "1. CREAR CUENTA.\n";
                cout << "2. VER CLIENTES.\n";
                cin >> opc;
                switch (opc){
                case 1:{
                    crearCuenta (cliente, tam);
                    break;
                }
                case 2:{
                    verClientes (cliente, tam);
                    break;
                }
                default:
                    system("cls");
                    cout << "NINGUNA OPCION DISPONIBLE FUE SELECCIONADA.\n";
                     cin.ignore();
                    break;
                }
                cin.ignore();
                break;
            }
            case 2:{
                system("cls");
                int ced = 0;
                cout << "INGRESE EL NUMERO DE CEDULA A LA CUAL VA A CONSIGNAR.\n-->";
                cin >> ced;
                consignacion (cliente, tam, ced);
                cin.get();
                cin.ignore();
                break;
            }
            case 3:{
                system("cls");
                int ced = 0;
                cout << "INGRESE EL NUMERO DE CEDULA A LA CUAL VA A CONSULTAR SALDO.\n-->";
                cin >> ced;
                consultarSaldo(cliente, tam, ced);
                cin.ignore();
                break;
            }
            case 4:{
                system("cls");
                int ced = 0;
                cout<<"INGRESE EL NUMERO DE CEDULA PARA HACER EL RETIRO.\n-->";
                cin>>ced;
                retiros(cliente,tam,ced);
                cin.ignore();
                break;
            }
            case 5:{
                system("cls");
                int ced = 0;
                cout<<"INGRESE EL NUMERO DE CEDULA PARA INSCRIBIR UN PAGO.\n-->";
                cin>>ced;
                inscribirPago(cliente,tam,ced);
                cin.ignore();
                break;
            }
            case 6:{
                system("cls");
                int ced = 0;
                cout<<"INGRESE EL NUMERO DE CEDULA PARA REALIZAR UN PAGO.\n-->";
                cin>>ced;
                pagos(cliente,tam,ced);
                cin.ignore();
                break;
            }
            case 7:{
                system("cls");
                int ced = 0;
                cout<<"INGRESE EL NUMERO DE CEDULA PARA ELIMINAR.\n-->";
                cin>>ced;
                eliminarCuenta(cliente,tam,ced);
                cin.ignore();
                break;
            }
            case 8:{
                system("cls");
                cout << "SALIENDO....\n";
                exit(0);
                break;
            }
            default:{
                system("cls");
                cout << "NINGUNA OPCION DISPONIBLE FUE SELECCIONADA.\n";
                cin.ignore();
                return menu();
                break;
            }
        }
    }while (opcion >= 1 && opcion < 9);
}
void datosClean (){
    Banco cliente[tam];
    for (int k = 0; k < tam; k++){
        cliente[k].cedula = 0;
        cliente[k].celular = 0;
        cliente[k].clave = "";
        cliente[k].email = "";
        cliente[k].saldo = 0;
        cliente[k].nombre = "";

    }
}

int main (){
    datosClean ();
    menu ();
    cin.ignore();
    return 0;
}
