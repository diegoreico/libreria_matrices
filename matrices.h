
typedef int TELEMENTO;
typedef void *TMATRIZ;

void crear(TMATRIZ *matrix,int size);

void destruir(TMATRIZ *matrix);

void asignar(TMATRIZ *matrix, int x,int y, TELEMENTO valor);

void recuperar(TMATRIZ matrix, int x, int y, TELEMENTO *d);

void tamano(TMATRIZ matrix, int *t);