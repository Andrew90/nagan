//---------------------------------------------------------------------------

#ifndef SMSH
#define SMSH

#include <Sockets.hpp>
#include "Dialogs.hpp"


//---------------------------------------------------------------------------
// класс по отправке и передаче сообщений между толщиномером и дефектоскопом по TCP/IP
// толщиномер всегда клиент (инициатор соединени€), дефектоскоп всегда сервер
class SMS
{
public:
	SMS(TComponent *Owner);		// конструктор (задать владельца - форму)
	~SMS();						// деструктор
	String ServerName;			// им€ сервера (нужно задать в обоих проектах!!!)
	int Port;					// номер порта по обмену (должен быть одинаков)
	void SendAnyMessage(String sendString);					// послать любое сообщение с клиента на сервер
	bool SendZoneThickness(int zone , double thickness);	// послать толщину в зоне
	int AskTubeLength();									// запрос длины трубы
	bool TestConnection();									// тест соединени€ по TCP/IP
	void StartServer();										// старт сервера (выолн€етс€ 1 раз в начале)

private:
	TTcpServer *Server;				// экземпл€р сервера
	TTcpClient *Client;				// экземпл€р клиента
	wchar_t client_rec[50];			// массив прин€тых данных клиента
	wchar_t server_rec[50];			// массив прин€тых данных сервера
	int server_rec_length;			// длина прин€тых данных сервера
	int client_rec_length;			// длина прин€тых данных клиента
	int sen_length;					// длина посылки
	TEvent *client_get;				// событие - клиент получил данные

	String CreateServerRespond();	// создает ответ сервера дл€ клиента
	void __fastcall ServerAccept(TObject *Sender, TCustomIpClient *ClientSocket);	// к серверу подключилс€ клиент
	void __fastcall ServerCreateHandle(TObject *Sender);							// сервер создан
	void __fastcall ServerDestroyHandle(TObject *Sender);							// сервер уничтожен
	void __fastcall ServerSend(TObject *Sender, PChar Buf, int &DataLen);			// сервер отправил
	void __fastcall ServerReceive(TObject *Sender, PChar Buf, int &DataLen);		// сервер получил

	void __fastcall ClientSend(TObject *Sender, PChar Buf, int &DataLen);			// клиент отправил
	void __fastcall ClientReceive(TObject *Sender, PChar Buf, int &DataLen);		// клиент получил
	void __fastcall ClientConnect(TObject *Sender);									// клиент соединилс€
	void __fastcall ClientDisconnect(TObject *Sender);								// клиент отсоединилс€
	void __fastcall ClientError(TObject *Sender, int SocketError);					// ошибка в клиенте

};
//---------------------------------------------------------------------------
extern SMS* sms;					// экземпл€р класса —ћ—, видимый отовсюду
//---------------------------------------------------------------------------
#endif
