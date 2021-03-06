#include "Buzon.h"

    Buzon::Buzon(){
        this->clave = 0xB70442;
        if (this->clave == (key_t)-1)
        {
            cout << "Error al obtener clave para cola mensajes" << endl;
            exit(-1);
        }

        this->id_Cola = msgget (clave, 0600 | IPC_CREAT);
        if (this->id_Cola == -1)
        {
            cout << "Error al obtener identificador para cola mensajes" << endl;
            exit (-1);
        }
    }

    void Buzon::enviar_Mensaje(long id,char * msj){
        un_Mensaje.id_Mensaje = id;
        msgsnd (this->id_Cola, (struct msgbuf *)&un_Mensaje, 
        sizeof(un_Mensaje.chunk_Num)+sizeof(un_Mensaje.mensaje), 0);
    }

    int Buzon::recibir_Mensaje(long id){
        int recibido = msgrcv (this->id_Cola, (struct msgbuf *)&un_Mensaje,
        sizeof(un_Mensaje.chunk_Num)+sizeof(un_Mensaje.mensaje), id, 0);
        //cout << "Recibido mensaje tipo "<< id<< endl;
        //cout << "Mensaje = " << un_Mensaje.mensaje << endl;
        return recibido;
    }

    Buzon::~Buzon(){
        msgctl (this->id_Cola, IPC_RMID, (struct msqid_ds *)NULL);
    }
