#Target_name : Dependencies

target_c: client.cpp main.cpp reminder.cpp message.cpp login.cpp password_auth.cpp hash.cpp 
	g++ client.cpp main.cpp reminder.cpp message.cpp login.cpp password_auth.cpp hash.cpp -lssl -lcrypto -w -o client.out

target_s: server.cpp reminder.cpp message.cpp login.cpp password_auth.cpp hash.cpp medication.cpp
	g++ server.cpp reminder.cpp message.cpp login.cpp password_auth.cpp hash.cpp medication.cpp -lssl -lcrypto -w -o server.out