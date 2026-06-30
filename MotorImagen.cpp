#include "MotorImagen.h"
#include <iomanip>
#include <sstream>
MotorImagen::MotorImagen() {
    // Constructor implementation
    nombreArchivo = "";
    filas = 0;
    columnas = 0;
    maxValor = 255;
    matrizPixeles = nullptr;
    imagenCargada = false;
    tipoImagen = "general";
std::cout << "[MotorImagen] Constructor: Motor inicializado." << std::endl;
}

MotorImagen::~MotorImagen() {
    liberarMemoria();
    std::cout << "[MotorImagen] Destructor: Memoria liberada." << std::endl;

}
void MotorImagen::liberarMemoria() {
    if (matrizPixeles != nullptr) {
        for (int i = 0; i < filas; i++) {
            delete[] matrizPixeles[i];
        }
        delete[] matrizPixeles;
        matrizPixeles = nullptr;
    }
    filas = 0;
    columnas = 0;
    imagenCargada = false;
   std::cout << "[Memoria] Matriz liberada correctamente." << std::endl;
}
bool MotorImagen::reservarMemoria(int filas, int columnas) {
    liberarMemoria();
    try{
        matrizPixeles = new Pixel*[filas];
        for (int i = 0; i < filas; i++) {
            matrizPixeles[i] = new Pixel[columnas];
            for (int j = 0; j < columnas; j++) {
                matrizPixeles[i][j] = {0, 0, 0}; // Inicializar con valores predeterminados
            }
       
        }
        this->filas = filas;
        this->columnas = columnas;
        imagenCargada = true;
        return true;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[Error] No se pudo reservar memoria para la matriz de píxeles." << std::endl;
        return false;
    }
}
void MotorImagen::copiarMatriz(const MotorImagen& origen){
    if (!origen.imagenCargada) return;
    reservarMemoria(origen.filas, origen.columnas);
    for (int i = 0; i < origen.filas; i++) {
        for (int j = 0; j < origen.columnas; j++) {
            matrizPixeles[i][j] = origen.matrizPixeles[i][j];
        }
    }
}

bool MotorImagen::cargarImagen(const std::string& ruta) {
    std::string extension = ruta.substr(ruta.find_last_of('.') + 1);
    if (extension == "ppm"|| extension == "PPM"){
        return cargarImagenPPM(ruta);
    } else if (extension == "pgm"|| extension == "PGM") {
        return cargarImagenPGM(ruta);
    } else {
        std::cerr << "[Error] Formato de imagen no soportado: " << extension << std::endl;
        return false;
    }
}
bool MotorImagen::cargarImagenPPM(const std::string& ruta) {
    liberarMemoria();
    std::ifstream archivo(ruta.c_str(), std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "[Error] No se pudo abrir el archivo: " << ruta << std::endl;
        return false;
    }

    std::string formato;
    archivo >> formato;
    if (formato != "P3" && formato != "P6") {
        std::cerr << "[Error] Formato de imagen PPM no válido. Debe ser P3 o P6" <<std::endl;
        archivo.close();
        return false;
    }
 char c;
 archivo >> c;
 while (c == '#'){
    archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    archivo >> c;
    /* code */
 }
 archivo.putback(c);
 archivo >> columnas >> filas >> maxValor;
 if (!reservarMemoria(filas, columnas)) {
     archivo.close();
     return false;
    }
    if(formato == "P3"){
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                archivo >> matrizPixeles[i][j].r;
                archivo >> matrizPixeles[i][j].g;
                archivo >> matrizPixeles[i][j].b;
            }
        }
    } else{
        archivo.get();
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                unsigned char r, g, b;
                archivo.read(reinterpret_cast<char*>(&r), sizeof(unsigned char));
                archivo.read(reinterpret_cast<char*>(&g), sizeof(unsigned char));
                archivo.read(reinterpret_cast<char*>(&b), sizeof(unsigned char));
                matrizPixeles[i][j].r = r;
                matrizPixeles[i][j].g = g;
                matrizPixeles[i][j].b = b;
            }
        }
    }
    archivo.close();
    nombreArchivo = ruta;
    imagenCargada = true;
    std::cout<< "Imagen cargada: "<< filas << "x" << columnas <<" ("<< (filas *columnas) << " píxeles)" << std::endl;
    std::cout <<" Formato: " << formato << ", Max Valor: " << maxValor << std::endl;
    return true;
 

}
bool MotorImagen::guardarImagenPPM(const std::string& ruta) {
    std::ofstream archivo(ruta.c_str());
    if (!archivo.is_open()) {
        std::cerr << "[Error] No se pudo abrir el archivo para guardar: " << ruta << std::endl;
        return false;
    }
    archivo << "P3"<< std::endl;
    archivo << "# Imagen guardada por MotorImagen" << std::endl;
    archivo << columnas << " " << filas << std::endl;
    archivo << maxValor << std::endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo << matrizPixeles[i][j].r << " "
                    << matrizPixeles[i][j].g << " "
                    << matrizPixeles[i][j].b << std::endl;
                    if(j < columnas - 1) archivo << " ";
                    
        }
        archivo << std::endl;
    }
    archivo.close();
    std::cout << "Imagen guardada" << ruta << std::endl;
    return true;
}

Pixel MotorImagen::getPixel(int fila, int col) const{
    if(validarCoordenadas(fila,col)){
        return matrizPixeles[fila][col];
    }
    return Pixel(0,0,0);
}
void MotorImagen::setPixel(int fila, int col, const Pixel& pixel){
    if(validarCoordenadas(fila, col)){
        matrizPixeles[fila][col] = pixel;
    }
}
void MotorImagen::setPixel(int fila, int col, int r, int g, int b){
    if(validarCoordenadas(fila, col)){
        matrizPixeles[fila][col].r = r;
        matrizPixeles[fila][col].g = g;
        matrizPixeles[fila][col].b = b;
    }
}
bool MotorImagen::validarCoordenadas(int fila, int col) const {
    return (fila >= 0 && fila < filas && col >= 0 && col < columnas && matrizPixeles != nullptr);
}
void MotorImagen::mostrarEstadisticas() const{
    if(!imagenCargada || matrizPixeles == nullptr){
        std::cout << "No hay imagen cargada en memoria"<< std::endl;
        return;
    }
    long long totalPixeles = static_cast<long long>(filas)* columnas;
    int minR = 255, maxR = 0, minG = 255, maxG = 0, minB = 255, maxB = 0;
    double sumaR = 0, sumaG = 0, sumaB = 0;
    for(int i = 0; i<filas; i++){
        for(int j=0; j< columnas; j++){
            const Pixel& p = matrizPixeles[i][j];
            sumaR += p.r; sumaG += p.g; sumaB += p.b;
            if (p.r<minR) minR= p.r; if(p.r > maxR) maxR = p.r;
            if (p.g<minG) minG= p.g; if(p.g > maxG) maxG = p.g;
            if (p.b<minB) minB= p.b; if(p.b > maxB) maxB = p.b;
        }
    }
    double mediaR = sumaR / totalPixeles;
    double mediaG = sumaG / totalPixeles;
    double mediaB = sumaB / totalPixeles;

    std::cout << "\n╔══════════════════════════════════════╗" << std::endl;
    std::cout << "║       ESTADÍSTICAS DE LA IMAGEN      ║" << std::endl;
    std::cout << "╠═══════════════════════════════════════╣" << std::endl;
    std::cout << "║ Archivo: " << std::left << std::setw(33) << nombreArchivo << "║" << std::endl;
    std::cout << "║ Dimensiones: " << filas << "x" << columnas << std::setw(17) << " " << "║" << std::endl;
    std::cout << "║ Total píxeles: " << totalPixeles << std::setw(16) << " "<< "║" << std::endl;
    std::cout << "║ Tipo: " << std::setw(33) << tipoImagen << "║" << std::endl;
    std::cout << "╠═══════════════════════════════════════╣" << std::endl;
    std::cout << "║ Canal | Min | Max |  Media  ║" << std::endl;
    std::cout << "╟———————┼—————┼—————┼—————————╢" << std::endl;
    std::cout << "║   R   | " << std::setw(3) << minR << " | " << std::setw(3) << maxR
              << " | " << std::fixed << std::setprecision(1) << std::setw(7) << mediaR << " ║" << std::endl;
    std::cout << "║   G   |" << std::setw(3) << minG << " | " << std::setw(3) << maxG
              << " | " << std::fixed << std::setprecision(1) << std::setw(7) << mediaG << " ║" << std::endl;
    std::cout << "║   B   |" << std::setw(3) << minB << " | "<< std::setw(3) << maxB
              << " | " << std::fixed << std::setprecision(1) << std::setw(7) << mediaB << " ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝"<< std::endl;

    long long memoria = totalPixeles * sizeof(Pixel);
    if(memoria < 1024){
        std::cout <<"Memoria: " << memoria<< "bytes" << std::endl;
    } else if (memoria < 1024 * 1024) {
        std::cout << "Memoria: " << memoria / 1024 << "KB" << std::endl;
    } else {
        std::cout << "Memoria: " << memoria / (1024 * 1024) << "MB" << std::endl;
    }
    

}
void MotorImagen::generarHistograma() const{
    if(!imagenCargada || matrizPixeles == nullptr) return;
    int histR[256] = {0}, histG[256] = {0}, histB[256] = {0};

    for(int i=0; i<filas; i++){
        for(int j = 0; j < columnas; j++){
            const Pixel& p = matrizPixeles[i][j];
            histR[p.r]++; histG[p.g]++; histB[p.b]++;
        }
    }
    std::cout << "\n=== HISTOGRAMA DE COLORES (resumido) ===" << std::endl;
    std::cout << "Rango |  R  |  G  |  B  |" << std::endl;
    std::cout << "——————┼—————┼—————┼—————┤" << std::endl;

    for(int i = 0; i < 8; i++){
        int inicio = i * 32;
        int fin = inicio + 31;
        int totalR = 0, totalG = 0, totalB = 0;

        for(int j = inicio; j <= fin && j<256; j++){
            totalR += histR[j];
            totalG += histG[j];
            totalB += histB[j];
        }
        std::cout << std::setw(3) << inicio << "-" << std::setw(3) << fin << " | "
                  << std::setw(4) << totalR << " | "
                  << std::setw(4) << totalG << " | "
                  << std::setw(4) << totalB << " |" << std::endl;
    }
}

void MotorImagen::establecerTipoImagen(const std::string& tipo){
    tipoImagen = tipo;
    std::cout << "Tipo de imagen establecido: "<< tipoImagen << std::endl;
}