# IRC

    to run :
        first terminal :
            g++ ./srcs/Serverer/Server.cpp -o Server
            ./Server
        second terminal : 
            use *nc* or any equiv command like
                nc -c localhost (127.0.0.1) with the assigned port (9999)
                    : nc -c 127.0.0.1 9999
        same command with the third terminal : 
            you will be able to notice that a multiple users created with a different Id
    21-08-2022:
        ->  server class + hpp are created and well handled 
        ->  the basic tests are working creating multiple client send and receive   msgs is working   
    23-08-2022"
        ->  create User and user map.
        ->  insert and erase a user with his ip and fd.
    24-08-2022:
        ->  create msg class and add check the syntaxe of the received message.