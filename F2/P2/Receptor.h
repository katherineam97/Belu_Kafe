#ifndef  RECEPTOR_H
#define RECEPTOR_H
#include "Cola.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <pthread.h>
/*El struct que utiliza el método que extrae los mensajes y escribe en los archivos
 */

class Receptor{
    private:
     Cola * cola;
    public:
        /*constructor, inicializa cola de mensajes
         */
        Receptor();
        /*Destructor de la clase Receptor
         */
        ~Receptor();
        /*Método que establece conexión con el emisor y recibe los mensajes 
         */
        void conectar();
        /*método que extrae el id, el tamaño del mensaje y el mensaje util, los separa y envía a encolar
         */
        void desempaquetar(char *);
        /*Método que recibe el mensaje util y el id, y el tamaño del mensaje para proceder a encolarlo en la
         * cola con su respectivo mensaje, prioridad y tamaño
         */
        void encolar(char *, long, int);
        /*Método que utilizan los hilos para desencolar mensaje util y escribir en el archivo
         */
        static void* hiloEscritor(void * data){
            size_t idT= (size_t) data;
            string cadena = "nuevo" + to_string(idT);
            int id = open( cadena.data(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
            Cola * colaH= new Cola();
             do{
                colaH->desencolar_Mensaje(idT);
                if(strcmp(colaH->un_Mensaje.mensaje,"")!=0)
                    write( id, colaH->un_Mensaje.mensaje, colaH->un_Mensaje.tamano);
			
            }while(strcmp(colaH->un_Mensaje.mensaje,"")!=0);
        }
        
    
};
#endif
