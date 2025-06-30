#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>

using namespace std;
void menu();
void prueba();
int mci(string);
void dibujarControles();

void cambiarColorTexto(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void setcolor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

bool ValidaMenu(const char* dato) {
    for (int i = 0; dato[i] != '\0'; ++i) {
        if (!isdigit(dato[i])) {
            return false;
        }
    }
    return true;
}

class cancionn {
public:
    int id;
    string nombre_cancion;
    string artista;
    string album;
    string duracion;
    string ruta;
    cancionn *next;
    cancionn *back;
};
cancionn *aux= new cancionn();
class lista {
private:
    int cancionesAgregadas;
    cancionn *head;
public:
    lista() : cancionesAgregadas(0), head(nullptr) {}
    cancionn *getHead();
    void insertarCancion(int, string, string, string, string,string);
    void mostrarCanciones();
    void siguiente();
    bool vacia();
    void cargar();
    bool editarCancion(int, string, string, string, string, string);
    bool eliminarCancion(int);
    void ascendente();
    void descendente();
    void invertir();
    void eliminarPrimero();
    void eliminarUltimo();
    cancionn* buscarPorNombre(const string& nombre);
    cancionn* buscarArtista(const string& artistaBuscar);
    void mostrarPrimero();
    void mostrarUltimo();
    void ordenarAlfabeticamente();
    void reproducirCancion();
    bool mostrarflecha(string);
};

cancionn* lista::getHead() {
    return head;
}

bool lista::vacia() {
    if (head == NULL)
        return true;
    else
        return false;
}

void lista::insertarCancion(int id,string nombre_cancion,string artista,string album, string duracion, string ruta) {
    cancionn *rola = new cancionn();
    rola->id = id;
    rola->nombre_cancion = nombre_cancion;
    rola->artista = artista;
    rola->album = album;
    rola->duracion = duracion;
    rola->ruta = ruta;
    if (head == NULL) {
        rola->next = rola;
        rola->back = rola;
        head = rola;
    }
    else {
        cancionn *last_node = head->back;
        rola->next = head;
        rola->back = last_node;
        head->back = rola;
        last_node->next = rola;
    }
    cancionesAgregadas++;
}

void lista::cargar() {
    head = NULL;
    ifstream file;
    int id;
    string line;
    string nombre_cancion, artista, album, duracion, ruta;
    file.open("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar
    if(file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string id_str;
            getline(ss, id_str, ',');
            id = stoi(id_str);
            getline(ss, nombre_cancion, ',');
            getline(ss, artista, ',');
            getline(ss, album, ',');
            getline(ss, duracion, ',');
            ss>>ruta;
            insertarCancion(id, nombre_cancion, artista, album, duracion, ruta);
        }
        file.close();
    }
    aux=head;
}

void lista::mostrarCanciones() {
    int posY = 10; // Posicion inicial vertical
    if (!vacia()) {
        cancionn *temp = head;

        do {
            gotoxy(5, posY);
            cout << temp->id;

            gotoxy(10, posY);
            string nombreCorto = temp->nombre_cancion;
            if (nombreCorto.length() > 20) {
                nombreCorto = nombreCorto.substr(0, 20) + "...";
            }
            gotoxy(10, posY);
            cout << nombreCorto;

            string artistaCorto = temp->artista;
            if(artistaCorto.length()>12){
                artistaCorto = artistaCorto.substr(0, 12) + "...";
            }
            gotoxy(34,posY);
            cout<< artistaCorto;

            string albumCorto = temp->album;
            if(albumCorto.length()>20){
                albumCorto=albumCorto.substr(0,20) +"...";
            }
            gotoxy(51, posY);
            cout<< albumCorto;
            gotoxy(81, posY);
            cout<< temp->duracion;

            if (temp->next != head) {
                cout << "\n";
                posY += 2;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "\n";
    }
}
bool lista::mostrarflecha(string nombre)
{
    bool bandera = false;
    cancionn *temp=head;
    int posY = 10;
    if(temp!=NULL)
    {
        do
        {
            cambiarColorTexto(15);
            if(nombre==temp->nombre_cancion)
            {
            gotoxy(2,posY);
           cambiarColorTexto(12);
            cout<< "->" << endl;
            cambiarColorTexto(2);
            }
            gotoxy(5, posY);
            cout << temp->id;

            gotoxy(10, posY);
            string nombreCorto = temp->nombre_cancion;
            if (nombreCorto.length() > 20) {
                nombreCorto = nombreCorto.substr(0, 20) + "...";
            }
            gotoxy(10, posY);
            cout << nombreCorto;

            string artistaCorto = temp->artista;
            if(artistaCorto.length()>12){
                artistaCorto = artistaCorto.substr(0, 12) + "...";
            }
            gotoxy(34,posY);
            cout<< artistaCorto;

            string albumCorto = temp->album;
            if(albumCorto.length()>20){
                albumCorto=albumCorto.substr(0,20) +"...";
            }
            gotoxy(51, posY);
            cout<< albumCorto;
            gotoxy(81, posY);
            cout<< temp->duracion;

            if (temp->next != head) {
                cout << "\n";
                posY += 2;
            }
            temp = temp->next;
        }while(temp != head);
        bandera=true;
    }
    else{
        cout<<"No hay canciones"<<endl;
        bandera=false;
    }

    return bandera;
}

bool lista::editarCancion(int id, string nombre_cancion, string artista, string album, string duracion, string ruta) {
    if (vacia()) {
        gotoxy(2,2);
        cout << "La lista esta vacia." << endl;
        return false;
    }
    cancionn *temp = head;
    do {
        if (temp->id == id) {
            temp->nombre_cancion = nombre_cancion;
            temp->artista = artista;
            temp->album = album;
            temp->duracion = duracion;
            temp->ruta = ruta;
            return true;
        }
        temp = temp->next;
    } while (temp != head);
    gotoxy(2,2);
    cout << "La cancion con ID " << id << " no se encontro en la lista." << endl;
    return false;
}

bool lista::eliminarCancion(int id) {
    if (vacia()) {
        gotoxy(2,2);
        cout << "La lista esta vacia." << endl;
        return false;
    }

    cancionn *temp = head;
    do {
        if (temp->id == id) {
            // Eliminar el nodo
            if (temp == head && temp->next == head) {
                head = NULL;
            } else {
                temp->back->next = temp->next;
                temp->next->back = temp->back;
                if (temp == head) {
                    head = temp->next;
                }
                delete temp;
            }
            return true;
        }
        temp = temp->next;
    } while (temp != head);
    gotoxy(2,2);
    cout << "La cancion con ID " << id << " no se encontro en la lista." << endl;
    return false;
}
void lista::ascendente() {
    if (!vacia()) {
        cancionn *temp;
        bool flag;
        do {
            temp = head;
            flag = false;
            do {
                if (temp->id > temp->next->id) {
                    swap(temp->id, temp->next->id);
                    swap(temp->nombre_cancion, temp->next->nombre_cancion);
                    swap(temp->artista, temp->next->artista);
                    swap(temp->album, temp->next->album);
                    swap(temp->duracion, temp->next->duracion);
                    swap(temp->ruta, temp->next->ruta);
                    flag = true;
                }
                temp = temp->next;
            } while (temp->next != head);
        } while (flag);

        // Guardar los cambios en el archivo
        ofstream outFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
        if (outFile.is_open()) {
            cancionn *temp = head;
            do {
                outFile << temp->id << ",";
                outFile << temp->nombre_cancion << ",";
                outFile << temp->artista << ",";
                outFile << temp->album << ",";
                outFile << temp->duracion << ",";
                outFile << temp->ruta << endl;
                temp = temp->next;
            } while (temp != head);
            outFile.close();
        } else {
            cout << "Error al guardar en el archivo." << endl;
        }
    }
}

void lista::descendente() {
    if (!vacia()) {
        cancionn *temp;
        bool flag;
        do {
            temp = head;
            flag = false;
            do {
                if (temp->id < temp->next->id) {
                    // Intercambiar datos
                    swap(temp->id, temp->next->id);
                    swap(temp->nombre_cancion, temp->next->nombre_cancion);
                    swap(temp->artista, temp->next->artista);
                    swap(temp->album, temp->next->album);
                    swap(temp->duracion, temp->next->duracion);
                    swap(temp->ruta, temp->next->ruta);
                    flag = true;
                }
                temp = temp->next;
            } while (temp->next != head);
        } while (flag);
        ofstream outFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
        if (outFile.is_open()) {
            cancionn *temp = head;
            do {
                outFile << temp->id << ",";
                outFile << temp->nombre_cancion << ",";
                outFile << temp->artista << ",";
                outFile << temp->album << ",";
                outFile << temp->duracion << ",";
                outFile << temp->ruta << endl;
                temp = temp->next;
            } while (temp != head);
            outFile.close();
        } else {
            cout << "Error al guardar en el archivo." << endl;
        }
    }
}

void lista::invertir() {
    if (head == NULL) {
        cout << "La lista esta vacia" << endl;
        return;
    }
    cancionn *prev = NULL;
    cancionn *curr = head;
    do {
        cancionn *next = curr->next;
        curr->next = curr->back;
        curr->back = prev;
        prev = curr;
        curr = next;
    } while (curr != head);
    head = prev;
    gotoxy(2,2);
    cout << "Lista invertida correctamente" << endl;

    // Guardar los cambios en el archivo
    ofstream outFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    if (outFile.is_open()) {
        cancionn *temp = head;
        do {
            outFile << temp->id << ",";
            outFile << temp->nombre_cancion << ",";
            outFile << temp->artista << ",";
            outFile << temp->album << ",";
            outFile << temp->duracion << ",";
            outFile << temp->ruta << endl;
            temp = temp->next;
        } while (temp != head);
        outFile.close();
    } else {
        cout << "Error al guardar en el archivo." << endl;
    }
}

void lista::eliminarPrimero() {
    if (vacia()) {
        gotoxy(2,2);
        cout << "La lista esta vacia." << endl;
        return;
    }
    if (head->next == head) {
        delete head;
        head = NULL;
    } else {
        cancionn *temp = head;
        head = head->next;
        head->back = temp->back;
        temp->back->next = head;
        delete temp;
    }

    ifstream inFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    string line;
    bool isFirstLine = true;
    while (getline(inFile, line)) {
        if (!isFirstLine) {
            outFile << line << endl;
        }
        isFirstLine = false;
    }
    inFile.close();
    outFile.close();
    remove("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    rename("temp.txt", "C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    gotoxy(2,2);
    cout << "La primera cancion ha sido eliminada correctamente." << endl;
}
void lista::eliminarUltimo() {
    if (vacia()) {
        cout << "La lista está vacia." << endl;
        return;
    }
    if (head->next == head) {
        delete head;
        head = NULL;
    } else {
        cancionn *temp = head->back;
        temp->back->next = head;
        head->back = temp->back;
        delete temp;
    }
    ifstream inFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    string line, lastLine;
    bool isFirstLine = true;
    while (getline(inFile, line)) {
        if (!isFirstLine) {
            outFile << lastLine << endl;
        }
        lastLine = line;
        isFirstLine = false;
    }
    inFile.close();
    outFile.close();
    remove("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt");
    rename("temp.txt", "C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    gotoxy(2,2);
    cout << "La ultima cancion ha sido eliminada correctamente." << endl;
}

cancionn* lista::buscarPorNombre(const string& nombre) {
    if (vacia()) {
        gotoxy(2,2);
        cout << "La lista esta vacia." << endl;
        return nullptr;
    }
    cancionn *temp = head;
    do {
        if (temp->nombre_cancion == nombre) {
            return temp;
        }
        temp = temp->next;
    } while (temp != head);
    gotoxy(2,2);
    cout << "No se encontro ninguna cancion con el nombre: " << nombre << "." << endl;
    return nullptr;
}
cancionn* lista::buscarArtista(const string& artistaBuscar) {
    if (!vacia()) {
        cancionn *temp = head;
        do {
            if (temp->artista == artistaBuscar) {
                return temp;
            }
            temp = temp->next;
        } while (temp != head);
    }
    return nullptr;
}

void lista::mostrarPrimero()
{
    if (vacia()) {
        gotoxy(2,2);
        cout << "La lista esta vacia." << endl;
        return;
    }
    else {
        gotoxy(2,2);
        cout << "Numero: " << head->id;
        gotoxy(2,3);
        cout << "Cancion: " << head->nombre_cancion;
        gotoxy(2,4);
        cout << "Artista: " << head->artista;
        gotoxy(40,2);
        cout << "Album: " << head->album;
        gotoxy(40,3);
        cout << "Duracion: " << head->duracion;
    }
}
void lista::mostrarUltimo(){
    if (vacia()) {
        gotoxy(2,2);
        cout << "La lista esta vacia." << endl;
        return;
    }
    else {
        gotoxy(2,2);
        cout << "Numero: " << head->back->id;
        gotoxy(2,3);
        cout << "Cancion: " << head->back->nombre_cancion;
        gotoxy(2,4);
        cout << "Artista: " << head->back->artista;
        gotoxy(40,2);
        cout << "Album: " << head->back->album;
        gotoxy(40,3);
        cout << "Duracion: " << head->back->duracion;
    }
}
void lista::ordenarAlfabeticamente(){
    if(!vacia()) {
        cancionn *temp;
        bool flag;
        do {
            temp = head;
            flag = false;
            do {
                if (temp->nombre_cancion > temp->next->nombre_cancion) {
                    swap(temp->id, temp->next->id);
                    swap(temp->nombre_cancion, temp->next->nombre_cancion);
                    swap(temp->artista, temp->next->artista);
                    swap(temp->album, temp->next->album);
                    swap(temp->duracion, temp->next->duracion);
                    swap(temp->ruta, temp->next->ruta);
                    flag = true;
                }
                temp = temp->next;
            } while (temp->next != head);
        } while (flag);

        // Guardar los cambios en el archivo
        ofstream outFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
        if (outFile.is_open()) {
            cancionn *temp = head;
            do {
                outFile << temp->id << ",";
                outFile << temp->nombre_cancion << ",";
                outFile << temp->artista << ",";
                outFile << temp->album << ",";
                outFile << temp->duracion << ",";
                outFile << temp->ruta << endl;
                temp = temp->next;
            } while (temp != head);
            outFile.close();
        } else {
            cout << "Error al guardar en el archivo." << endl;
        }
    }
}


class File {
private:
public:
    void saveTo(int, string, string, string, string, string);
    bool edit(int, cancionn, File);
    bool eliminar(int );
    int getLastStoredId();
};

void File::saveTo(int id, string nombre_cancion, string artista, string album, string duracion, string ruta) {
    ofstream file;
    file.open("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt", ios::app); // modificar archivo
    if (file.is_open()) {
        file << id << ",";
        file << nombre_cancion << ",";
        file << artista << ",";
        file << album << ",";
        file << duracion << ",";
        file << ruta << endl;
        file.close();
    } else {
        cout << "Error" << endl;
    }
}

bool File::eliminar(int id) {
    ifstream inFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    ofstream outFile("temp.txt"); // modificar
    if (!inFile || !outFile) {
        cout << "Error al abrir el archivo." << endl;
        return false;
    }
    string line;
    bool isEmpty = true;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id_str;
        getline(ss, id_str, ',');
        if (stoi(id_str) != id) {
            outFile << line << endl;
            isEmpty = false;
        }
    }

    inFile.close();
    outFile.close();
    remove("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    rename("temp.txt","C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo archivo
    if (isEmpty) {
        ofstream newFile("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
        if (newFile.is_open()) {
            newFile.close();
            return true;
        } else {
            cout << "Error al crear un nuevo archivo." << endl;
            return false;
        }
    }

    return true;
}


int File::getLastStoredId() {
    ifstream file;
    file.open("C:/Users/noe_l/OneDrive/Escritorio/Ramirin/reproducir.txt"); // modificar archivo
    int lastId = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id_str;
            getline(ss, id_str, ',');
            lastId = stoi(id_str);
        }
        file.close();
    }
    return lastId;
}
lista *lis = new lista();
int main(int argc, char **argv) {
    cambiarColorTexto(2);
    File file;
    int id = file.getLastStoredId() + 1;
    string nombre_cancion, artista, album, duracion, ruta;
    int opc = 0, opc2 = 0;
    char opcion[100], opcion2[100], id_[100];
    do {
        system("cls");
        lis->mostrarCanciones();
        menu();
        lis->cargar();
        gotoxy(107,17);
        cin >> opcion;
        if (ValidaMenu(opcion)) {
            opc = atoi(opcion);
            switch (opc) {

            case 1: {
            cambiarColorTexto(15);
            gotoxy(2,2);
            cout <<"Cancion:" << endl;
            cin.ignore();
            gotoxy(10,2);
            getline(cin, nombre_cancion);
            while (nombre_cancion.empty()) {
            gotoxy(10,2);
            getline(cin, nombre_cancion);
            }
            gotoxy(2,2);
            cout<<"                                                            ";
            gotoxy(2,2);
            cout <<"Artista:" << endl;
            gotoxy(10,2);
            getline(cin, artista);
            while (artista.empty()) {
            gotoxy(10,2);
            getline(cin, artista);
            }
            gotoxy(2,2);
            cout<<"                                                            ";

            gotoxy(2,2);
            cout <<"Album:" << endl;
            gotoxy(8,2);
            getline(cin, album);
            while (album.empty()) {
            gotoxy(8,2);
            getline(cin, album);
            }
            gotoxy(2,2);
            cout<<"                                                            ";

            gotoxy(2,2);
            cout <<"Duracion:" << endl;
            gotoxy(11,2);
            getline(cin, duracion);
            while (duracion.empty()) {
            gotoxy(11,2);
            getline(cin, duracion);
            }
            gotoxy(2,2);
            cout<<"                                                            ";

            gotoxy(2,2);
            cout <<"Ruta:"<< endl;
            gotoxy(7,2);
            getline(cin, ruta);
            while (ruta.empty()) {
            gotoxy(7,2);
            getline(cin, ruta);
            }
            gotoxy(2,2);
            cout<<"                                                            ";

            file.saveTo(id, nombre_cancion, artista, album, duracion, ruta);
            lis->insertarCancion(id, nombre_cancion, artista, album, duracion, ruta);
            lis->cargar();
            lis->mostrarCanciones();
            id++;
            break;
            }

                case 2: {
                    cambiarColorTexto(15);
                string artistaBuscar;
                gotoxy(2, 2);
                cout <<"Nombre del artista:";
                cin.ignore();
                gotoxy(21,2);
                getline(cin, artistaBuscar);
                gotoxy(1,2);
                cout<<"                                                   ";
                cancionn *cancionEncontrada = lis->buscarArtista(artistaBuscar);
                if (cancionEncontrada != nullptr) {
                gotoxy(2, 2);
                cout << "Cancion encontrada";
                gotoxy(2, 3);
                cout << "ID: " << cancionEncontrada->id;
                gotoxy(2,4);
                cout << "Nombre: " << cancionEncontrada->nombre_cancion;
                gotoxy(2,5);
                cout << "Artista: " << cancionEncontrada->artista;
                gotoxy(40,3);
                cout << "Album: " << cancionEncontrada->album;
                gotoxy(40,4);
                cout << "Duracion:" << cancionEncontrada->duracion;
                } else {
                gotoxy(2, 2);
                cout << "No se encontro ninguna cancion de ese artista." << endl;
                }
                break;
                }

                case 3: {
                    cambiarColorTexto(15);
                string nombreBuscar;
                gotoxy(2, 2);
                cout <<"Nombre de la cancion:";
                cin.ignore();
                gotoxy(23,2);
                getline(cin, nombreBuscar);
                gotoxy(2,2);
                cout<<"                                                   ";
                cancionn *cancionEncontrada = lis->buscarPorNombre(nombreBuscar);
                if (cancionEncontrada != nullptr) {
                gotoxy(2, 2);
                cout << "Cancion encontrada:" << endl;
                gotoxy(2,3);
                cout << "ID: " << cancionEncontrada->id << endl;
                gotoxy(2,4);
                cout << "Nombre: " << cancionEncontrada->nombre_cancion << endl;
                gotoxy(2,5);
                cout << "Artista: " << cancionEncontrada->artista << endl;
                gotoxy(40,3);
                cout << "Album: " << cancionEncontrada->album << endl;
                gotoxy(40,4);
                cout << "Duracion: " << cancionEncontrada->duracion << endl;
                } else {
                gotoxy(2, 2);
                cout << "No se encontro ninguna cancion con ese nombre" << endl;
                }
                break;
                }
                case 4: {
                    cambiarColorTexto(15);
                int id_editar;
                gotoxy(2,2);
                cout <<"ID a editar:";
                gotoxy(14,2);
                cin >> id_;
                if(ValidaMenu(id_)){
                id_editar = atoi(id_);
                gotoxy(2,2);
                cout<<"                                                      ";

                gotoxy(2,2);
                cout <<"Nuevos datos:" << endl;

                gotoxy(2,3);
                cout <<"Nombre:";
                cin.ignore();
                gotoxy(9,3);
                getline(cin, nombre_cancion);
                gotoxy(2,3);
                cout<<"                                                      ";

                gotoxy(2,3);
                cout << "Artista:";
                gotoxy(10,3);
                getline(cin, artista);
                gotoxy(2,3);
                cout<<"                                                     ";

                gotoxy(2,3);
                cout << "Album:";
                gotoxy(9,3);
                getline(cin, album);
                gotoxy(2,3);
                cout<<"                                                    ";

                gotoxy(2,3);
                cout <<"Duracion:";
                gotoxy(11,3);
                getline(cin, duracion);
                gotoxy(2,3);
                cout<<"                                                    ";

                gotoxy(2,3);
                cout <<"Ruta:";
                gotoxy(7,3);
                getline(cin, ruta);
                gotoxy(2,3);
                cout<<"                                                   ";
                if (lis->editarCancion(id_editar, nombre_cancion, artista, album, duracion, ruta)) {
                file.eliminar(id_editar);
                file.saveTo(id_editar, nombre_cancion, artista, album, duracion, ruta);
                gotoxy(2,2);
                cout << "La cancion ha sido editada correctamente." << endl;
                }
                }
                break;
                }
                case 5: {
                    cambiarColorTexto(15);
                int id_eliminar;
                gotoxy(2,2);
                cout <<"ID a eliminar:";

                gotoxy(16,2);
                cin >> id_;
                if(ValidaMenu(id_)){
                id_eliminar = atoi(id_);
                if (lis->eliminarCancion(id_eliminar)) {
                file.eliminar(id_eliminar);
                gotoxy(2,2);
                cout << "La cancion ha sido eliminada correctamente." << endl;
                }
                }
                break;
                }

                case 6: {
                    cambiarColorTexto(15);
                lis->eliminarPrimero();
                break;
                }

                case 7: {
                    cambiarColorTexto(15);
                lis->eliminarUltimo();
                break;
                }
                case 8: {
                    cambiarColorTexto(15);
                lis->invertir();
                break;
                }
                case 9:{
                    cambiarColorTexto(15);
                lis->ordenarAlfabeticamente();
                break;
                }

                case 10: {
                    cambiarColorTexto(15);
                lis->ascendente();
                break;
                }
                case 11: {
                    cambiarColorTexto(15);
                lis->descendente();
                break;
                }

                case 12: {
                    cambiarColorTexto(15);
                lis->mostrarPrimero();
                break;
                }
                case 13: {
                    cambiarColorTexto(15);
                lis->mostrarUltimo();
                break;
                }
                case 14: {
                    cambiarColorTexto(15);
                 prueba();
                 cambiarColorTexto(15);
                break;
                }
                case 15:{

                return 0;
                break;
                }
                default:
                gotoxy(92,19);
                cambiarColorTexto(15);
                cout<<"Opcion invalida";
                break;
                }
                }
        gotoxy(92,18);
        cambiarColorTexto(15);
        cout << "Continue 1.Si 2.No: ";
        cin >> opcion2;
        while (!ValidaMenu(opcion2)) {
        gotoxy(92,19);
        cambiarColorTexto(15);
        cout <<"Opcion invalida";
        gotoxy(92,20);
        cambiarColorTexto(15);
        cout<<"Continuar 1.Si 2.No: ";
        cin >> opcion2;
        }
    } while (opc2 != 2);
    system("cls");
    return 0;
}

void menu(){
    cambiarColorTexto(15);
//Titulo
gotoxy(36,1);
cout<<"PROYECTO REPRODUCTOR";
gotoxy(92,1);
cout<<"Opciones";
gotoxy(4,8);
cout<<"ID";
gotoxy(18,8);
cout<<"Cancion";
gotoxy(39,8);
cout<<"Artista";
gotoxy(61,8);
cout<<"Album";
gotoxy(79,8);
cout<<"Duracion";
//Esquina izquierda
cambiarColorTexto(2);
gotoxy(92,2);
cambiarColorTexto(15);
cout<<"1.- Agregar cancion"<<endl;
gotoxy(92,3);
cout<<"2.- Buscar Por Artista"<<endl;
gotoxy(92,4);
cout<<"3.- Buscar Por Nombre"<<endl;
gotoxy(92,5);
cout<<"4.- Editar cancion "<<endl;
gotoxy(92,6);
cout<<"5.- Eliminar Cancion"<<endl;
gotoxy(92,7);
cout<<"6.- Eliminar Primer Cancion "<<endl;
gotoxy(92,8);
cout<<"7.- Eliminar Ultima Cancion "<<endl;
gotoxy(92,9);
cout<<"8.- Invertir Lista "<<endl;
gotoxy(92,10);
cout<<"9.- Ordenar Alfabeticamente"<<endl;
gotoxy(92,11);
cout<<"10.-Ordenar ascendente "<<endl;
gotoxy(92,12);
cout<<"11.-Ordenar descendente "<<endl;
gotoxy(92,13);
cout<<"12.-Mostrar primer cancion"<<endl;
gotoxy(92,14);
cout<<"13.-Mostrar ultima Cancion "<<endl;
gotoxy(92,15);
cout<<"14.-Reproducir Cancion "<<endl;
gotoxy(92,16);
cout<<"15.- Salir"<<endl;
gotoxy(92,17);
cout<<"Digite opcion:";


gotoxy(0,0);
cout<<char(201);
cambiarColorTexto(2);

//Lineas horizontales ID-Cancion inferior
for(int x=0;x<11;x++){
gotoxy(x,9);
cout<<char(205);
}
//Conexion ID a Cancion
gotoxy(9,9);
cout<<char(206);


//Lineas verticales izquierda-arriba
for(int y=1;y<7;y++){
gotoxy(0,y);
cout<<char(186);
}
//Conexion izquierda
gotoxy(0,7);
cout<<char(204);

for(int y=10;y<25;y++){
gotoxy(9,y);
cout<<char(186);
}

//Lineas verticales izquierda-abajo
for(int y=8;y<35;y++){
gotoxy(0,y);
cout<<char(186);
}

//Esquina izquierda inferior
gotoxy(0,35);
cout<<char(200);

//Lineas horizontales de la esquina izquierda inferior a la conexion
for(int x=1;x<90;x++){
gotoxy(x,35);
cout<<char(205);
}
//Lineas horizontales con conexion
for(int x=1;x<9;x++){
gotoxy(x,25);
cout<<char(205);
}

//Conexion Abajo
gotoxy(33,25);
cout<<char(202);

//Lineas horizontales cancion
for(int x=9;x<33;x++){
gotoxy(x,25);
cout<<char(205);
}

//Lineas horizontales cancion arriba
for(int x=10;x<33;x++){
gotoxy(x,7);
cout<<char(205);
}
//Conexion
gotoxy(33,7);
cout<<char(203);

//Conexion arriba
gotoxy(33,9);
cout<<char(206);

gotoxy(33,8);
cout<<char(186);

for(int y=10;y<25;y++){
gotoxy(33,y);
cout<<char(186);
}


//Lineas horizontales cancion medias
for(int x=11;x<33;x++){
gotoxy(x,9);
cout<<char(205);
}

//Lineas horizontales artista

for(int x=34;x<50;x++){
gotoxy(x,7);
cout<<char(205);
}

for(int x=34;x<50;x++){
gotoxy(x,9);
cout<<char(205);
}

for(int x=34;x<50;x++){
gotoxy(x,25);
cout<<char(205);
}

gotoxy(50,7);
cout<<char(203);
gotoxy(50,8);
cout<<char(186);
gotoxy(50,9);
cout<<char(206);
gotoxy(50,25);
cout<<char(202);

for(int y=10;y<25;y++){
gotoxy(50,y);
cout<<char(186);
}

//Lineas album
for(int x=51;x<76;x++){
gotoxy(x,7);
cout<<char(205);
}
for(int x=51;x<76;x++){
gotoxy(x,9);
cout<<char(205);
}
for(int x=51;x<76;x++){
gotoxy(x,25);
cout<<char(205);
}
gotoxy(76,7);
cout<<char(203);
gotoxy(76,8);
cout<<char(186);
gotoxy(76,9);
cout<<char(206);
gotoxy(76,25);
cout<<char(202);

for(int y=10;y<25;y++){
gotoxy(76,y);
cout<<char(186);
}

//Lineas duracion
for(int x=77;x<91;x++){
gotoxy(x,7);
cout<<char(205);
}
for(int x=77;x<91;x++){
gotoxy(x,9);
cout<<char(205);
}
for(int x=77;x<91;x++){
gotoxy(x,25);
cout<<char(205);
}

//Conexion
gotoxy(9,25);
cout<<char(202);

//Lineas horizontales al lado de conexion izquierda
for(int x=1;x<9;x++){
gotoxy(x,7);
cout<<char(205);
}



//Conexion ID Y Cancion
gotoxy(9,7);
cout<<char(203);

//Linea vertical conectada
gotoxy(9,8);
cout<<char(186);

//Conexion izquierda-derecha superior
gotoxy(90,7);
cout<<char(185);

//Lineas verticales abajo de la conexion
for(int y=8;y<25;y++){
gotoxy(90,y);
cout<<char(186);
}
//Conexion izquierda, derecha y arriba
gotoxy(90,25);
cout<<char(202);

for(int x=91;x<119;x++){
gotoxy(x,25);
cout<<char(205);
}


//Conexion izquierda-derecha inferior
gotoxy(90,35);
cout<<char(205);


//Lineas horizontales arriba
for(int x=1;x<90;x++){
gotoxy(x,0);
cout<<char(205);
}
//Cruce
gotoxy(90,0);
cout<<char(203);

//Lineas verticales del cruce
for(int y=1;y<7;y++){
gotoxy(90,y);
cout<<char(186);
}

//Lineas horizontales despues del cruce
for(int x=91;x<119;x++){
gotoxy(x,0);
cout<<char(205);
gotoxy(x,0);
cout<<char(205);
}
//Esquina derecha
gotoxy(119,0);
cout<<char(187);

//Lineas verticales derecha
for(int y=1;y<35;y++){
gotoxy(119,y);
cout<<char(186);
}
//Esquina inferior derecha
gotoxy(119,35);
cout<<char(188);

for(int x=91;x<119;x++){
gotoxy(x,35);
cout<<char(205);
}

}





void prueba() {
    cancionn *temp = NULL;
    temp = aux;
    int opc2 = 0;
    int a = 0;
    int b = 0; // par almacenar la segunda tecla
    //opciones();

    do {
        system("cls");
        menu();
        while (true) {
            if (_kbhit()) {
                a = _getch(); // lee la primera tecla
                if (a == 224) { // si es una flecha va a leer de nuevo
                    b = _getch();

                    switch (b) {


                        case 72: // Flecha arriba
                            system("cls");
                            menu();
                            temp = temp->back;
                            lis->mostrarflecha(temp->nombre_cancion);
                            break;
                        case 80: // Flecha abajo
                            system("cls");
                            menu();
                            temp = temp->next;
                            lis->mostrarflecha(temp->nombre_cancion);
                            //opciones();
                            break;

                        case 75: // Flecha abajo
                            system("cls");
                            menu();
                            lis->mostrarflecha(temp->nombre_cancion);
                            //opciones();
                            mci(temp->nombre_cancion);
                            break;
                    }
                } else if (a == 32) {

                    return;
                }
            }
        }
    } while (a != 20);


}


int mci(string cancion) {
    cambiarColorTexto(15);
    string ruta = "C:/Users/noe_l/OneDrive/Escritorio/Ramirin/" + cancion + ".wav"; // nueva ruta
    mciSendString(("open \"" + ruta + "\" type waveaudio alias mysound").c_str(), NULL, 0, NULL);
    char buffer[128];
    mciSendString("status mysound length", buffer, sizeof(buffer), NULL);
    long songLength = atol(buffer);
    mciSendString("play mysound", NULL, 0, NULL);

    // Inicialización de la barra de progreso vacía inmediatamente después de iniciar la reproducción
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.dwSize.X;

    // Dibuja la barra vacía antes de empezar el bucle de actualización
    gotoxy(2, 26); // Ajusta la posición según tu preferencia
    cambiarColorTexto(8);
    for (int i = 2; i <= screenWidth - 6; i++) {
        cout << char(177);
    }
    cambiarColorTexto(15);

    gotoxy(6, 40);
    dibujarControles();

    // Configuración de variables para el progreso
    long startTime = GetTickCount();
    long pausedTime = 0;
    bool isPaused = false;
    double previousProgress = 0.0;

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                case 'p':
                    if (!isPaused) {
                        mciSendString("pause mysound", NULL, 0, NULL);
                        pausedTime = GetTickCount() - startTime;
                        isPaused = true;
                    }
                    break;
                case 'r':
                    if (isPaused) {
                        mciSendString("resume mysound", NULL, 0, NULL);
                        startTime = GetTickCount() - pausedTime;
                        isPaused = false;
                    }
                    break;
                case 'q':
                    mciSendString("close mysound", NULL, 0, NULL);
                    for (int i = 2; i < 70; i++) {
                        gotoxy(i, 27);
                        cout << " ";
                    }
                    return 0;
            }
        }

        long currentTime = GetTickCount();
        long elapsedTime = isPaused ? pausedTime : (currentTime - startTime);
        double progress = static_cast<double>(elapsedTime) / songLength;

        // se actualiza cada que avance el 1%
        if (progress - previousProgress >= 0.01) {
            gotoxy(2, 26);

            if (progress >= 1.0) break;

            for (int i = 2; i <= progress * (screenWidth - 4); i++) {
                gotoxy(i, 26);
                cout << char(219);
            }

            previousProgress = progress;
        }

        Sleep(5);
    }

    mciSendString("close mysound", NULL, 0, NULL);
    return 0;
}

void dibujarControles() {
    int xPos = 36; // Ajusta la posición horizontal para cada círculo
    int yPos = 28; // Línea debajo de la barra de progreso

    // Dibujo del botón "Stop" (dentro de un círculo pequeño)
    gotoxy(xPos, yPos);
    cout << "   . . .   ";
    gotoxy(xPos, yPos + 1);
    cout << " .       . ";
    gotoxy(xPos, yPos + 2);
    printf(".    %c    .",254);
    gotoxy(xPos, yPos + 3);
    cout << " .       . ";
    gotoxy(xPos, yPos + 4);
    cout << "   . . .   ";

    // Dibujo del botón "Pause" (dentro de un círculo pequeño)
    xPos += 15;
    gotoxy(xPos, yPos);
    cout << "   . . .   ";
    gotoxy(xPos, yPos + 1);
    cout << " .       . ";
    gotoxy(xPos, yPos + 2);
    printf(".   %c %c   .",124,124);
    gotoxy(xPos, yPos + 3);
    cout << " .       . ";
    gotoxy(xPos, yPos + 4);
    cout << "   . . .   ";

    // Dibujo del botón "Play" (dentro de un círculo pequeño)
    xPos += 15;
    gotoxy(xPos, yPos);
    cout << "   . . .   ";
    gotoxy(xPos, yPos + 1);
    cout << " .       . ";
    gotoxy(xPos, yPos + 2);
    printf(".    %c    .",61);
    gotoxy(xPos, yPos + 3);
    cout << " .       . ";
    gotoxy(xPos, yPos + 4);
    cout << "   . . .   ";
}
